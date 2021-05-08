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

// void (*)(int)
void handler_1(int a){
    printf("inside function hanlder_1: a = %d\n", a);
    return;
}

void handler_2(int a){
    printf("inside function handler_2: a = %d\n", a);
    return;
}

void handler_3(int a){
    printf("inside function handler_3: a = %d\n", a);
    return;
}

// void(*my_function(int, void(*)(int)))(int);
void (*my_function(int k, void (*new_pfn)(int)))(int p){
    static void (*saved_pfn)(int) = NULL;
    void (*ret_pfn)(int) = NULL;

    printf("inside my_function: k = %d\n", k);
    ret_pfn = saved_pfn;
    saved_pfn = new_pfn;

    return ret_pfn;
}

int main(void){
    void (*pfn) (int) = NULL;
    pfn = my_function(10, handler_1);

    pfn = my_function(20, handler_2);
    pfn(200);

    pfn = my_function(30, handler_3);
    pfn(300);

    return 0;
}
