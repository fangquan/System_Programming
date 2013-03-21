#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <signal.h>
#define NAME	"/home/qfang/server"

void deleteSocket(int sig) {
	unlink(NAME);
	exit(0);
}

main( ) {
  struct sockaddr_un	 sock_name;
  int fd, len;
/* Step 1: create socket in UNIX domain for datagram 
	communication.  The third argument specifies the
	protocol, but since there's only one such protocol in
	this domain, it's set to zero */
	if ((fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	/* Step 2: set up a sockaddr structure to contain the
	   name we want to assign to the socket */
	sock_name.sun_family = PF_UNIX;
	strcpy(sock_name.sun_path, NAME);
	len = strlen(NAME) + sizeof(sock_name.sun_family);


	/* Step 3: bind the name to the socket */
	if (bind(fd, (struct sockaddr *)&sock_name, len) < 0) {
		perror("bind");
		exit(1);
	}
	signal(SIGINT, deleteSocket);

	while (1) {
		char buf[1024];
		struct sockaddr_un from_addr;
		int from_len = sizeof(from_addr);
		int msg_size;

		/* Step 4: receive message from client */

		if ((msg_size = recvfrom(fd, buf, 1024, 0,(struct sockaddr *)&from_addr, &from_len)) < 0) {
			perror("recvfrom");
			exit(1);
		}
		buf[msg_size] = 0;
		printf("message from %s:\n%s\n", from_addr.sun_path,
			buf);

		/* Step 5: respond to client */
		if (sendto(fd, "thank you", 9, 0,(const struct sockaddr *)&from_addr,from_len) < 0) {
			perror("sendto");
			exit(1);
		}
	}
}
