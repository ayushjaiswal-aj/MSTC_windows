/*
Declear a pointer to function accepting 
    1.  int
    2.  a pointer to function accepting 
            a. int
        and returning
            a. void
    and returning
        a. a pointer to function accepting
            (a) int 
        returing
            (a) void

    void (*(*pfn) (int, void (*)(int)))(int);

*/

#include <stdio.h>
#include <stdlib.h>

void handler_1(int a){
    printf("inside handler function: a = %d\n", a);
    return;
}

void (*my_function (int k, void(*my_function_pfn)(int a)))(int n){
    void (*ret_pfn)(int) = NULL;
    printf("inside my_function: k = %d\n", k);
    ret_pfn = my_function_pfn;
    return (ret_pfn);
}

int main(void){
    void (*pfn)(int);

    pfn = my_function(10, handler_1);
    pfn(100);

    return 0;
}
