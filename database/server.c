#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include "window.h"
#include "io_functions.h"
#include "db.h"
#define MAXLINE 256
#define MAXNUM  16

/* Struct encapsulating information about a client */
typedef struct Client {
	Window *window;  // The client window
} Client;

struct argument {
    Client *client;
    pthread_t *thread;
};

// Global variables
Database *db;
char *scriptname;
int active_threads = 0;
pthread_mutex_t mut         = PTHREAD_MUTEX_INITIALIZER;    // This lock is for active threads
pthread_mutex_t clientlock  = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  clientcond  = PTHREAD_COND_INITIALIZER;
int if_stopped = 0;
pthread_t thread_array[MAXNUM];   //thread id global array

// Forward declarations
void client_new(int id);
void client_delete(Client *client);
void Client_delete(void *client);
void *run_client(void *client);
void process_command(char *command, char *response);
void wait_for_true ();
int  install_handler(int sig, void (*handler)(int));
void sigint_handler() {
}

// Add or Delete thread id
void add_t (pthread_t thread) {
    for (int i=0;i<MAXNUM; i++) {
        if (thread_array[i] == 0) {
            thread_array[i] = thread;
            break;
        }
    }
}
void delete_t (pthread_t thread) {
    //printf("%lu\n",thread);
    for (int i=0;i<MAXNUM; i++) {
        if (thread_array[i] == thread) {
            //printf("inner %lu\n",thread);
            thread_array[i] = 0;
            break;
        }
    }
}
void print_t() {
    for (int i=0;i<MAXNUM; i++) {
        if (thread_array[i] > 0) {
            printf("%d %lu\n",i,thread_array[i]);
        }
    }
}

/***********************************
 * Main function
 ***********************************/
int main(int argc, char **argv) {
        int ret;
        memset(thread_array,0,MAXNUM);
	if(argc == 1) {
		scriptname = NULL;
	} else if(argc == 2) {
		int len = strlen(argv[1]);
		scriptname = malloc(len+1);
		strncpy(scriptname, argv[1], len+1);
	} else {
		fprintf(stderr, "Usage: %s [scriptname]\n", argv[0]);
		exit(1);
	}
	// Ignore SIGPIPE
	struct sigaction ign;
	ign.sa_handler = SIG_IGN;
	sigemptyset(&ign.sa_mask);
	ign.sa_flags = SA_RESTART;
	sigaction(SIGPIPE, &ign, NULL);
        // install SIG_INT
        struct sigaction action1;
        action1.sa_handler = sigint_handler; // new handler: clients terminate but server continues working
        sigemptyset(&action1.sa_mask);
        sigaddset(&action1.sa_mask,SIGINT);
        action1.sa_flags   = SA_RESTART;
        sigaction(SIGINT,&action1,NULL);
	db = db_new();
        while (1) {
            char cmdline[MAXLINE];
            int bytes;
            if ((bytes = read(STDIN_FILENO, cmdline, sizeof (cmdline))) == 0 ) {
                for (int i=0;i<MAXNUM;i++)
                {
                    if (thread_array[i] != 0) {
                        //printf("we will cancel %lu\n",thread_array[i]);
                        if (pthread_cancel(thread_array[i])!=0){
                            return 1;
                        }
                        thread_array[i]=0;
                        sleep(1);
                    }
                }
                exit(1);
            }
            // Read from file descriptor
            if (cmdline[bytes-1] == '\n') {
                if (cmdline[0] == 's' && bytes == 2) {
                    pthread_mutex_lock(&mut);
                    if_stopped = 1;
                    printf("stop\n");
                    pthread_mutex_unlock(&mut);
                }
                else if (cmdline[0] == 'g' && bytes == 2) {
                    pthread_mutex_lock(&mut);
                    if_stopped = 0;
                    printf("go\n");
                    pthread_mutex_unlock(&mut);
                    pthread_cond_broadcast(&clientcond);
                }
                else {
                    client_new(active_threads);
                }
            }
        }
        if ( active_threads == 0) {
            db_delete(db);
        }
        free(scriptname);
        pthread_exit(&ret);
}

/***********************************
 * Client handling functions
 ***********************************/
/* Create a new client */
// part1, when the main thread terminate on EOF, clients windows forcely closed ?? But I already detach each thread.
void client_new(int id) {
        pthread_t thread;
	Client *client = (Client *)malloc(sizeof(Client));
	if(!client) {
		perror("malloc");
		return ;
	}
	// Create a window and set up a communication channel with it
	char title[20];
	sprintf(title, "Client %d", id);
	if(!(client->window = window_new(title, scriptname))) {
		free(client);
		return ;
	}
        struct argument *Argument = malloc(sizeof(struct argument));
        Argument->client = client;
        Argument->thread = &thread;
        // add pthread id to a list
        if (pthread_create(&thread,0,run_client,Argument) != 0) {
            return;
        }
        //printf("client_new %lu\n",thread);
        add_t(thread);
        pthread_detach(thread);
        pthread_mutex_lock(&mut);
        active_threads++;
        pthread_mutex_unlock(&mut);
}

/* Delete a client and all associated resources */
void client_delete(Client *client) {
    window_delete(client->window);
    free(client);
}

void Client_delete(void *arg) {
    Client *client = (Client *)arg;
    window_delete(client->window);
    free(client);
    pthread_mutex_lock(&mut);
    active_threads--;
    pthread_mutex_unlock(&mut);
}

void wait_for_true () {
    pthread_mutex_lock(&clientlock);
    while ( if_stopped == 1 ) {
        pthread_cond_wait(&clientcond,&clientlock);
    }
    pthread_mutex_unlock(&clientlock);
}

/* Function executed for a given client */
// How to set up the testing features
void *run_client(void *arg) {
        struct argument *ptr = arg;
        Client   *client = ptr->client;
        pthread_t thread = *(ptr->thread);
        //printf("run_client %lu\n",thread);

	char command[BUF_LEN];
	char response[BUF_LEN];
        // Main loop of the client: fetch commands from window, interpret
	// and handle them, and send results to window.
        pthread_cleanup_push(&Client_delete,(void *)client);
	while(get_command(((Client *)client)->window, command)) {
                wait_for_true();
		process_command(command, response);
		if(!send_response(((Client *)client)->window, response)) {
			break;
                }
	}
        delete_t(thread);
        fprintf(stderr, "Quitting\n");
        pthread_cleanup_pop(1);
        return NULL;
}

/***********************************
 * Command processing functions
 ***********************************/
char *skip_ws(char *str);
char *skip_nonws(char *str);
void next_word(char **curr, char **next);

/* Process the given command and produce an appropriate response */
void process_command(char *command, char *response) {
	char *curr;
	char *next = command;
	next_word(&curr, &next);

	if(!*curr) {
		strcpy(response, "no command");
	} else if(!strcmp(curr, "a")) {
		next_word(&curr, &next);
		char *name = curr;
		next_word(&curr, &next);

		if(!*curr || *(skip_ws(next))) {
			strcpy(response, "ill-formed command");
		} else if(db_add(db, name, curr)) {
			strcpy(response, "added");
		} else {
			strcpy(response, "already in database");
		}
	} else if(!strcmp(curr, "q")) {
		next_word(&curr, &next);

		if(!*curr || *(skip_ws(next))) {
			strcpy(response, "ill-formed command");
		} else if(!db_query(db, curr, response, BUF_LEN)) {
			strcpy(response, "not in database");
		}
	} else if(!strcmp(curr, "d")) {
		next_word(&curr, &next);

		if(!*curr || *(skip_ws(next))) {
			strcpy(response, "ill-formed command");
		} else if(db_remove(db, curr)) {
			strcpy(response, "deleted");
		} else {
			strcpy(response, "not in database");
		}
	} else if(!strcmp(curr, "p")) {
		next_word(&curr, &next);

		if(!*curr || *(skip_ws(next))) {
			strcpy(response, "ill-formed command");
		} else {
			FILE *foutput = fopen(curr, "w");
			if (foutput) {
				db_print(db, foutput);
				fclose(foutput);
				strcpy(response, "done");
			} else {
				strcpy(response, "could not open file");
			}
		}
	} else if(!strcmp(curr, "f")) {
		next_word(&curr, &next);

		if(!*curr || *(skip_ws(next))) {
			strcpy(response, "ill-formed command");
		} else {
			FILE *finput = fopen(curr, "r");
			if(finput) {
				while(fgets(command, BUF_LEN, finput) != 0)
					process_command(command, response);

				fclose(finput);

				strcpy(response, "file processed");
			} else {
				strcpy(response, "could not open file");
			}
		}
	} else {
		strcpy(response, "invalid command");
	}
}

/* Advance pointer until first non-whitespace character */
char *skip_ws(char *str) {
	while(isspace(*str))
		str++;
	return str;
}

/* Advance pointer until first whitespace or null character */
char *skip_nonws(char *str) {
	while(*str && !(isspace(*str)))
		str++;
	return str;
}

/* Advance to the next word and null-terminate */
void next_word(char **curr, char **next) {
	*curr = skip_ws(*next);
	*next = skip_nonws(*curr);
	if(**next) {
		**next = 0;
		(*next)++;
	}
}
