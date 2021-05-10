#include <stdio.h>
#include <stdlib.h>

int n, m;

int *p;
const int* cp;

int *const x = &n;
const int *const y = &m;

int main(void){
    printf("p is pointer to integer value so it is *p is valid lvalue\n");
    p = &n;
    *p = 10;
    printf("n = %d\n", n);
    
    p = &m;
    *p = 20;
    printf("m = %d\n", m);

    cp = &n;
    cp = &m;
    printf("cp is pointer to const integer value so *cp is invalid lvalue but cp is valid lvalue\n");

    *x = 1000;
    printf("x is const pointer to integer value so x is invalid lvalue but *x is valid lvalue\n");

    printf("y is const pointer to const integer so y and *y both are invalid l value\n");

    return 0;
}