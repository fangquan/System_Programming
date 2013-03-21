#include<stdio.h>

int sum(int a, int b) {
	int t = a+b;
	return t;
}

void swap (int *xp, int *yp) {
	int t0 = *xp;
	int t1 = *yp;
	*xp = t1;
	*yp = t0;
}



int main (int argc, char** argv) {
	
	int a;
	a = sum(1,2);
	int b = 4;
	printf ("%d\t%d\n",a,b);	
	swap(&a,&b);
	printf ("%d\t%d\n",a,b);	


	return 0;
}
