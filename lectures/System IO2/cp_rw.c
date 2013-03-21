#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define BSIZE (8*1024)

int main(int argc, char *argv[]) {
  int sourcefd;
  int targetfd;
  char buf[BSIZE];
  int ret;

  if (argc != 3) {
    fprintf(stderr, "Usage: cp_rw source target\n");
    exit(1);
  }

  if ((sourcefd = open(argv[1], O_RDONLY)) == -1) {
    perror(argv[1]);
    exit(1);
  }

  if ((targetfd = open(argv[2], O_CREAT|O_TRUNC|O_RDWR, 0666)) == -1) {
    perror(argv[2]);
    exit(1);
  }

  while (1) {
    if ((ret = read(sourcefd, buf, BSIZE)) == -1) {
      perror("read");
      exit(1);
    }
    if (ret == 0)
      break;
    if (write(targetfd, buf, ret) == -1) {
      perror("write");
      exit(1);
    }
  }

  return 0;
}
