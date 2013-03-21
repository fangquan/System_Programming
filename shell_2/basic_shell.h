/* 
 * File:   basic_shell.h
 * Author: qfang
 *
 * Created on November 12, 2012, 5:01 PM
 */

#ifndef _BASIC_SHELL_H
#define	_BASIC_SHELL_H


#define MAXARGS 1024
#define MAXLINE 1024

/* Judge redirection validness, return 1 for valid redirection; 0 for invalid redirection */
int  good_redirection(char *buf, char *inputfile, char *outputfile, char * appendfile);

/* If redirection exists, return redir type
return 0 for input   redirection
return 1 for output  redirection
return 2 for append  redirection
 */
int  which_redirection(char *buf, char *inputfile, char *outputfile, char * appendfile, int which_redirection);

/* return 1 if no redirection file exists; return 0 if redirection file exist *
 * This function is called in which_redirection
 */
int  no_redirection_file(char *buf, int sign);

/* parse the command line and build the argv array
   return value doesn't matter
 */
int  parseline(char *buf, char **argv);

/* returns 1 if "&" exists, otherwise returns 0, and remove the ampersand sign*/
int  background_job(char **argv);

#endif	/* _BASIC_SHELL_H */

