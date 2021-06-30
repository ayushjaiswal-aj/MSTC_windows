// Looping right shift
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i;
    int n;
    int k;

    puts("Block 1:");
    for(i = 256; i>0; i = i >> 2){
        printf("i = %d\n", i);
    }
    puts("Block 2:");
    printf("enter n: ");
    scanf("%d", &n);
    printf("Enter k: ");
    scanf("%d", &k);
    for(i = n; i>0; i >>= k){
        printf("i = %d\n", i);
    }

    return 0;
}