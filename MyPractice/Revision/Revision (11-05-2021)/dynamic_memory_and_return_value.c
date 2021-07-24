#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int* get_dynamic_integer(int init_n);
int factorial(int n);

int main(void){
    int *p_int = NULL;
    int result;

    p_int = get_dynamic_integer(5);
    printf("address in p: %p\n", p_int);
    result = factorial(*p_int);
    printf("result = %d\n", result);

    free(p_int);
    p_int = NULL;
}

int* get_dynamic_integer(int init_n){
    int *p = NULL;
    p = malloc(sizeof(int));
    assert(p);
    *p = init_n;

    return p;
}

int factorial(int n){
    if(n < 0){
        return (-1);
    }
    if (n == 0 || n == 1){
        return 1;
    }
    
    return n * factorial(n-1);
}