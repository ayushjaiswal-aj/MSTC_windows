#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int SumUniqueElements(int *arr, int size){
    int i, j;
    int sum = 0;
    int repeat_flag;
    for(i = 0; i < size; i++){
        repeat_flag = 0;
        for(j=0; j<i; j++){
            if(arr[i] == arr[j]){
                repeat_flag = 1;
            }
        }
        if(repeat_flag == 1){
            continue;
        }
        sum = sum + arr[i];
    }

    return sum;
}

int main(void){
    int *arr = (int*)malloc(sizeof(int) * 10);
    int i;
    int sum;
    for(i=0; i<10; i++){
        arr[i] = rand() % 10;
        printf("array[%d]: %d\n", i, arr[i]);
    }

    sum = SumUniqueElements(arr, 10);
    printf("Sum = %d\n", sum);
    return (EXIT_SUCCESS);
}