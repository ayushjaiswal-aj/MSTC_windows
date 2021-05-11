#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void method1(void);
int* method2(void);
void method3(void);

int *gptr = NULL;

int main(void){
    int *p_ret = NULL;
    method1();

    p_ret = method2();
    *p_ret = 500;
    printf("*p_ret = %d\n", *p_ret);

    free(p_ret);
    p_ret = NULL;

    method3();
    printf("*gptr = %d\n", *gptr);

    free(gptr);
    gptr = NULL;

    return 0;
}

void method1(void){
    int *p = NULL;
    p = (int*) malloc(sizeof(int));
    if(p == NULL){
        puts("Memory allocation error");
        exit (-1);
    }

    *p = 500;
    printf("*p = %d\n", *p);

    free(p);
    p = NULL;
}

int* method2(void){
    int *p = NULL;
    p = (int*)malloc(sizeof(int));
    if(p = NULL){
        puts("Memory allocation error");
        exit (-1);
    }
    return p;
}

void method3(void){
    int *p = NULL;
    p = (int*) malloc(sizeof(int));
    if(p == NULL){
        puts("Memory allocation error");
        exit (-1);
    }

    *p = 5000;
    gptr = p;
}