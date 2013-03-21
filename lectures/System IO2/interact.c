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

  if (argc != 3) {
    fprintf(stderr, "Usage: interact infifo outfifo\n");
    exit(1);
  }

  if ((in = open(argv[1], O_RDONLY)) == -1) {
    perror(argv[1]);
    exit(1);
  }

  if ((out = open(argv[2], O_WRONLY)) == -1) {
    perror(argv[2]);
    exit(1);
  }

  while (1) {
    write(1, "> ", 2);
    fgets(obuf, BSIZE, stdin);
    if (write(out, obuf, strlen(obuf)+1) == -1) {
      perror("out pipe");
      exit(1);
    }
    if ((ret = read(in, ibuf, BSIZE)) == -1) {
      perror("in pipe");
      exit(1);
    }
    if (ret == 0)
      break;
    fputs(ibuf, stdout);
  }
  return 0;
}
