#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
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
		fprintf(stderr, "Usage: Epoll nbytes\n");
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
	int sizeLR=0, sizeRL=0, wret;
	char bufLR[BSIZE], bufRL[BSIZE];
	char *bufpL, *bufpR;
	int moreL = 1, moreR = 1;
	extern int errno;
	int efd;
	struct epoll_event ev[4];
	int lreadok=0, lwriteok=0, rreadok=0, rwriteok=0;
	int lreading = 1, rreading = 1;

	if ((efd = epoll_create(2)) == -1) {
		perror("epoll_create");
		exit(1);
	}

	ev[0].events = EPOLLIN|EPOLLET;
	ev[0].data.fd = leftwardIn;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, leftwardIn, &ev[0]) == -1) {
		perror("epoll_ctl");
		exit(1);
	}
	ev[1].events = EPOLLOUT|EPOLLET;
	ev[1].data.fd = leftwardOut;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, leftwardOut, &ev[1]) == -1) {
		perror("epoll_ctl");
		exit(1);
	}
	ev[2].events = EPOLLIN|EPOLLET;
	ev[2].data.fd = rightwardIn;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, rightwardIn, &ev[2]) == -1) {
		perror("epoll_ctl");
		exit(1);
	}
	ev[3].events = EPOLLOUT|EPOLLET;
	ev[3].data.fd = rightwardOut;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, rightwardOut, &ev[3]) == -1) {
		perror("epoll_ctl");
		exit(1);
	}
	if (fcntl(leftwardIn, F_SETFL, O_NONBLOCK) == -1) {
		perror("fcntl");
		exit(1);
	}
	if (fcntl(leftwardOut, F_SETFL, O_NONBLOCK) == -1) {
		perror("fcntl");
		exit(1);
	}
	if (fcntl(rightwardIn, F_SETFL, O_NONBLOCK) == -1) {
		perror("fcntl");
		exit(1);
	}
	if (fcntl(rightwardOut, F_SETFL, O_NONBLOCK) == -1) {
		perror("fcntl");
		exit(1);
	}

	while (moreL || moreR) {
		int ndescs;
		int i;
		int more;

		if ((ndescs = epoll_wait(efd, ev, 4, -1)) == -1) {
			perror("epoll_wait");
			exit(1);
		}
		for (i=0; i<ndescs; i++) {
			int fd = ev[i].data.fd;
			if (fd == leftwardIn)
				lreadok = 1;
			else if (fd == leftwardOut)
				lwriteok = 1;
			else if (fd == rightwardIn)
				rreadok = 1;
			else if (fd == rightwardOut)
				rwriteok = 1;
			else {
				fprintf(stderr, "unknown file descriptor\n");
				exit(1);
			}
		}
		if (!moreL && lreadok) {
			lreadok = 0;
		}
		if (!moreR && rreadok) {
			rreadok = 0;
		}
		more = 1;
		while (more) {
			more = 0;
   			if (lreadok && lreading) {
   				sizeLR = read(leftwardIn, bufLR, BSIZE);
   				if (sizeLR == -1) {
   					if (errno == EAGAIN) {
   						lreadok = 0; // must poll before next read
   					} else {
   						perror("read");
   						exit(1);
   					}
   				} else {
   				if (sizeLR == 0) {
   					moreL = 0; // EOF
					lreadok = 0;
				} else {
					lreading = 0; // must write before next read
					bufpR = bufLR;
					if (sizeLR < BSIZE)
   						lreadok = 0; // must poll before next read
				}
			}
		}
		if (rreadok && rreading) {
   			sizeRL = read(rightwardIn, bufRL, BSIZE);
   			if (sizeRL == -1) {
   				if (errno == EAGAIN) {
   					rreadok = 0; // must poll before next read
   				} else {
   					perror("read");
   					exit(1);
   				}
   			} else {
   				if (sizeRL == 0) {
					moreR = 0; // EOF
					rreadok = 0;
				} else {
					rreading = 0; // must write before next read
					bufpL = bufRL;
					if (sizeRL < BSIZE)
   						rreadok = 0; // must poll before next read
				}
			}
		}
		if (rwriteok && !lreading) {
			if ((wret = write(rightwardOut, bufpR, sizeLR)) == -1) {
				if (errno == EAGAIN) {
					rwriteok = 0; // must poll before next write
				} else {
					perror("write");
					exit(1);
				}
			} else {
				assert(wret != 0);
				if ((sizeLR -= wret) == 0) {
					// all of buffer has been written
					lreading = 1; // must read before next write
					if (lreadok)
						more = 1;
				} else {
					bufpR += wret;
					rwriteok = 0; // must poll before next write
				}
			}
		}
		if (lwriteok && !rreading) {
			if ((wret = write(leftwardOut, bufpL, sizeRL)) == -1) {
				if (errno == EAGAIN) {
					lwriteok = 0; // must poll before next write
				} else {
					perror("write");
					exit(1);
				}
			} else {
				assert(wret != 0);
				if ((sizeRL -= wret) == 0) {
					// all of buffer has been written
					rreading = 1;
					if (rreadok)
						more = 1;
					} else {
						bufpL += wret;
						lwriteok = 0; // must poll before next write
					}
				}
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