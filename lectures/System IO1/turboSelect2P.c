#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

#define BSIZE (1024)		// minimum size for I/O
#define PCBSIZE (10*BSIZE)	// size of buffer
#define BBSIZE (BSIZE*8)	// transfer size used by source and sink processes

typedef struct pc {
	int done;
	int pblocked;
	int cblocked;
	int occupied;
	int empty;
	int nextin;
	int nextout;
	int descriptors[2];
	int eof;
	int needRead;
	int needWrite;
	char buf[PCBSIZE];
} pc_t;

void pc_init(pc_t *pc, int in, int out) {
	pc->occupied = 0;
	pc->empty = PCBSIZE;
	pc->nextin = pc->nextout = 0;
	pc->done = 0;
	pc->eof = 0;
	pc->cblocked = 0;
	pc->pblocked = 0;
	pc->descriptors[0] = in;
	pc->descriptors[1] = out;
}

#define pready(pc) (!pc->needRead && (pc->empty > BSIZE) && !pc->eof)
#define cready(pc) (!pc->needWrite && ((pc->occupied > BSIZE) || (pc->eof && pc->occupied > 0)))

void producer(pc_t *pc) {
	int size;
	int tsize;

	pc->needRead = 0;
	if (pc->eof || pc->pblocked)
		return;

	while(1) {
		if (pc->empty < BSIZE) {
			// wait till at least BSIZE bytes free in buffer
			// pthread_cond_wait(&pqueue, &mut);
			pc->pblocked = 1;
			assert(!pc->cblocked);
			return;
		}
		tsize = pc->empty;
			// read as much as buffer will hold
		if (tsize+pc->nextin > PCBSIZE) {
			// transfer wraps around buffer
			struct iovec iov[2];
			int tlen1 = PCBSIZE-pc->nextin;
			int tlen2 = tsize-tlen1;
			iov[0].iov_base = &pc->buf[pc->nextin];
			iov[0].iov_len = tlen1;
			iov[1].iov_base = &pc->buf[0];
			iov[1].iov_len = tlen2;
			if ((size = readv(pc->descriptors[0], iov, 2)) == -1) {
				if (errno == EAGAIN) {
					pc->needRead = 1;
					return;
				}
				perror("readv");
				exit(1);
			}
		} else {
			if ((size = read(pc->descriptors[0], &pc->buf[pc->nextin], tsize)) == -1) {
				if (errno == EAGAIN) {
					pc->needRead = 1;
					return;
				}
				perror("read");
				exit(1);
			}
		}
		if (size == 0) {
			pc->eof = 1;
			pc->cblocked = 0;
			//pthread_cond_signal(&cqueue);
			return;
		}
		pc->empty -= size;
		pc->occupied += size;
		pc->cblocked = 0;
		//pthread_cond_signal(&cqueue);
		pc->nextin += size;
		pc->nextin %= PCBSIZE;
	}
}

void consumer(pc_t *pc) {
	int size;
	int tsize;

	pc->needWrite = 0;
	if (pc->done || pc->cblocked)
		return;

	while(1) {
		if ((pc->occupied < BSIZE) && !pc->eof) {
			// wait till at least BSIZE bytes in buffer or all done
			// pthread_cond_wait(&cqueue, &mut);
			pc->cblocked = 1;
			assert(!pc->pblocked);
			return;
		}
		tsize = pc->occupied;
			// write as much as buffer now contains
		if (tsize == 0) {
			assert(pc->eof);
			break;
		}
		if (tsize+pc->nextout > PCBSIZE) {
			// transfer wraps around buffer
			struct iovec iov[2];
			int tlen1 = PCBSIZE-pc->nextout;
			int tlen2 = tsize-tlen1;
			iov[0].iov_base = &pc->buf[pc->nextout];
			iov[0].iov_len = tlen1;
			iov[1].iov_base = &pc->buf[0];
			iov[1].iov_len = tlen2;
			if ((size = writev(pc->descriptors[1], iov, 2)) == -1) {
				if (errno == EAGAIN) {
					pc->needWrite = 1;
					return;
				}
				perror("writev");
				exit(1);
			}
		} else {
			if ((size = write(pc->descriptors[1], &pc->buf[pc->nextout], tsize)) == -1) {
				if (errno == EAGAIN) {
					pc->needWrite = 1;
					return;
				}
				perror("write");
				exit(1);
			}
		}
		pc->occupied -= size;
		if (pc->eof && pc->occupied == 0)
			break;
		pc->empty += size;
		pc->pblocked = 0;
		//pthread_cond_signal(&pqueue);
		pc->nextout += size;
		pc->nextout %= PCBSIZE;
	}
	pc->done = 1;
}

unsigned int nbytes;

int main(int argc, char *argv[]) {
	void relay(int, int);
	void source(int);
	void sink(int);
	int leftwardIn[2];
	int leftwardOut[2];
	int rightwardIn[2];
	int rightwardOut[2];

	if (argc != 2) {
		fprintf(stderr, "Usage: turboSelect2P nbytes\n");
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

	if (fork() == 0) {
		close(rightwardIn[0]);
		close(rightwardOut[1]);
		relay(leftwardIn[0], leftwardOut[1]);
		exit(0);
	}

	if (fork() == 0) {
		close(leftwardIn[0]);
		close(leftwardOut[1]);
		relay(rightwardIn[0], rightwardOut[1]);
		exit(0);
	}


	close(leftwardIn[0]);
	close(leftwardOut[1]);
	close(rightwardIn[0]);
	close(rightwardOut[1]);

	while(wait(0) != -1)
		;

	return(0);
}

void relay(int In, int Out) {
	fd_set rd, wr;
	int maxFD = ((Out>In)?Out:In)+1;

	if (fcntl(In, F_SETFL, O_NONBLOCK) == -1) {
		perror("fcntl");
		exit(1);
	}

	if (fcntl(Out, F_SETFL, O_NONBLOCK) == -1) {
		perror("fcntl");
		exit(1);
	}


	pc_t *pc = (pc_t *)malloc(sizeof(pc_t));

	pc_init(pc, In, Out);

	while (!pc->done) {
		// event loop
		int readok = 0;
		int writeok = 0;

		FD_ZERO(&rd);
		FD_ZERO(&wr);
		FD_SET(In, &rd);
		FD_SET(Out, &wr);

		// determine which file descriptors are ready for reading and writing
		if (select(maxFD, &rd, &wr, 0, 0) == -1) {
			perror("select");
			exit(1);
		}

		if (FD_ISSET(In, &rd))
			readok = 1;

		if (FD_ISSET(Out, &wr))
			writeok = 1;

		do {
			// call pc routines if appropriate file descriptors are ready
			if (readok) {
				producer(pc);
			}
			if (writeok) {
				consumer(pc);
			}
		} while ((readok && pready(pc)) || 
				(writeok && cready(pc)));
		readok = 0;
		writeok = 0;
	}
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