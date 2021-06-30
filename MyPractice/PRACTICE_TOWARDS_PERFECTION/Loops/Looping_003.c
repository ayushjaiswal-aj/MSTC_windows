// looping multiplication

#include <stdio.h>
int main(void){
    int i;
    int n;
    int k;

    puts("block 1:");
    for(i = 1; i<100; i = i*2)
        printf("i = %d\n", i);

    puts("block 2:");
    for(i = 1; i<= 256; i*=2);
        printf("i = %d\n", i);
    
    puts("block 3: ");
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter k: ");
    scanf("%d", &k);
    for(i=1; i<n; i = i*k){
        printf("i = %d\n", i);
    }
    for(i = 1; i<=n; i *= k){
        printf("i = %d\n", i);
    }
    return (0);
}