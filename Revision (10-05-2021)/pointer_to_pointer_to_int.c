#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void){
    int *p = NULL;
    int **pp = NULL;

    int n;

    printf("Address of (n) = %p\n", &n);
    printf("address of (p) = %p\n", &p);
    printf("address in (p) = %p\n", p);

    p = &n;

    printf("address of (&p) = %p\n", &p);
    printf("address in (p) = %p\n", p);

    p = (int*)malloc(sizeof(int));
    assert(p);

    printf("address of (&p) = %p\n", &p);
    printf("address in (p) = %p\n", p);

    free(p);
    p = NULL;

    pp = &p;

    printf("address in (pp) = %p\n", pp);
    printf("address of (pp) = %p\n", &pp);

    n = 100;

    p = &n;
    printf("*p = %d\n", *p);

    pp = &p;
    printf("**p = %d\n", **pp);

    return 0;
}