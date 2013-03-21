#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[ ]) {
	struct sockaddr_in my_addr;
	int lsock;
	void serve(int);
	if (argc != 2) {
		fprintf(stderr, "Usage: server port\n");
		exit(1);
	}

	// Step 1: establish a socket for TCP
	// lsock listening socket
	if ((lsock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	/* Step 2: set up our address */
	/* A little complicated than unix domain */
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = PF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(atoi(argv[1]));

	/* Step 3: bind the address to our socket */
	if (bind(lsock, (struct sockaddr *)&my_addr,sizeof(my_addr)) < 0) {
		perror("bind");
		exit(1);
	}

	/* Step 4: put socket into listening modes */
	if (listen(lsock, 5) < 0) {
		perror("listen");
		exit(1);
	}

	while (1) {
		int csock;
		struct sockaddr_in client_addr;
		int client_len = sizeof(client_addr);

		/* Step 5: receive a connection */
		csock = accept(lsock,(struct sockaddr *)&client_addr, &client_len);
		printf("Received connection from %s\n",inet_ntoa(client_addr.sin_addr));
		switch (fork( )) {
			case -1:
				perror("fork");
				exit(1);
			case 0:
				// Step 6: create a new process to handle connection
				serve(csock);
				break;
			default:	
				close(csock);
				break;
		}
	}
	return 0;
}

void serve(int fd) {
	char buf[1024];
	int count;

	// Step 7: read incoming data from connection
	while ((count = read(fd, buf, 1024)) > 0) {
		write(1, buf, count);
	}
	if (count == -1) {
		perror("read");
		exit(1);
	}
	printf("connection terminated\n");
}
