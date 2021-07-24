/*
Declare a pointer to function accepting two integers and returns 
        a pointer to array 5 of int

        int (*((*pfn)(int, int)))[5];
*/

#include <stdio.h>
#include <stdlib.h>

int (*(*pfn)(int, int))[5];

int (*my_function(int x, int y))[5] {
    static int a[5];
    a[0] = x+y;
    a[1] = x-y;
    a[2] = x*y;
    a[3] = x/y;
    a[4] = x%y;

    return (&a);
}

int main(void){
    int (*ret)[5];
    int i;
    pfn = my_function;
    ret = pfn(10, 4);

    for(i=0; i<5; i++){
        printf("ret[%d] = %d\n", i, (*ret)[i]);
    }
    return 0;
}