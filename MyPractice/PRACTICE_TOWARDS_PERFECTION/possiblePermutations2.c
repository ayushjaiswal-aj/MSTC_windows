#include <stdlib.h>
#include <stdio.h>

void showArray(int *arr, int size){
    int i;
    for(i = 0; i< size; i++){
        printf("[%d]", arr[i]);
    }
    printf("\n");
}

void leftShift(int *arr, int start, int end){
    int i, temp;
    temp = arr[start];
    for(i=start; i<end; i++){
        arr[i] = arr[i+1];
    }
    arr[end] = temp;
}

void possiblePermutations(int *nums, int numsSize){
    int i, j, k;

    for(i = 0; i < numsSize; i++){
        showArray(nums, numsSize);
        leftShift(nums, 0, numsSize-1);
        possiblePermutations(nums+i, numsSize-1);
    }
}

int main(void){
    int *arr = NULL;
    arr = malloc(sizeof(int) * 4);
    int i;
    for(i = 0; i < 4; i++){
        arr[i] = i+1;
    }

    possiblePermutations(arr, 4);
    return (EXIT_SUCCESS);
}