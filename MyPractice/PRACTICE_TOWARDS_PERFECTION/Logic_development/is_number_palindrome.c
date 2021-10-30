/*
 *checks if number is palindrome
 */

#include <stdio.h>
#include <stdlib.h>

int is_palindrome(int num);
int get_number_of_digits(int num);

int main(void){
    int num;
    printf("Enter number: ");
    scanf("%d", &num);
    
    if(is_palindrome(num)){
        printf("number %d is palindrome\n", num);
    }
    else {
        printf("number %d is not palindrome\n", num);
    }
    return 0;
}

int is_palindrome(int num){
    int nr_digits;
    nr_digits = get_number_of_digits(num);
    int *digits = NULL;
    digits = (int*)malloc(sizeof(int) * nr_digits);

    int i = 0, j = 0;
    while(num != 0){
        *(digits + i) = num % 10;
        num = num / 10;
        i++;
    }

    i = 0;
    j = nr_digits - 1;
    
    while(i < j){
        if(digits[i] != digits[j]){
            return 0;
        }
        i ++;
        j --;
    }
    free(digits);
    digits = NULL;
    return 1;
}

int get_number_of_digits(int num){
    printf("inside get_number_of_digits()\n");
    int count = 0;
    while(num != 0){
        num = num / 10;
        count++;
    }
    return count;
}