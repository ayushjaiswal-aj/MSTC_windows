#include <stdio.h>
#include <stdlib.h>

int g_rw_int = 100;
const int g_ro_int = 1000;

int *ptr_to_int;
const int *ptr_to_const_int;

int main(void){
    int loc_rw_int = 200;
    const int loc_ro_int = 2000;

    ptr_to_int = &g_rw_int;
    printf("ptr_to_int = &g_rw_int --> *ptr_to_int = %d\n", *ptr_to_int);

    ptr_to_int = &loc_rw_int;
    printf("ptr_to_int = &loc_rw_int --> *ptr_to_int = %d\n", *ptr_to_int);

    ptr_to_int = &g_ro_int;
    //*ptr_to_int = -1000;
    printf("ptr_to_int = &g_ro_int -->on *ptr_to_int = -1000 is invalid opration\n");

    ptr_to_const_int = &g_rw_int;
    //*ptr_to_const_int = -1000;
    printf("ptr_to_const_int = &g_rw_int -> on *ptr_to_const_int = -1000 it is invalid opration\n");
    printf("it considers the address it is pointing to as const, you cannot write using pointer to const int\n");

    printf("you can change to which location you point to\n");

    ptr_to_const_int = &g_ro_int;
    ptr_to_const_int = &loc_rw_int;
    ptr_to_const_int = &loc_ro_int;
    
    return 0;
}