#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 1024
#define SUCCESS 1
#define FAILURE 0

typedef int status_t;

status_t multiply(int *res, int *res_size, int n);
status_t factorial(int n);

int main(void){
    int n;
    printf("Enter number: ");
    scanf("%d", &n);

    factorial(n);
    return (EXIT_SUCCESS);
}

status_t multiply(int *res, int *res_size, int n){
    int carry = 0;
    int product = 0;
    int i;
    for(i = 0; i < *res_size; i++){
        product = (res[i] * n) + carry;
        res[i] = product % 10;
        carry = product / 10;
    }

    while (carry != 0){
        res[i] = carry % 10;
        i++;
        carry = carry/10;
    }
    *res_size = i;
    return (SUCCESS);
}

status_t factorial(int n){
    int *res = (int*)malloc(sizeof(int) * MAX);
    int i = 0, j = n;
    int *res_size = (int*)malloc(sizeof(int) * 1);
    while(1){
        res[i] = j % 10;
        i++;
        j = j/10;
        if(j == 0){
            break;
        }
    }
    *res_size = i;
    j = n-1;
    while(j > 0){
        multiply(res, res_size, j);
        j--;
    }
    printf("res_size = %d\n", *res_size);
    printf("factorial of %d: ", n);
    for(i = *res_size - 1; i >= 0; i--){
        printf("%d", res[i]);
    }
    printf("\n");
    return (SUCCESS);
}