#include <stdio.h>
#include <stdlib.h>

const int gc_num = 100;

int main(void){
    const int lc_num = 200;

    printf("gc_num = %d\n", gc_num);
    printf("lc_num = %d\n", lc_num);
    printf("gc_num is const integer, not a valid lvalue\n");
    printf("lc_num is const integer, not a valid lvalue\n");

    return 0;
}