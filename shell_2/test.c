#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
    int i = atoi(argv[1]);
    while (i) {
        sleep(1);
        //printf("%d\n",i);
        i--;
    }
    return 0;
}