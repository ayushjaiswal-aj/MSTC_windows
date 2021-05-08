#include <stdio.h>
#include <stdlib.h>

struct A{
    int a;
    char b;
    float c;
}inA;

typedef unsigned long long int off_t;

int main(void){
    off_t offset_a, offset_b, offset_c;

    offset_a = (off_t)&inA.a - (off_t)&inA;
    offset_b = (off_t)&inA.b - (off_t)&inA;
    offset_c = (off_t)&inA.c - (off_t)&inA;

    printf("offset_a = %llu\noffset_b = %llu\noffset_c = %llu\n", offset_a, offset_b, offset_c);

    struct A *p = NULL;
    offset_a = offset_b = offset_c = 100;
    offset_a = (off_t)(&p->a);
    offset_b = (off_t)(&p->b);
    offset_c = (off_t)(&p->c);

    printf("VIA SOLN 2:\noffset_a = %llu\noffset_b = %llu\noffset_c = %llu\n", offset_a, offset_b, offset_c);
    
    offset_a = (unsigned long long int)(&((struct A*)0)->a);
    offset_b = (unsigned long long int)(&((struct A*)0)->b);
    offset_c = (unsigned long long int)(&((struct A*)0)->c);

    printf("VIA SOLN 3:\noffset_a = %llu\noffset_b = %llu\noffset_c = %llu\n", offset_a, offset_b, offset_c);

    return 0;
}