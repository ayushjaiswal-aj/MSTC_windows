#include <stdio.h>
#include <stdlib.h>

void get_integer_instance(int *pp);

int main(void){
    int *p = NULL;

    get_integer_instance(&p);

    printf("address of p (&p) = %p\n", &p);
    printf("address in p (p) = %p\n", p);

    *p = 700;
    printf("*p = %d\n", *p);

    free(p);
    p = NULL;

    return 0;
}

void get_integer_instance(int **pp){
    *pp = malloc(sizeof(int));
}