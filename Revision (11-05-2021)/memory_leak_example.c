#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_function(void);
void test_function_2(void);

int main(void){
    test_function();
    test_function_2();
    return 0;
}

void test_function(void){
    int *p = NULL;
    p = (int *)malloc(sizeof(int));
    if(p == NULL){
        puts("memory allocation error\n");
        exit (-1);
    }

    memset(p, 0, sizeof(int));
    *p = 500;
}

void test_function_2(void){
    for(int i=0; i<0xffffff; i++);
}