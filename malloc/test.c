/* 
 * File:   test.c
 * Author: qfang
 *
 * Created on November 28, 2012, 12:07 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */
int main(int argc, char** argv) {
    printf("%d\n", sizeof(size_t));
    char *src   = "hello\n\0";
    char *dest[10];
    memcpy(src,src,strlen(src));
    return 0;
}

