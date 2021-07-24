#include <stdio.h>
#include <stdlib.h>

int aj_square(int a){
    printf("inside of function aj_square: a = %d\n", a);
    return a*a;
}

int aj_cube(int a){
    printf("inside of function aj_cube: a = %d\n", a);
    return a*a*a;
}

int aj_times_two(int a){
    printf("inside of function aj_cube: a = %d\n", a);
    return a*2;
}

int main(void){
    int (*arr[3])(int);
    int a = 10;
    
    arr[0] = aj_square;
    arr[1] = aj_cube;
    arr[2] = aj_times_two;

    printf("arr[0](a): %d\n", arr[0](a));
    printf("arr[1](a): %d\n", arr[1](a));
    printf("arr[2](a): %d\n", arr[2](a));

    return 0;
}