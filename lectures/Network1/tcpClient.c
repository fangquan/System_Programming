#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char *argv[]) {
	struct sockaddr_in server_addr;
	int sock;
	struct hostent *hostinfo;

	char buf[1024];
	if (argc != 3) {
		fprintf(stderr, "Usage: client host port\n");
		exit(1);
	}

	// set up socket for TCP
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
	// Binding for TCP is optional

	// Step 2: find the internet address of the server
	if ((hostinfo = gethostbyname(argv[1])) == 0) {
		fprintf(stderr, "Host %s does not exist\n", argv[1]);
		exit(1);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	memcpy(&server_addr.sin_addr, hostinfo->h_addr_list[0],hostinfo->h_length);
	server_addr.sin_port = htons(atoi(argv[2]));

	// Step 3: connect to the server
	if (connect(sock, (struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
		perror("connect");
		exit(1);
	}

	// Step 4: send data to the server
	while(fgets(buf, 1024, stdin) != 0) {
		if (write(sock, buf, strlen(buf)) < 0) {
			perror("write");
			exit(1);
		}
	}
	return(0);
}
