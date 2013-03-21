#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char** argv) {
	printf ("%d\n",getpid());
	printf ("%d\n",getppid());	
	
	pid_t pid;
	int x = 1;
	pid = fork();
	if (pid == 0){
		printf("pid: pid=%d\n",pid);
		printf("Child: x=%d\n",++x);
		close(1);
		if (open("/home/qfang/course/cs033/Shell/output","O_WRONLY") == -1) {
			perror("/home/qfang/course/cs033/Shell/output");
			exit(1);	
		}
		execl("./random","random","12",(void*)0);	
		// execl call once, but never returns, except when there is an error 
		exit(0);	
	}
	printf("pid: pid=%d\n",pid);
	printf("parent: x=%d\n",--x);
	exit(0);
}


