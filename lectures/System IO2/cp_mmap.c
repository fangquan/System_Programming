#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

#define BSIZE (8*1024)

int main(int argc, char *argv[]) {
  int sourcefd;
  int targetfd;
  char buf[BSIZE];
  int ret;
  void *src;
  void *dest;
  struct stat sbuf;

  if (argc != 3) {
    fprintf(stderr, "Usage: cp_mmap source target\n");
    exit(1);
  }

  if ((sourcefd = open(argv[1], O_RDONLY)) == -1) {
    perror(argv[1]);
    exit(1);
  }
  if (fstat(sourcefd, &sbuf) == -1) {
    perror("fstat");
    exit(1);
  }

  if ((src = mmap(0, sbuf.st_size, PROT_READ, MAP_SHARED, sourcefd, 0))
      == MAP_FAILED) {
    perror("mmap source");
    exit(1);
  }

  if ((targetfd = open(argv[2], O_CREAT|O_TRUNC|O_RDWR, 0666)) == -1) {
    perror(argv[2]);
    exit(1);
  }

  if (lseek(targetfd, sbuf.st_size-1, SEEK_SET) == -1) {
    perror("lseek");
    exit(1);
  }

  if (write(targetfd, "x", 1) == -1) {
    perror("write");
    exit(1);
  }

  if ((dest = mmap(0, sbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED,
      targetfd, 0)) == MAP_FAILED) {
    perror("mmap target");
    exit(1);
  }

  memcpy(dest, src, sbuf.st_size);

  return 0;
}
