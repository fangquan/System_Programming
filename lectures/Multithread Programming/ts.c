#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main(int argc, char *argv[]) {
	int nthreads;
	int niters;
	int i;
	int val;
	pthread_t thread;
	void *tfunc(void *);

	if (argc != 3) {
		fprintf(stderr, "Usage: ts nthreads iterations\n");
		exit(1);
	}

	nthreads = atoi(argv[1]);
	niters = atoi(argv[2]);
	val = niters/nthreads;

	for (i=0; i<nthreads; i++) {
		int ret;
		if ((ret = pthread_create(&thread, 0, tfunc, (void *)val)) != 0) {
			fprintf(stderr, "pthread_create: %s\n", strerror(ret));
			exit(1);
		}
	}

	pthread_exit(0);

	return(0);
}

void *tfunc(void *arg) {
	int n = (int)arg;
	int i;
	int j;
	volatile int x;

	for (i=0; i<n; i++) {
		x = 0;
		for (j=0; j<1000; j++)
			x = x+j;
	}
	return(0);
}
