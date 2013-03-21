#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

#define SNAME "/home/qfang/server"
#define CNAME "/home/qfang/client"

void deleteSocket() {
	unlink(CNAME);
	exit(0);
}

int main( ) {
	struct sockaddr_un server_name;
	struct sockaddr_un client_name;
	int fd, server_len, client_len;

	/* Step 1: create socket in UNIX domain for datagram
	   communication.  The third argument specifies the
	   protocol, but since there's only one such protocol
	   in this domain, it's set to zero */
	if ((fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	/* Step 2: set up a sockaddr structure to contain the
	   name we want to assign to the socket */
	client_name.sun_family = PF_UNIX;
	strcpy(client_name.sun_path, CNAME);
	client_len = strlen(CNAME) + sizeof(client_name.sun_family);

	/* Step 3: bind the name to the socket */
	if (bind(fd, (struct sockaddr *)&client_name,client_len) < 0) {
		perror("bind");
		exit(1);
	}

	/* Step 4: set up servers name */
	server_name.sun_family = PF_UNIX;
	strcpy(server_name.sun_path, SNAME);
	server_len = strlen(SNAME) + sizeof(server_name.sun_family);
	
	// Call the unlink function to remove the specified file
	// When you bind a name to to unix_domian socket, the name is actually created in the file system
	signal(SIGINT, deleteSocket);

	while (1) {
		char buf[1024];
		int msg_size;

		if (fgets(buf, 1024, stdin) == 0)
			break;

		/* Step 5: send data to server */
		if (sendto(fd, buf, strlen(buf), 0,(const struct sockaddr *)&server_name,server_len) < 0) {
			perror("sendto");
			deleteSocket();
			exit(1);
		}

		/* Step 6: receive response from server */
		/* Why this 	*/
		if ((msg_size = recvfrom(fd, buf, 1024, 0, 0,0)) < 0) {
			perror("recvfrom");
			deleteSocket();
			exit(1);
		}
		buf[msg_size] = 0;
		printf("Server says: %s\n", buf);
	}
	deleteSocket();
	return(0);
}
