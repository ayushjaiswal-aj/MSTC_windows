#include <stdio.h>
#include <stdlib.h>

unsigned long long n = 0;
/*
memory blocks of n = [  ][  ][  ][  ][  ][  ][  ][  ]
                        7   6   5   4   3   2   1   n

*/
int main(void){
    printf("n = %llx\n", n);
    
    // M[n] <- 0xff
    // memory blocks of n = [  ][  ][  ][  ][  ][  ][  ][ ff ]
    *(char*) (&n) = 0xff;
    printf("n = %llx\n", n);

    // M[n:1 - n:2] <- 0x ff ff
    //memory blocks of n = [  ][  ][  ][  ][  ][ ff ][ ff ][ ff ]
    *(short*)((char*)(&n)+1) = 0xffff;
    printf("n = %llx\n", n);

    // M[n:3 - n:6] <- 0x ff ff ff ff
    //memory blocks of n = [  ][ ff ][ ff ][ ff ][ ff ][ ff ][ ff ][ ff ]
    *(int*)((char*)(&n) + 3) = 0xffffffff;
    printf("n = %llx\n", n);

    // M[n:7] <- 0x ff
    //memory blocks of n = [ ff ][ ff ][ ff ][ ff ][ ff ][ ff ][ ff ][ ff ]
    *(char*)((char*)&n + 7) = 0xff;
    printf("n = %llx\n", n);

    return 0;
}