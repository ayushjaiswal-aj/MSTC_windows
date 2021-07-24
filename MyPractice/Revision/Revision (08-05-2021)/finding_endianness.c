#include <stdio.h>
#include <stdlib.h>

int main(void){
    int n = 0x0a0b0c0d;

    if(*(char*)&n == 0x0d){
        puts("this machine is a little endian machine");
    }
    else if(*(char*)&n == 0x0a){
        puts("this machine is big endian machine");
    }
    else {
        puts("this is a strange machine");
    }

    return 0;
}