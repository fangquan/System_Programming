#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define BSIZE (8*1024)

int main(int argc, char *argv[]) {
  long long fsize;
  int fd;
  char buf[BSIZE];
  long long i;

  if (argc != 3) {
    fprintf(stderr, "Usage: file name size\n");
    exit(1);
  }

  if ((fd = open(argv[1], O_CREAT|O_TRUNC|O_RDWR, 0666)) == -1) {
    perror(argv[1]);
    exit(1);
  }

  fsize = atoll(argv[2]);

  for (i=0; i<fsize; i+= BSIZE) {
    if (write(fd, buf, BSIZE) == -1) {
      perror("write");
      exit(1);
    }
  }

  return 0;
}
