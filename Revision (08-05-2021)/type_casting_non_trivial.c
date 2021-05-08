#include <stdio.h>
#include <stdlib.h>

struct A{
    int a;
    char b;
    int arr[5];
    float c;
}inA = {0x12131415, 'A', {0x10203040, 0x50607080, 0x0a0b0c0d, 0xaabbccdd, 0x11223344}, 4.56f};

struct B{
    int p;
    char q;
    int r;
    char s;
    int t;
};

void show(struct A *pA);

int main(void){
    show(&inA);
    *(short*)(&((struct B*)&inA)->t) = 0xf0f0;
    show(&inA);
    return 0;
}

void show(struct A* pA){
    int i;
    printf("pA->a = %x\npA->b = %c\n",pA->a, pA->b);
    for (i=0; i<5; i++){
        printf("pA->arr[%d]: %x\n", i, pA->arr[i]);
    }
    printf("pA->c = %f\n", pA->c);
}