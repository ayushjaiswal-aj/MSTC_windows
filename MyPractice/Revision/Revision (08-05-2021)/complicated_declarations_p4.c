// Declare a pointer to a function accepting two integers and returns an int

#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b){
    return (a+b);
}

int main(void){
    int (*pfn) (int, int) = NULL;
    int ret;
    pfn = sum;
    ret = pfn(8, 7);
    printf("ret = %d\n", ret);
    printf("size of pointer to function = %zu\n", sizeof(pfn));
    return 0;
}