#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int bool;

bool isPowerOfTwo(int n);
bool isPowerOfTwoPro(int n);

int main(void){
    int n;
    printf("enter number: ");
    scanf("&n");

    if(isPowerOfTwo(n)){
        printf("%d is power of 2\n", n);
    }
    else {
        printf("%d is not a power of 2\n", n);
    }
    
    if(isPowerOfTwoPro(n)){
        printf("%d is power of 2\n", n);
    }
    else {
        printf("%d is not a power of 2\n", n);
    }

    return (EXIT_SUCCESS);
}

bool isPowerOfTwo(int n){
    return (ceil(log(n, 2)) == floor(log(n, 2)))    
}

bool isPowerOfTwoPro(int n){
    return (!(n & (n - 1)));
}
