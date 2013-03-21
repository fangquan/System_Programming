#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/select.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>

fd_set rd;
fd_set wr;

#define MAX_CLIENTS 16
#define BSIZE 1024
typedef struct client {
	int fd;		// file descriptor of local file being transferred
	int size;   // size of out-going data in buffer
	char buf[BSIZE];
	enum state {RDY, BAD, GOOD, TRANSFER} state;
	/*
	   states:
	            RDY: ready to receive client's command (P or G)
				BAD: client's command was bad, sending B response + error msg
				GOOD: client's command was good, sending G response
				TRANSFER: transferring data
	*/
	enum dir {IN, OUT} dir;
	/*
	   IN: client has issued P command
	   OUT: client has issued G command
	*/
} client_t;

client_t clients[MAX_CLIENTS];	// Each active client has a slot in this array.
								// Array is indexed by file descriptor of
								// connected socket

int main(int argc, char *argv[ ]) {
	struct sockaddr_in my_addr;
	int lsock;
	int maxfd;
	int new_client(int);
	void read_event(int);
	void write_event(int);

	if (argc != 2) {
		fprintf(stderr, "Usage: server port\n");
		exit(1);
	}

	signal(SIGPIPE, SIG_IGN);
		// ignore SIGPIPE so that we learn about it via an errno

	// establish a socket for TCP
	if ((lsock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	/* set up our address */
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = PF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(atoi(argv[1]));

	/* bind the address to our socket */
	if (bind(lsock, (struct sockaddr *)&my_addr,
		sizeof(my_addr)) < 0) {
		perror("bind");
		exit(1);
	}

	/* put socket into “listening mode” */
	if (listen(lsock, 5) < 0) {
		perror("listen");
		exit(1);
	}

	memset(clients, -1, sizeof(clients));
		// fill clients array with invalid entries

	// zero out fd sets, then initialize rd with the listening socket
	FD_ZERO(&rd);
	FD_ZERO(&wr);
	FD_SET(lsock, &rd);
	maxfd = lsock+1;

	while (1) {
		int nfds;
		int i;
		int serviced;
		fd_set trd;
		fd_set twr;

		// refresh fd sets
		trd = rd;
		twr = wr;

		// Wait for something to happen: always interested in read events
		// from listening socket (i.e., new connections).
		// For the other sockets, their bits in trd and twr (for reading
		// and writing) are set only if we are expecting input or attemping
		// output
		if ((nfds=select(maxfd, &trd, &twr, 0, 0)) == -1) {
			perror("select");
			exit(1);
		}
		// fd sets now tell us which operations are possible

		serviced = 0;
		if (FD_ISSET(lsock, &trd)) {
			// a new connection
			int newfd = new_client(lsock);
			if (newfd >= maxfd)
				maxfd = newfd+1;
			serviced++;
		}
		for (i=lsock+1; i<maxfd; i++) {
			if (FD_ISSET(i, &trd)) {
				// ready to read
				read_event(i);
				serviced++;
			}
			if (FD_ISSET(i, &twr)) {
				// ready to write
				write_event(i);
				serviced++;
			}
			if (serviced >= nfds-1)
				break;
		}
	}
	return 0;
}

// Accept a new connection on listening socket fd. Return
// the connected file descriptor
int new_client(int fd) {
	struct sockaddr_in client_addr;
	int client_len = sizeof(client_addr);

	int cfd = accept(fd, (struct sockaddr *)&client_addr, &client_len);
	if (cfd == -1) {
		perror("accept");
		return 0;
	}
	fprintf(stderr, "Received connection from %s\n",		
		inet_ntoa(client_addr.sin_addr));
	if (cfd >= MAX_CLIENTS) {
		fprintf(stderr, "too many clients\n");
		return 0;
	}
	assert(clients[cfd].fd == -1);
	clients[cfd].state = RDY;
	FD_SET(cfd, &rd);
	return cfd;
}


// File descriptor fd is ready to be read. Read it, then handle
// the input
void read_event(int fd) {
	client_t *c = &clients[fd];
	int ret = read(fd, c->buf, BSIZE);
	if (ret == -1) {
		// couldn't read from client; terminate connection
		close(c->fd);
		close(fd);
		FD_CLR(fd, &wr);
		c->fd = -1;
		perror("read from client");
		return;
	}
	switch (c->state) {
	case RDY:
		if (c->buf[0] == 'G') {
			// GET request (to fetch a file)
			c->dir = OUT;
			if ((c->fd = open(&c->buf[1], O_RDONLY)) == -1) {
				// open failed; send negative response and error message
				c->state = BAD;
				c->buf[0] = 'B';
				strncpy(&c->buf[1], strerror(errno)+1, BSIZE-2);
				c->buf[BSIZE-1] = 0;
				c->size = strlen(c->buf)+1;
			} else {
				// open succeeded; send positive response
				c->state = GOOD;
				c->size = 1;
				c->buf[0] = 'G';
			}
			// prepare to send response to client
			FD_SET(fd, &wr);
			FD_CLR(fd, &rd);
			break;
		}
		if (c->buf[0] == 'P') {
			// PUT request (to create a file)
			c->dir = IN;
			if ((c->fd = open(&c->buf[1], O_RDWR|O_CREAT|O_TRUNC, 0666)) == -1) {
				// open failed; send negative response and error message
				c->state = BAD;
				c->buf[0] = 'B';
				strcpy(&c->buf[1], strerror(errno));
				c->size = strlen(c->buf);
			} else {
				// open succeeded; send positive response
				c->state = GOOD;
				c->size = 1;
				c->buf[0] = 'G';
			}
			// prepare to send response to client
			FD_SET(fd, &wr);
			FD_CLR(fd, &rd);
			break;
		}
	case TRANSFER:
		// should be in midst of receiving file contents from client
		assert(c->dir == IN);
		if (ret == 0) {
			// eof: all done
			close(c->fd);
			close(fd);
			FD_CLR(fd, &rd);
			c->fd = -1;
			break;
		}
		if (write(c->fd, c->buf, ret) == -1) {
			// write to file failed: terminate connection to client
			perror("write");
			close(c->fd);
			close(fd);
			FD_CLR(fd, &rd);
			c->fd = -1;
			break;
		}
		// continue to read more data from client
		break;
	default:
		close(c->fd);
		close(fd);
		FD_CLR(fd, &rd);
		break;
	}
	return;
}

// File descriptor fd is ready to be written to. Write to it, then,
// depending on current state, prepare for the next action.
void write_event(int fd) {
	client_t *c = &clients[fd];
	int ret = write(fd, c->buf, c->size);
	if (ret == -1) {
		// couldn't write to client; terminate connection
		close(c->fd);
		close(fd);
		FD_CLR(fd, &wr);
		c->fd = -1;
		perror("write to client");
		return;
	}
	switch (c->state) {
	case BAD:
		// finished sending error message; now terminate client connection
		close(c->fd);
		close(fd);
		FD_CLR(fd, &wr);
		c->fd = -1;
		break;
	case GOOD:
		if (c->dir == IN) {
			// finished response to PUT request
			c->state = TRANSFER;
			FD_SET(fd, &rd);
			FD_CLR(fd, &wr);
			break;
		}
		// otherwise finished response to GET request, so proceed
	case TRANSFER:
		// should be in midst of transferring file contents to client
		assert(c->dir == OUT);
		if ((c->size = read(c->fd, c->buf, BSIZE)) == -1) {
			// read from file failed: terminate connection to client
			perror("read");
			close(c->fd);
			close(fd);
			FD_CLR(fd, &wr);
			c->fd = -1;
			break;
		} else if (c->size == 0) {
			// no more file to transfer; terminate client connection
			close(c->fd);
			close(fd);
			FD_CLR(fd, &wr);
			c->fd = -1;
			break;
		}
		// continue to write more data to client
		break;
	default:
		// protocol problem if we get here
		assert(0 && "shouldn't be here");
	}
}
