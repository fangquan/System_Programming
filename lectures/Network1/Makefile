CC = gcc
CFLAGS = -g -std=c99

EXECS = tcpClient tcpServer udpClient udpServer

all: $(EXECS)

tcpClient: tcpClient.c
	$(CC) $(CFLAGS) tcpClient.c -o tcpClient

tcpServer: tcpServer.c 
	$(CC) $(CFLAGS) tcpServer.c -o tcpServer

udpClient: udpClient.c
	$(CC) $(CFLAGS) udpClient.c -o udpClient

udpServer: udpServer.c
	$(CC) $(CFLAGS) udpServer.c -o udpServer


.PHONY: clean
clean:
	rm -rvf *.o $(EXECS)

