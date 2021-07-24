#include <stdio.h>
#include <stdlib.h>

#define OFFSET_OF(Type, Mem)                ((unsigned long long)(&((Type*)0)->Mem))
#define CONTAINER_OF(Addr, Type, Mem)       (Type*)((unsigned long long)Addr - OFFSET_OF(Type, Mem))

struct A{
    char b;
    int a;
    float c;
};

void f1(int *pi);
void f2(float *pf);

int main(void){
    int *p_int;
    float *pf;
    struct A inA = {'B', 100, 55.55f};
    struct A *pA = (struct A*) malloc(sizeof(struct A));

    pA->b = 'Z';
    pA->a = 300;
    pA->c = 56.532f;

    p_int = &inA.a;
    pf = &pA->c;

    f1(p_int);
    f2(pf);

    free (pA);
    pA = NULL;

    return 0;
}

void f1(int *pi){
    struct A *pA = (struct A*)((unsigned long long)pi - ((unsigned long long)(&(((struct A*)0)->a))));
    printf("pA->b = %c\npA->a = %d\npA->c = %f\n", pA->b, pA->a, pA->c);   
}

void f2(float *pf){
    struct A *pA = (struct  A*)((unsigned long long)pf - ((unsigned long long)(&(((struct A*)0)->c))));
    printf("pA->b = %c\npA->a = %d\npA->c = %f\n", pA->b, pA->a, pA->c);
}