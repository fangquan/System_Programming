#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char** argv) {
	pid_t pid;
	pid_t ParentPid = getpid();	

	pid = fork();
	if (pid == 0){
		printf("In Child Process, %d, %d, %d\n",pid,ParentPid,getpid());
	}
	printf("In Parent Process: %d, %d, %d\n",pid,ParentPid,getpid());
	return 0;
}

