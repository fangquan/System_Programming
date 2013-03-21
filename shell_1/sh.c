/*
 *shell part 1
 *Quan Fang
 *Nov/02/2012
 *qfang@brown.edu
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAXARGS 1024
#define MAXLINE 1024

int good_redirection(char *buf, char *inputfile, char *outputfile, char * appendfile);
int which_redirection(char *buf, char *inputfile, char *outputfile, char * appendfile, int which_redirection);
int no_redirection_file(char *buf, int sign);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

int main(int argc, char** argv) {
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
        for (i = 0; i < MAXLINE; i++) {inputfile[i]='\0';}
        char outputfile[MAXLINE];
        for (i = 0; i < MAXLINE; i++) {outputfile[i]='\0';}
        char appendfile[MAXLINE];
        for (i = 0; i < MAXLINE; i++) {appendfile[i]='\0';}

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
        if (!builtin_command(argv))
        {
            childpid = fork();
            // In the child process
            if (childpid == 0) {
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
                wait(&status);
            }
        }
    }
    return 0;
}

// parse the command line and build the argv array
int parseline(char *buf, char **argv) {
    char *delim;
    int argc;
    buf[strlen(buf)-1] = '\t';
    while (*buf && (*buf == ' ' || *buf == '\t'))
        buf++;
    // Ignore leading spaces and tabs

    /*Build the argv list*/
    argc = 0;
    // split out the spaces or tabs
    // strchr will return NULL if not found
    // if no space or tab, delim will go to the last element
    if (strchr(buf, ' ') != NULL) {
        delim = strchr(buf, ' ') < strchr(buf, '\t') ? strchr(buf, ' '):strchr(buf, '\t');
    } else {
        delim = strchr(buf, '\t');
    }
    
    while (delim)
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ' || *buf == '\t')) /*Ignore leading spaces*/
        {
            buf++;
        }
        if (strchr(buf, ' ') != NULL) {
            delim = strchr(buf, ' ') < strchr(buf, '\t') ? strchr(buf, ' '):strchr(buf, '\t');
        } else {
            delim = strchr(buf, '\t');
        }
    }
    argv[argc] = NULL;
    return 1;
}

int good_redirection(char *buf, char *inputfile, char *outputfile, char * appendfile) {
    // return 0 if fails
    // buf has a tailing \n sign
    int len = strlen(buf);
    int input = 0, output = 0, append = 0;
    int i;
    for ( i = 0; i < len-1 ; ) {
        if ( buf[i] == '<')  {input++; i++;}
        else if ( buf[i] == '>' ) {
                if ( buf[i+1] == '>' && i+1 < len -1) {append++; i += 2;}
                else {output++; i++;}
        }
        else {i++;}
    }
    
    // Case1, two input(append)/output redirects
    if (output + append > 1 || input > 1) {
        char *error = "ERROR: Can't have 2 input/output redirects on one line\n";
        write(STDERR_FILENO,error,strlen(error));
        return 0;
    }
    
    // Case2, there is only one input sign
    if (input == 1 && (output + append == 0)) {
        which_redirection(buf, inputfile, outputfile, appendfile, 0);
        return 1;
    }

    // Case 3, there is only one output sign
     if (output == 1 && (input + append == 0)) {
       which_redirection(buf, inputfile, outputfile, appendfile, 1);
       return 1;
    }

    // Case 4, there is only one append sign
    if (append == 1 && (input + output == 0)) {
        which_redirection(buf, inputfile, outputfile, appendfile, 2);
        return 1;
    }
    
    //Case 5, there is 1 output and 1 input sign, no append sign
    // In this case, we have to work on the sign closer to the end.
    // Otherwise, /bin/cat<bar>foo will be "bar>foo" as input
    if (append == 0 && input == 1 && output == 1) {
       int insign = 0, outsign = 0;
       while (buf[insign] != '<')  {insign++;}
       while (buf[outsign] != '>') {outsign++;}
       if (insign > outsign)
       {
       which_redirection(buf, inputfile, outputfile, appendfile, 0);
       which_redirection(buf, inputfile, outputfile, appendfile, 1);
       }
       else
       {
       which_redirection(buf, inputfile, outputfile, appendfile, 1);
       which_redirection(buf, inputfile, outputfile, appendfile, 0);
       }

       return 1;
    }

    //Case 6, there is 1 append and 1 input sign, no output sign
    if (append == 1 && input == 1 && output == 0) {
       int insign = 0, appendsign = 0;
       while (buf[insign] != '<')  {insign++;}
       while (buf[appendsign] != '>') {appendsign++;}
       appendsign++;
       if (insign > appendsign)
       {
       which_redirection(buf, inputfile, outputfile, appendfile, 0);
       which_redirection(buf, inputfile, outputfile, appendfile, 2);
       }
       else
       {
       which_redirection(buf, inputfile, outputfile, appendfile, 2);
       which_redirection(buf, inputfile, outputfile, appendfile, 0);
       }
       return 1;
    }
    // This is returned when there is no redirections
    return 1;
}

// which_type
// but this function is for only 1 sign
// if we have 2 signs, we need to work from back to front
// 0 ==> input
// 1 ==> output
// 2 ==> appendfile
int which_redirection(char *buf, char *inputfile, char *outputfile, char * appendfile, int which_type) {
        int sign = 0, file_starting, file_ending;
        if (which_type == 0) {
            while (buf[sign] != '<') {sign++;}
        }

        if (which_type == 1) {
            while (buf[sign] != '>') {sign++;}
        }

        if (which_type == 2) {
            while (buf[sign] != '>') {sign++;}
            sign++;
        }
        
        if(no_redirection_file(buf,sign)){
        char *error = "ERROR: No redirection file specified\n";
        write(STDERR_FILENO,error,strlen(error));
        return 0;}
        // file_starting is the first letter of input file
        file_starting = sign+1;
        while (buf[file_starting] != '\n' && (buf[file_starting] == ' ' || buf[file_starting] == '\t'))
        {file_starting++;}
        // file_ending is the first letter not of input file
        file_ending = file_starting;
        while (buf[file_ending] != '\n' && (buf[file_ending] != ' ' && buf[file_ending] != '\t'))
        {file_ending++;}
        
        if (which_type == 0) {
            strncpy(inputfile,buf+file_starting,file_ending-file_starting);
        }
        if (which_type == 1) {
            strncpy(outputfile,buf+file_starting,file_ending-file_starting);
        }
        if (which_type == 2) {
            strncpy(appendfile,buf+file_starting,file_ending-file_starting);
            sign--;
        }
        int i;
        for (i=sign;i<file_ending;i++) {
            buf[i] = ' ';
        }
        return 1;
}

// return 1 if no redirection file exists; return 0 if redirection file exists
int no_redirection_file(char *buf, int sign) {
    int no_file = 1;
    sign++;
    while (buf[sign]!= '\n') {
        if (buf[sign] != ' ' && buf[sign] != '\t') {
            no_file--;
            break;
        }
        else {sign++;};
    }
    return no_file;
}

int builtin_command(char ** argv) {
        if (strcmp(argv[0], "exit") == 0) {
            exit(0);
        }
        else if (strcmp(argv[0], "cd") == 0) {
            if (chdir(argv[1]) != 0) {
                perror(argv[1]);
            }
            return 1;
	}
        // ln -s {target-filename} {symbolic-filename}
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
        else {
            return 0;
        }
}









