#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int m = 10;
int *const const_ptr_to_non_const_int = &m;
const int* const const_ptr_to_const_int = &m;

int main(void){
    auto int pxyz;
    register int xyz;

    int n = 20;

    //const_ptr_to_non_const_int = &n;  //compile time error

    printf("before: m = %d\n", m);
    *const_ptr_to_non_const_int = 1000;
    printf("after: m = %d\n", m);

    //*const_ptr_to_const_int = 2000;   //compile time error
    // const_ptr_to_const_int = &n;     //compile time error

    return 0;
}