#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <fcntl.h>
#include "display.h"
#include "support.h"
#define BUFFER_SIZE 256

void run_memtop(void) {
    //TODO: initialization for read and select
    fd_set rd;
    struct timeval timeout;
    int bytes;
    char buf[BUFFER_SIZE];
    // Should I put this code insize FD_ISSET or where?
    // With
    if (fcntl(STDIN_FILENO,F_SETFL,O_NONBLOCK) == -1) {
                perror("fcntl()\n");
    }
    //to avoid unused variable warning. You may remove it once you use buf.
    buf[0] = 0;
    while(1) {
        //TODO: call select, read, and process_data
        FD_ZERO(&rd);               // Clear the fd set
        FD_SET(STDIN_FILENO,&rd);   // Fill the fd set
        timeout.tv_sec  = 0;        // Waiting time is 0
        timeout.tv_usec = 0;         
        if (select(1,&rd,NULL,NULL,&timeout) == -1) {
            perror("select()");
        }
        // Check if STDIN_FILENO ready or not 
        if (FD_ISSET(STDIN_FILENO,&rd)) {
            // read up to BUFFER_SIZE bytes
            
            if ((bytes = read(STDIN_FILENO,buf,BUFFER_SIZE)) == -1) {
                perror("read()\n");
            }
            if (process_input(buf,bytes) != 0) {
                break;
            }
        }

        //read proc filesystem
        int n_procs = 0;
        process_t *proc_arr = collect_data(&n_procs);

        if (proc_arr == NULL) {
            continue;
        }

        sort_data(proc_arr, n_procs);
        //update display
        display_data(proc_arr, n_procs);
                //free proc_data
        free(proc_arr);
    }
}

int main(int argc, char *argv[]) {
    display_init();
    run_memtop();
    display_finish();
    return 0;
}

