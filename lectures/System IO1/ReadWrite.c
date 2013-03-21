#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>

#define BSIZE (1024)

long long nbytes;

int main(int argc, char *argv[]) {
	void relay(int, int, int, int);
	void source(int);
	void sink(int);
	int leftwardIn[2];
	int leftwardOut[2];
	int rightwardIn[2];
	int rightwardOut[2];

	if (argc != 2) {
		fprintf(stderr, "Usage: ReadWrite nbytes\n");
		exit(1);
	}
	nbytes = atoll(argv[1]);
	
	// 4 pipes
	if (pipe(leftwardIn) == -1) {
		perror("pipe");
		exit(1);
	}

	if (pipe(leftwardOut) == -1) {
		perror("pipe");
		exit(1);
	}

	if (pipe(rightwardIn) == -1) {
		perror("pipe");
		exit(1);
	}

	if (pipe(rightwardOut) == -1) {
		perror("pipe");
		exit(1);
	}

	if (fork() == 0) {
		// leftward source: writes to leftwardIn[1]
		// leftwardIn[1] is the stdout from leftward source
		close(rightwardIn[0]);
		close(rightwardIn[1]);
		close(rightwardOut[0]);
		close(rightwardOut[1]);
		close(leftwardOut[0]);
		close(leftwardOut[1]);
		close(leftwardIn[0]);
		source(leftwardIn[1]);
		exit(0);
	}
	if (fork() == 0) {
		// rightward source: writes to rightwardIn[1]
		// rightwardIn[1] is the stdout from rightward source
		close(rightwardIn[0]);
		close(rightwardOut[0]);
		close(rightwardOut[1]);
		close(leftwardOut[0]);
		close(leftwardOut[1]);
		close(leftwardIn[0]);
		close(leftwardIn[1]);
		source(rightwardIn[1]); 
		exit(0);
	}
	if (fork() == 0) {
		// leftward sink: reads from leftwardOut[0]
		// leftwardOut[0] is the stdin to leftward sink
		close(rightwardIn[0]);
		close(rightwardIn[1]);
		close(rightwardOut[0]);
		close(rightwardOut[1]);
		close(leftwardOut[1]);
		close(leftwardIn[0]);
		close(leftwardIn[1]);
		sink(leftwardOut[0]);
		exit(0);
	}
	if (fork() == 0) {
		// rightward sink: reads from rightwardOut[0]
		// rightwardOut[0] is the stdin to rightward sink
		close(rightwardIn[0]);
		close(rightwardIn[1]);
		close(rightwardOut[1]);
		close(leftwardOut[0]);
		close(leftwardOut[1]);
		close(leftwardIn[0]);
		close(leftwardIn[1]);
		sink(rightwardOut[0]);
		exit(0);
	}
	
	
	close(leftwardIn[1]);
	close(leftwardOut[0]);
	close(rightwardIn[1]);
	close(rightwardOut[0]);

	relay(leftwardIn[0], leftwardOut[1], rightwardIn[0], rightwardOut[1]);

	close(leftwardIn[0]);
	close(leftwardOut[1]);
	close(rightwardIn[0]);
	close(rightwardOut[1]);

	while(wait(0) != -1) 
		;
 
	return(0);
}

int Write(int fd, void *buf, size_t size) {
	// repeatedly calls write until all size bytes are written
	size_t wsize = size;
	int ret;
	char *bp = buf;

	while(wsize > 0) {
		if ((ret = write(fd, bp, wsize)) == -1) {
			return -1;
		}
		if (ret == wsize)
			break;
		assert((ret < wsize) && (ret > 0));
		wsize -= ret;
		bp += ret;
	}
	return size;
}

int Read(int fd, void *buf, size_t size) {
	// repeatedly calls read until all size bytes are read or EOF
	size_t rsize = size;
	int ret;
	char *bp = buf;
	int count = 0;

	while(rsize > 0) {
		if ((ret = read(fd, bp, rsize)) <= -1) {
			return -1;
		}
		count += ret;
		if ((ret == rsize) || (ret == 0))
			break;
		rsize -= ret;
		bp += ret;
	}
	return count;
}

void relay(int leftwardIn, int leftwardOut, int rightwardIn, int rightwardOut) {
	char buf[BSIZE];
	int ldone = 0;
	int rdone = 0;
	int size;
	int wsize;
	int wret;
	char *bp;

	while(!(ldone && rdone)) {
		if (!ldone)
			if ((size = Read(leftwardIn, buf, BSIZE)) <= -1) {
				perror("relay: leftward read");
				exit(1);
			}
			if (size == 0) {
				ldone = 1;
			} else if (Write(leftwardOut, buf, size) == -1) {
				perror("relay: leftward write");
				exit(1);
			}
		if (!rdone)
			if ((size = Read(rightwardIn, buf, BSIZE)) <= -1) {
				perror("relay: rightward read");
				exit(1);
			}
			if (size == 0) {
				rdone = 1;
			} else if (Write(rightwardOut, buf, size) == -1) {
				perror("relay: rightward write");
				exit(1);
			}
	}
}

#define BBSIZE (BSIZE*8)

void source(int fd) {
	unsigned char buf[BBSIZE];
	long long i;
	for (i=0; i<nbytes; i+=BBSIZE) {
		buf[0] = (unsigned char)(i/BBSIZE);
			// put data in this byte so we can check that things are transferred in correct order
		int amtLeft = nbytes-i;
		if (amtLeft > BBSIZE)
			amtLeft = BBSIZE;
		if (Write(fd, buf, amtLeft) == -1) {
			perror("source");
			exit(1);
		}
	}
}

void sink(int fd) {
	unsigned char buf[BBSIZE];
	long long count = 0;
	int ret;

	while (1) {
		if ((ret = Read(fd, buf, BBSIZE)) == -1) {
			perror("sink");
			exit(1);
		}
		if (ret == 0)
			break;

		// check data-containing byte
		if (buf[0] != (unsigned char)(count/BBSIZE)) {
			fprintf(stderr, "data received out of order; buf[0] = %d, count = %d\n", buf[0], count);
			exit(1);
		}
		count += ret;
	}
	if (count != nbytes)
		fprintf(stderr, "wrong amount of data received: %d\n", count);
}
