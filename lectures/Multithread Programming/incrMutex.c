#include <stdio.h>
#include <pthread.h>

#define NTHREADS	4
#define NITERATIONS	1000000

volatile long count;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

main() {
	pthread_t thread[NTHREADS];
	void *thread_proc(void *);
	int i;

	for (i = 0; i < NTHREADS; i++) {
		pthread_create(
		&thread[i],
		0,
		thread_proc,
		(void *) i);
	}

	for (i = 0; i < NTHREADS; i++) {
		pthread_join(thread[i], 0);
	}
}

void *thread_proc(void *arg) {
	int tid = (int)arg;
	long i;

	for (i = 0; i < NITERATIONS; i++) {
		pthread_mutex_lock(&mut);
		count++;
		pthread_mutex_unlock(&mut);
	}
	printf("Thread %d: %d\n", tid, count);
	return(0);
}
