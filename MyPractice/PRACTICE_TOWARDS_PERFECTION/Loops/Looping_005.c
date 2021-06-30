//Looping left shift

#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i;
    int n;
    int k;
    puts("Block 1: ");
    for(i=1; i<256; i <<= 2){
        printf("i = %d\n", i);
    }
    puts("block 2: ");
    for(i=1; i<= 256; i<<=2){
        printf("i = %d\n", i);
    }
    puts("Block 3: ");
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter k: ");
    scanf("%d", &k);
    for(i=1; i<=n; i<<=k){
        printf("i = %d\n", i);
    }
    puts("block 4: ");
    for(i = 1; i<=n; i <<= n){
        printf("i = %d", i);
    }
    return (0);
}