/*
 *shell part 2
 *Quan Fang
 *Nov/10/2012
 *qfang@brown.edu
 */
//#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include "jobs.h"
#include "basic_shell.h"
#define MAXARGS 1024
#define MAXLINE 1024

void read_and_echo();
int  install_handler(int sig, void (*handler)(int));
void sigint_handler(int sig);
void sigtstp_handler(int sig);
void sigquit_handler(int sig);
void child_handler(int sig);
int  builtin_command(char **argv);

int fg_global_pid = 0;
int jid = 0;
job_list_t *job_list;

int main(int argc, char** argv) {
        job_list = init_job_list();
        sigset_t old;
	sigset_t full;
	sigfillset(&full);
	// Ignore signals while installing handlers
        // Previous value od the blocked bit vector is stored in old
        // If it's NULL, no save for the old blocked set
	sigprocmask(SIG_SETMASK, &full, &old);
       	//Install signal handlers
	if(install_handler(SIGINT, &sigint_handler))
		perror("Warning: could not install handler for SIGINT");
	if(install_handler(SIGTSTP, &sigtstp_handler))
		perror("Warning: could not install handler for SIGTSTP");
	if(install_handler(SIGQUIT, &sigquit_handler))
		perror("Warning: could not install handler for SIGQUIT");
        if(install_handler(SIGCHLD, &child_handler))
            	perror("Warning: could not install handler for SIGCHLD");
	// Restore signal mask to previous value
	sigprocmask(SIG_SETMASK, &old, NULL);
        read_and_echo();
        return 0;
}

void read_and_echo() {
    while(1)
    {
        // Print Prompt, terminal I/O and take commands
        char cmdline[MAXLINE];
        int i;
        for (i = 0; i < MAXLINE; i++) {cmdline[i]='\0';}
        const char *path = "$";
        #ifndef NO_PROMPT
        write(STDOUT_FILENO, path, strlen(path));        // just print the dollar sign
	#endif
	int bytes = read(STDIN_FILENO, cmdline, sizeof (cmdline));  // Read from file descriptor
	if (bytes == 0) {
		exit(0);
	}
        // Evaluate, parse cmdline, and execute
        char *argv[MAXARGS];    // Argument list for execve()
        char buf[MAXLINE];      // Holds modified command line
        for (i = 0; i < MAXLINE; i++) {buf[i]='\0';}
        pid_t childpid;
        strcpy(buf, cmdline);
        // Inputfile, output and appendfile corresponding to '<', '>' and '>>'
        // Initialize them, in order to use strlen(inputfile) later
        char inputfile[MAXLINE];
        for (i = 0; i < MAXLINE; i++) { inputfile[i]='\0';}
        char outputfile[MAXLINE];
        for (i = 0; i < MAXLINE; i++) {outputfile[i]='\0';}
        char appendfile[MAXLINE];
        for (i = 0; i < MAXLINE; i++) {appendfile[i]='\0';}

        // return 1 if it's background job
        // 
        
        // return 1 if good redirection, return 0 if not good redirection
        if (!good_redirection(buf, inputfile, outputfile, appendfile))
        {continue;}
        parseline(buf, argv); // char **argv == char *argv[]
        if (argv[0] == NULL) {
            continue;
        }
        int argc = 0;
        while (argv[argc] != NULL)
        {
            argc++;
        }
        
        int IsBackground = background_job(argv);
        // jobs starts here
        if (!builtin_command(argv))
        {
            jid++;
            sigset_t set;
            if (sigemptyset(&set) == -1){
                perror(" ");
            }
            if (sigaddset(&set,SIGCHLD) == -1){
                perror(" ");
            }
            if (sigprocmask(SIG_BLOCK,&set,NULL) == -1) {
                perror(" ");
            }
            childpid = fork();        
            if (childpid == 0) {
                // setpgid(getpid(),getpid());
                // getpid() returns the real id of this child process,
                // and now each child hash its own unique pgid
                if (strlen(inputfile) != 0) {
                    close(0);
                    if (open(inputfile,O_RDONLY,0) < 0)
                    {perror(inputfile);}
                }
                if (strlen(outputfile) != 0) {
                    close(1);
                    if (open(outputfile,O_CREAT|O_TRUNC|O_RDWR,0666)<0)
                    {perror(outputfile);}
                }
                if (strlen(appendfile) != 0) {
                    close(1);
                    if(open(appendfile,O_APPEND|O_CREAT|O_RDWR,0666) < 0)
                    {perror(appendfile);}
                }
                
                execv(argv[0], argv);
                // We won't get here unless execv fails
                perror(argv[0]);
                exit(1);
            }
            else {
                // In the parent process
                int status;
                setpgid(childpid,childpid);
                if (IsBackground) {
                    add_job(job_list, jid, childpid, _STATE_RUNNING, argv[0]);
                    if (sigprocmask(SIG_UNBLOCK,&set,NULL) == -1) {
                        perror(" ");
                    }
                }
                else
                {
                    fg_global_pid = childpid;
                    add_job(job_list, jid, childpid, _STATE_RUNNING, argv[0]);         
                    //waitpid(-1,&status,WUNTRACED);
                    if (sigprocmask(SIG_UNBLOCK,&set,NULL) == -1) {
                        perror(" ");
                    }
                    while(fg_global_pid) {
                        sleep(1);
                    }
                }
            }
        }
    }
}

int builtin_command(char ** argv) {
        if (strcmp(argv[0], "exit") == 0) {
            cleanup_job_list(job_list);
            exit(0);
        }
        else if (strcmp(argv[0], "cd") == 0) {
            if (chdir(argv[1]) != 0) {
                perror(argv[1]);
            }
            return 1;
	}
        else if (strcmp(argv[0], "ln") == 0) {
            const char* existing = argv[1];
            const char* new      = argv[2];
            if (link(existing,new) != 0) { perror(" ");}
            return 1;
        }
        else if (strcmp(argv[0], "rm") == 0) {
            const char* file = argv[1];
            if (unlink(file) != 0) {perror(file);}
            return 1;
        }

        else if (strcmp(argv[0], "jobs") == 0) {
            jobs(job_list);
            return 1;
        }
        // How to do it??
        // How to send SIGCONT ??
        else if (strcmp(argv[0], "fg") == 0) {
            int status;
            int pid = atoi(argv[1]);
            if (kill(pid,SIGCONT) == -1) {
                    char *pid = "fg pid\n";
                    write(1,pid,strlen(pid));
                    perror("kill");
            }
            else {
                fg_global_pid = pid;
                // you have to wait this process 
                while(fg_global_pid) {
                    sleep(1);
                }
            }
            return 1;
        }
        
        else if (strcmp(argv[0], "bg") == 0) {
            int status;
            // update job list
            int pid = atoi(argv[1]);
            if (kill(pid,SIGCONT) == -1) {
                perror("kill");
            }
            else {
            }
            return 1;
        }
        else {
            return 0;
        }
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
        sigemptyset(&action.sa_mask);
        sigaddset(&action.sa_mask,SIGINT);
        sigaddset(&action.sa_mask,SIGTSTP);
        sigaddset(&action.sa_mask,SIGQUIT);
        sigaddset(&action.sa_mask,SIGCHLD);
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
    //char *echo = "\nReceive signal: CTRL-C\n";
    //write(1,echo,strlen(echo));
    // why we do it when child_group_id != 0 ??
    if (fg_global_pid != 0){
        kill(-fg_global_pid,SIGINT);
    }
}

/* sigtstp_handler
 * Respond to SIGTSTP signal (CTRL-Z)
 *
 * Argument: int sig - the integer code representing this signal
 */
void sigtstp_handler(int sig) {
    if (fg_global_pid != 0){
        if ( kill(-fg_global_pid,SIGTSTP) == 0) {
            fg_global_pid = 0;
        }
        else {
            perror(" ");
        }
    }
}

/* sigquit_handler
 * Catches SIGQUIT signal (CTRL-\)
 *
 * Argument: int sig - the integer code representing this signal
 */
void sigquit_handler(int sig) {
    if (fg_global_pid != 0){
        kill(-fg_global_pid,SIGQUIT);
    }
}

// waitpid() will detect the pid, whose state changed.

void child_handler(int sig) {
    // update a job here
    int status;
    pid_t pid;
    //pid = get_next_pid(job_list);
    
    if ((pid = waitpid(-1,&status,WNOHANG|WUNTRACED|WCONTINUED)) == -1) {
        perror("waitpid");
    }
    // If fg job terminates, busy loop ends.
    if ( pid == fg_global_pid) {
        fg_global_pid = 0;
    }
    // job normally exited
    if ( WIFEXITED(status) ) {
            fg_global_pid = 0;
            char info[100] = {0x0};
            char *cmd; char buf[10] = {0x0};
            cmd = "Jobs ["; strcat(info,cmd);
            sprintf(buf,"%d",get_job_jid(job_list,pid));
            strcat(info,buf);
            cmd = "] ("; strcat(info,cmd);
            sprintf(buf,"%d",pid);
            strcat(info,buf);
            cmd = ") normally exited."; strcat(info,cmd);
            sprintf(buf,"%d\n",WEXITSTATUS(status));
            strcat(info,buf);
            //write(1,info,strlen(info));
            if (remove_job_pid(job_list,pid) != 0) {
                perror("Remove job error !\n");}
       }
        // job terminated by a signal
    if (WIFSIGNALED(status)) {
            fg_global_pid = 0;
            char info[100] = {0x0};
            char *cmd; char buf[10] = {0x0};
            cmd = "Jobs ["; strcat(info,cmd);
            sprintf(buf,"%d",get_job_jid(job_list,pid));
            strcat(info,buf);
            cmd = "] ("; strcat(info,cmd);
            sprintf(buf,"%d",pid);
            strcat(info,buf);
            cmd = ") terminated by signal"; strcat(info,cmd);
            sprintf(buf,"%d\n",WTERMSIG(status));
            strcat(info,buf);
            write(1,info,strlen(info));
            if (remove_job_pid(job_list,pid) != 0) {
                perror("Remove job error !\n");}
    }
        // job stopped by signal
    if (WIFSTOPPED(status)) {
            fg_global_pid = 0;
            char info[100] = {0x0};
            char *cmd; char buf[10] = {0x0};
            cmd = "Jobs ["; strcat(info,cmd);
            sprintf(buf,"%d",get_job_jid(job_list,pid));
            strcat(info,buf);
            cmd = "] ("; strcat(info,cmd);
            sprintf(buf,"%d",pid);
            strcat(info,buf);
            cmd = ") stopped by signal"; strcat(info,cmd);
            sprintf(buf,"%d\n",WSTOPSIG(status));
            strcat(info,buf);
            write(1,info,strlen(info));
            if (update_job_pid(job_list, pid, _STATE_STOPPED)) {
                perror("Update error !\n");
            }
    }
        // job resumed by signal
        if (WIFCONTINUED(status)) {
            if (update_job_pid(job_list, pid, _STATE_RUNNING)) {
                perror("Update error !\n");
            }
        }
}
