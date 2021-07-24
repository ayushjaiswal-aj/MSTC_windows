/*
Declare an array 5 of pointers to function accepting
    a. int
    b. int
returning
    a. int

*/

#include <stdio.h>
#include <stdlib.h>

int aj_add(int, int);
int aj_sub(int, int);
int aj_mul(int, int);
int aj_div(int, int);
int aj_mod(int, int);

int main(void){
    int (*arr[5])(int, int);
    int a = 10, b = 3;
    int i;
    int ret;

    arr[0] = aj_add;
    arr[1] = aj_sub;
    arr[2] = aj_mul;
    arr[3] = aj_div;
    arr[4] = aj_mod;

    for(i=0; i<5; i++){
        ret = arr[i](a, b);
        printf("ret = %d\n", ret);
    }
    return 0;
}

int aj_add(int a, int b){
    return (a+b);
}

int aj_sub(int a, int b){
    return (a-b);
}

int aj_mul(int a, int b){
    return (a*b);
}

int aj_div(int a, int b){
    return (a/b);
}

int aj_mod(int a, int b){
    return (a%b);
}