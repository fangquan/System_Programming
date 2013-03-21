#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#define MAX(x,y) ((x) > (y) ? x : y)
#define BUFFER 1024

int process_input(char *buffer, uint16_t num_stations, int sock);

int main(int argc, char *argv[]) {
	struct sockaddr_in server_addr, client_addr;
	int sock;
        int udpsock;
	struct hostent *hostinfo;

	char buf[BUFFER];
	if (argc != 4) {
		fprintf(stderr, "Usage: snow_client servername serverport udpport\n");
		exit(1);
	}

	// Step1, set up socket for TCP
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket");
            exit(1);
	}
        
        // set up socket for UDP
        // this UDP port only recvfrom, don't sendto server
        if ((udpsock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
            perror("set UDP socket");
            exit(1);
        }

        // bind the UDP socket
	client_addr.sin_family = PF_INET;
        client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        client_addr.sin_port = htons(atoi(argv[3]));
        if (bind(udpsock,(struct sockaddr *) &client_addr, sizeof(client_addr)) < 0) {
            perror("bind UDP socket");
            exit(1);
        }

        // Step 2: find the internet address of the server
	if ((hostinfo = gethostbyname(argv[1])) == 0) {
		fprintf(stderr, "Host %s does not exist\n", argv[1]);
		exit(1);
	}
        memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	memcpy(&server_addr.sin_addr, hostinfo->h_addr_list[0],hostinfo->h_length); //copy to the internet address
	server_addr.sin_port = htons(atoi(argv[2]));// the server port

	// Step 3: connect to the server
	if (connect(sock, (struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
		perror("connect");
		exit(1);
	}

        // Send HELLO to server
        uint8_t command_type = 0;
        uint16_t udpport = atoi(argv[3]);
        udpport = htons(udpport);
        // convert uint16_t from host byte to network byte order
        memcpy(buf,&command_type,sizeof(uint8_t));
        memcpy(buf+sizeof(uint8_t), &udpport,sizeof(uint16_t));
        write(sock,buf,sizeof(uint8_t)+sizeof(uint16_t));
        
        // Receive WELCOME from server
        uint8_t reply_type;
        uint16_t num_stations;
        int msg_size;
        msg_size = read(sock, buf, sizeof(buf));
        memcpy(&reply_type,buf,sizeof(uint8_t));
        memcpy(&num_stations,buf+sizeof(uint8_t),sizeof(uint16_t));
        num_stations = ntohs(num_stations);
        // convert uint16_t from network byte order to host byte
        if (reply_type == 0) {
                fprintf(stderr,"WELLCOME\nreply_type: %d\nstation_number: %d\n",reply_type,num_stations);
        }

        fd_set rd;
        struct timeval timeout;
        while (1) {
            FD_ZERO(&rd);               // Clear the fd set
            FD_SET(STDIN_FILENO,&rd);   // Fill the fd set
            FD_SET(sock,&rd);
            FD_SET(udpsock,&rd);
            timeout.tv_sec  = 0;        // Waiting time is 0
            timeout.tv_usec = 0;
            if (select(MAX(sock,udpsock)+1,&rd,NULL,NULL,&timeout) == -1) {
                perror("select()");
            }
            // Check if STDIN_FILENO ready or not 
            if (FD_ISSET(STDIN_FILENO,&rd)) {
                char buf[BUFFER];
                memset(buf,0,BUFFER);
                int  bytes;
                if ((bytes = read(STDIN_FILENO,buf,BUFFER)) == -1) {
                    perror("STDIN_FILENO\n");
                }
                process_input(buf,num_stations,sock);
            }
            
            // TCP socket
            if (FD_ISSET(sock,&rd)) {
                char buf[BUFFER];
                if ((msg_size = read(sock,buf,BUFFER)) < 0) {
                    perror("read()");
                    exit(1);
                }
                // Received annoucement from the server
                int reply_type = buf[0];
                int song_name_size = buf[1];
                char song_name[song_name_size];
                memcpy(song_name, buf+2,song_name_size);
                song_name[song_name_size] = '\0';
		fprintf(stderr,"reply_type: %d\nsong_name_size: %d\n%s\n",reply_type,song_name_size,song_name);
            }
            
            // UDP socket
            if (FD_ISSET(udpsock,&rd)) {
                char buf[BUFFER];
                if ((msg_size = read(udpsock,buf,BUFFER)) < 0)  {
                    perror("read()");
                    exit(1);
                }
                write(STDOUT_FILENO,buf,msg_size);
            }
	}
	return 0;
}

int process_input(char* buf,uint16_t num_stations, int sock) {
    buf[strlen(buf)-1] = '\0';
    int len = strlen(buf);
    int wholedigit = 1;
    for (int i=0; i<len; i++) {
        if (isdigit(buf[i]) == 0) {
            wholedigit = 0;
            break;
        }
    }
    // "q" or "quit"
    if ( (strcmp(buf,"q") == 0) || (strcmp(buf,"quit") == 0)) {
        exit(0);
    }

    // blankline, igonred
    else if (len == 0) {
        return 0;
    }

    // integer onits own lines
    if (wholedigit)  {
        // Send SetStation to server
        int station = atoi(buf);
        if (station >= num_stations) {
            char response[] = "Invalid station";
            write(STDERR_FILENO,response,sizeof(response));
            return 0;
        }
        uint8_t  command_type   = 1;
        uint16_t station_number = station;
        station_number = htons(station_number);
        // convert uint16_t from host byte to network byte order
        memcpy(buf,&command_type,sizeof(uint8_t));
        memcpy(buf+sizeof(uint8_t), &station_number,sizeof(uint16_t));
        write(sock,buf,sizeof(uint8_t)+sizeof(uint16_t));
        return 0;
    }
    else
    {
        write(sock,buf,strlen(buf));
        // Received annoucement from the server
        char buf[BUFFER];
        if (read(sock,buf,BUFFER) < 0) {
            perror("read()");
            exit(1);
        }
        uint8_t reply_type = buf[0];
        uint8_t reply_string_size = buf[1];
        char reply_string[reply_string_size];
        memcpy(reply_string, buf+2,reply_string_size);
        reply_string[reply_string_size] = '\0';
        fprintf(stderr,"reply_type: %d\nreply_string_size: %d\n%s\n",reply_type,reply_string_size,reply_string);
    }
    return 0;
}








