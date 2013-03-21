#include <stdio.h>
#include <stdlib.h>
#define HowMany 17

int main (int argc, char** argv) {
	int i;
	int stop = atoi(argv[1]);	
	for (i=0;i<stop;i++) {
		printf ("%d\n",rand()%100);
	}
	exit(0);
}


