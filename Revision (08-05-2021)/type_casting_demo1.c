#include <stdio.h>
#include <stdlib.h>

int n = 0x0a0b0c0d;
unsigned char uc;

int main(void){
    uc = (unsigned char) n;
    printf("uc = %hhx\n", uc);
    return 0;
}