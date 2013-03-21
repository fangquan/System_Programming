#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define BSIZE 1024

int main(int argc, char *argv[]) {
	struct sockaddr_in server_addr;
	int sock;
	struct hostent *hostinfo;
	int ret;
	int sourceFD;

	char buf[BSIZE];
	if (argc != 5) {
		fprintf(stderr, "Usage: Put host port local_file server_file\n");
		exit(1);
	}

	if ((sourceFD = open(argv[3], O_RDONLY)) == -1) {
		perror(argv[3]);
		exit(1);
	}

	// set up socket for TCP
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	// find the internet address of the server
	if ((hostinfo = gethostbyname(argv[1])) == 0) {
		fprintf(stderr, "Host %s does not exist\n", argv[1]);
		exit(1);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	memcpy(&server_addr.sin_addr, hostinfo->h_addr_list[0],
		hostinfo->h_length);
	server_addr.sin_port = htons(atoi(argv[2]));

	// connect to the server
	if (connect(sock, (struct sockaddr *)&server_addr,
		sizeof(server_addr)) < 0) {
		perror("connect");
		exit(1);
	}

	// send request to the server
	buf[0] = 'P';
	strncpy(&buf[1], argv[4], BSIZE-2);
	buf[BSIZE-1] = 0;
		// request consists of P command and file name;
		// make sure file name is null-terminated
	if (write(sock, buf, strlen(buf)+1) == -1) {
		perror("write");
		exit(1);
	}
	// get response from server
	if ((ret = read(sock, buf, BSIZE)) == -1) {
		perror("read from server");
		exit(1);
	}
	if (ret == 0) {
		// shouldn't happen ...
		fprintf(stderr, "unexpected end of file\n");
		exit(1);
	}
	if (buf[0] == 'B') {
		// server says no and supplies reason
		buf[ret] = 0;
		fprintf(stderr, "error from server: %s\n", &buf[1]);
		exit(1);
	}
	if (buf[0] != 'G') {
		// shouldn't happen ...
		fprintf(stderr, "unexpected response from server: %c\n", buf[0]);
		exit(1);
	}
	// good response
	while ((ret = read(sourceFD, buf, BSIZE)) > 0) {
		// get local file contents and send to server
		if (write(sock, buf, ret) == -1) {
			perror("write to server");
			exit(1);
		}
	}
	if (ret == -1) {
		perror("read from local file");
		exit(1);
	}
	return 0;
}
