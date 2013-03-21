#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int);
void sending_signal_kill_function ();

int main() {
	//sending_signal_kill_function ();
	signal(SIGINT,handler);
	while (1)
	;
	return 0;
}

// signal handler when receiving ctrl+c
void handler(int signo) {
	printf("I received signal %d." "Whoopee!!\n",signo);
	exit(0);
}

void sending_signal_kill_function () {
	pid_t pid;
	if ((pid = fork()) == 0) {
		pause();
		printf("control should never reach here !\n");
		exit(0);	
	}
	kill (pid,SIGKILL);
	exit(0);
}
