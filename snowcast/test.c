#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
int main(int argc, char *argv[]) {
    char buf[1024];
    uint8_t command_type = 0;
    uint16_t udp_port = 2223;
    memcpy(buf,&command_type,sizeof(command_type));
    memcpy(buf,&udp_port,sizeof(udp_port));


  int i;
  char szInput [256];
  printf ("Enter a number: ");
  fgets ( szInput, 256, stdin );
  i = atoi (szInput);
  printf ("The value entered is %d. The double is %d.\n",i,i*2);

  i = strcmp("1","1");
  int j = strcmp("1","2");
  int k = strcmp("2","1");

   i = atoi("a");

  return 0;
}
