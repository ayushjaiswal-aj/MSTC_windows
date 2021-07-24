#include <stdio.h>
#include <stdlib.h>

int *p = (int*) 1000;

int main(void){
    printf("p + 1 = %llu\n", (unsigned long long)(p + 1));
    printf("p + 1 = %llu\n", (unsigned long long)p + 1);
    printf("p + 2 = %llu\n", (unsigned long long)(p + 2));
    printf("p - 1 = %llu\n", (unsigned long long)(p - 1));
    printf("p - 2 = %llu\n", (unsigned long long)(p - 2));

    printf("(char*)p + 1 = %llu\n", (unsigned long long)((char*)p + 1));
    printf("(char*)p + 2 = %llu\n", (unsigned long long)((char*)p + 2));
    printf("(char*)p - 1 = %llu\n", (unsigned long long)((char*)p - 1));
    printf("(char*)p - 2 = %llu\n", (unsigned long long)((char*)p - 2));

        return 0;
}