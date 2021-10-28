/*
 *prints number of on bit in integer.
 */

#include <stdio.h>

int number_of_on_bits(int num);

int main(void){
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    printf("number of on bits in %d: %d\n", n,number_of_on_bits(n));
    return 0;
}

int number_of_on_bits(int num){
    int i;
    int count = 0;
    while(num){
        count = count + (num & 1);
        num = num >> 1;
    }
    return count;
}