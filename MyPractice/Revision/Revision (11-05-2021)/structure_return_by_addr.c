#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct A{
    int a;
    char b;
    float c;
};

struct A* get_instance_of_A(int init_a, char init_b, float init_c);

int main(void){
    struct A* pA = NULL;

    pA = get_instance_of_A(10, 'A', 3.14f);
    printf("pA->a = %d\npA->b = %c\npA->c = %f\n", pA->a, pA->b, pA->c);

    free(pA);
    pA = NULL;

    return 0;
}

struct A* get_instance_of_A(int init_a, char init_b, float init_c){
    struct A* pA = NULL;
    pA = malloc(sizeof(struct A));
    assert(pA);

    pA->a = init_a;
    pA->b = init_b;
    pA->c = init_c;

    return (pA);
}