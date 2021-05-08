// Declare a pointer to array 5 of struct A.

#include <stdio.h>
#include <stdlib.h>

struct A {
    int x;
    char c;
};

struct A (*pA) [5];

int main(void){
    int i;
    struct A a[5] = {
        {1, 'a'},
        {2, 'b'},
        {3, 'c'},
        {4, 'd'},
        {5, 'e'}
    };

    pA = &a;
    /*
    this implies that
        a[0] = (*pA)[0]
        a[1] = (*pA)[1]
        .
        .
        a[4] = (*pA)[4]
    */

    for (i=0; i<5; i++){
        printf("a[%d].x = %d\ta[%d].c = %c\n", i, a[i].x, i, a[i].c);
    }

    for(i=0; i<5; i++){
        printf("(*pA)[%d].x = %d\t(*pA)[%d].c = %c\n", i, (*pA)[i].x, i, (*pA)[i].c);
    }
}