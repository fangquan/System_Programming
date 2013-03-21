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

unsigned int nbytes;

int main(int argc, char *argv[]) {
	void relay(int, int, int, int);
	void source(int);
	void sink(int);
	int leftwardIn[2];
	int leftwardOut[2];
	int rightwardIn[2];
	int rightwardOut[2];

	if (argc != 2) {
		fprintf(stderr, "Usage: Select nbytes\n");
		exit(1);
	}
	nbytes = atoi(argv[1]);

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

	while(rsize > 0) {
		if ((ret = read(fd, bp, rsize)) == -1) {
			return -1;
		}
		if (ret == rsize)
			break;
		if (ret == 0) {
			if (rsize == size) {
				// return 0 only if this is the first pass through the loop
				return 0;
			} else {
				// return total number of bytes read
				return (int)bp - (int)buf;
			}
		}
		rsize -= ret;
		bp += ret;
	}
	return size;
}

void relay(int leftwardIn, int leftwardOut, int rightwardIn, int rightwardOut) {
	fd_set rd, wr;
	int left_read = 1, right_write = 0;
	int right_read = 1, left_write = 0;
	int sizeLR, sizeRL, wret;
	char bufLR[BSIZE], bufRL[BSIZE];
	char *bufpR, *bufpL;
	int maxFDL = (leftwardOut>leftwardIn)?leftwardOut:leftwardIn;
	int maxFDR = (rightwardOut>rightwardIn)?rightwardOut:rightwardIn;
	int maxFD = ((maxFDL>maxFDR)?maxFDL:maxFDR)+1;
	int moreL = 1, moreR = 1;

	while(moreL || moreR) {
		FD_ZERO(&rd);
		FD_ZERO(&wr);
		if (left_read && moreL)
			FD_SET(leftwardIn, &rd);
		if (right_read && moreR)
			FD_SET(rightwardIn, &rd);
		if (left_write)
			FD_SET(leftwardOut, &wr);
		if (right_write)
			FD_SET(rightwardOut, &wr);

		select(maxFD, &rd, &wr, 0, 0);

		if (FD_ISSET(leftwardIn, &rd)) {
			if ((sizeLR = read(leftwardIn, bufLR, BSIZE)) > 0) {
				left_read = 0;
				right_write = 1;
				bufpR = bufLR;
			} else
				moreL = 0;
		}
		if (FD_ISSET(rightwardIn, &rd)) {
			if ((sizeRL = read(rightwardIn, bufRL, BSIZE)) > 0) {
				right_read = 0;
				left_write = 1;
				bufpL = bufRL;
			} else 
				moreR = 0;
		}
		if (FD_ISSET(rightwardOut, &wr)) {
			if ((wret = write(rightwardOut, bufpR, sizeLR)) == sizeLR) {
				left_read = 1;
				right_write = 0;
			} else {
				sizeLR -= wret;
				bufpR += wret;
			}
		}
		if (FD_ISSET(leftwardOut, &wr)) {
			if ((wret = write(leftwardOut, bufpL, sizeRL)) == sizeRL) {
				right_read = 1;
				left_write = 0;
			} else {
				sizeRL -= wret;
				bufpL += wret;
			}
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