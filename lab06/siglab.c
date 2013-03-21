#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

// Forward Declarations
int  install_handler(int sig, void (*handler)(int));
void sigint_handler(int sig);
void sigtstp_handler(int sig);
void sigquit_handler(int sig);
int  read_and_echo();

// Global variables
int time_sigint  = 0;
int time_sigtstp = 0;
int time_sigquit = 0;


/* main
 * Install the necessary signal handlers, then call read_and_echo().
 */
int main(int argc, char** argv) {
	sigset_t old;
	sigset_t full;
	sigfillset(&full);
        
	// Ignore signals while installing handlers
        // Previous value od the blocked bit vector is stored in old
        // If it's NULL, no save for the old blocked set
	sigprocmask(SIG_SETMASK, &full, &old);

        // Convert siglab process id into integer
        char sig_p[20] = {0x0};
        sprintf(sig_p,"%d",getpid());
        write(1,sig_p,sizeof(sig_p));
       	//Install signal handlers
	if(install_handler(SIGINT, &sigint_handler))
		perror("Warning: could not install handler for SIGINT");

	if(install_handler(SIGTSTP, &sigtstp_handler))
		perror("Warning: could not install handler for SIGTSTP");

	if(install_handler(SIGQUIT, &sigquit_handler))
		perror("Warning: could not install handler for SIGQUIT");

	// Restore signal mask to previous value
	sigprocmask(SIG_SETMASK, &old, NULL);
	read_and_echo();
	return 0;
}


/* install_handler
 * Installs a signal handler for the given signal
 * Returns 0 on success, -1 on error
 */
int install_handler(int sig, void (*handler)(int)) {
	// TODO: Use sigaction() to install the given function
	// as a handler for the given signal.
        // sa_mask specifies a mask of signals which should be blocked
        // during execution of the signal handler.
        struct sigaction action;
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        // Mask the signals 
        // Am I doing right ??
        sigemptyset(&action.sa_mask);
        sigaddset(&action.sa_mask,SIGINT);
        sigaddset(&action.sa_mask,SIGTSTP);
        sigaddset(&action.sa_mask,SIGQUIT);
        // NULL means previous action is not saved.
        if (sigaction(sig,&action,NULL) == 0){
            return 0;
        }
	return -1;
}

/* sigint_handler
 * Respond to SIGINT signal (CTRL-C)
 *
 * Argument: int sig - the integer code representing this signal
 */
void sigint_handler(int sig) {
    char *echo = "\nReceive signal: CTRL-C\n";
    write(1,echo,strlen(echo));
    time_sigint= time(NULL);
    char time[20] = {0x0};
    sprintf(time,"%d",time_sigint);
    write(1,time,sizeof(time));
}

/* sigtstp_handler 
 * Respond to SIGTSTP signal (CTRL-Z)
 *
 * Argument: int sig - the integer code representing this signal
 */
void sigtstp_handler(int sig) {
        char *echo = "\nReceive signal: CTRL-Z\n";
        write(1,echo,strlen(echo));
        time_sigtstp = time(NULL);
        char time[20] = {0x0};
        sprintf(time,"%d",time_sigtstp);
        write(1,time,sizeof(time));
}


/* sigquit_handler
 * Catches SIGQUIT signal (CTRL-\)
 *
 * Argument: int sig - the integer code representing this signal
 */
void sigquit_handler(int sig) {
        char *echo = "\nReceive signal: CTRL\\n";
        write(1,echo,strlen(echo));
        time_sigquit = time(NULL);
        char time[20] = {0x0};
        sprintf(time,"%d",time_sigquit);
        write(1,time,sizeof(time));
}

/* read_and_echo
 * Read input from stdin, echo to stdout.
 * Return 0 on EOF, -1 on error
 */
int read_and_echo() {
	// TODO: Read from stdin and write to stdout
	// Use the async-signal-safe syscalls read() and write()
    char buf[1024];
    while (1) {
        for (int i = 0; i< 1024; i++) {
        buf[i] = '\0';}
        // how to deal  with eof
        int bytes = read(0,buf,sizeof(buf));
        write(1,buf,bytes);        // Write to file  descriptor;
        // How to deal with EOF ??
        if ( bytes == 0 ) {
            return 0;
        }

        if ( (time_sigtstp - time_sigint > 1) && (time_sigtstp - time_sigint < 3) && (time_sigquit - time_sigtstp > 1) && (time_sigquit - time_sigtstp < 3))
        {
            exit(0);
        }

    }
    return -1;
}
