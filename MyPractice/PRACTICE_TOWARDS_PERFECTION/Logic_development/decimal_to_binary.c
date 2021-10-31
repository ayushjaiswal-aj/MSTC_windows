/*
 * decimal to binary
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* get_binary_representation(int num);

int main(void){
    int num;
    int *binary = NULL;
    int i;
    printf("Enter number: ");
    scanf("%d", &num);
    binary = get_binary_representation(num);
    for (i = 0; i < 32; i++){
        printf("%d ", binary[i]);
    }
    printf("\n");
    free(binary);
    binary = NULL;
    return 0;
}

int* get_binary_representation(int num){
    int *digits = (int *)malloc(sizeof(int) * 32);
    int i = 31;
    memset(digits, 0, sizeof(int) * 32);
    while(num != 0){
        digits[i] = num % 2;
        num = num / 2;
        i--;
    }
    return digits;
}