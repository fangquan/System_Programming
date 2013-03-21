/* This program reads command line arguments
 * and sends the corresponding signals to the specified PID */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* Main function */
int main(int argc, char** argv) {
	// TODO: Parse command line arguments and send the specified signals
	// Pause briefly between signals using sleep(), usleep(), or nanosleep()
        if ( argc != 3)
	{ printf ("Usage: ./knocler pid czq\n"); return 0;}

        pid_t pid = atoi(argv[1]);
        char *command = argv[2];
        for (int i = 0; i < strlen(command); i++) {
            if (command[i] == 'c') {
                sleep(2);
                kill(pid,SIGINT);
            }
            if (command[i] == 'z') {
                sleep(2);
                kill(pid,SIGTSTP);
            }
            if (command[i] == 'q') {
                sleep(2);
                kill(pid,SIGQUIT);
            }
        }
}
