#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BSIZE 1024

int main(int argc, char *argv[]) {
  char ibuf[BSIZE];
  char obuf[BSIZE];
  int in;
  int out;
  int ret;
  char *s;

  if (argc != 3) {
    fprintf(stderr, "Usage: talk infifo outfifo\n");
    exit(1);
  }

  if ((out = open(argv[2], O_WRONLY)) == -1) {
    perror(argv[2]);
    exit(1);
  }

  if ((in = open(argv[1], O_RDONLY)) == -1) {
    perror(argv[1]);
    exit(1);
  }

  while (1) {
    if ((ret = read(in, ibuf, BSIZE)) == -1) {
      perror("in pipe");
      exit(1);
    }
	fputs(ibuf, stdout);
    write(1, "> ", 2);
	s = fgets(obuf, BSIZE, stdin);
	if (s == 0)
		break;
    if (write(out, obuf, strlen(obuf)+1) == -1) {
      perror("out pipe");
      exit(1);
    }
  }
  return 0;
}
