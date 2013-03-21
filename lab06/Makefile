CC = gcc
CFLAGS = -Wall -std=c99 -D_GNU_SOURCE


all: siglab knocker

siglab: siglab.c
	$(CC) $(CFLAGS) siglab.c -o siglab

knocker: knocker.c
	$(CC) $(CFLAGS) knocker.c -o knocker

clean:
	rm -rf siglab knocker
