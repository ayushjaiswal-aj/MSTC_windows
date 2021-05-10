#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct A{
    int a;
    char b;
    float c;
};

void get_instance_of_A_1(struct A *pA);
void get_instance_of_A_2(struct A **ppA);
void show_A(struct A *pA);

int main(void){
    struct A inA;
    struct A *ptr = NULL;
    struct A *ptr1 = NULL, *ptr2 = NULL;

    memset(&inA, 0, sizeof(struct A));
    ptr = (struct A*)malloc(sizeof(struct A));
    assert(ptr != NULL);
    memset(ptr, 0, sizeof(struct A));

    get_instance_of_A_1(&inA);
    get_instance_of_A_2(ptr);

    show_A(&inA);
    show_A(ptr);

    free(ptr);
    ptr = NULL;

    return 0;
}

void get_instance_of_A_1(struct A *pA){
    pA->a = 100;
    pA->b = 'X';
    pA->c = 3.14f;
}

void get_instance_of_A_2(struct A **ppA){
    *ppA = (struct A*) malloc(sizeof(struct A));
    assert(*ppA != NULL);
    (*ppA)->a = 1000;
    (*ppA)->b = 'Z';
    (*ppA)->c = 6.28;
}

void show_A(struct A *pA){
    printf("member (a) = %d\nmember (b) = %c\nmember (c) = %f\n", pA->a, pA->b, pA->c);
}