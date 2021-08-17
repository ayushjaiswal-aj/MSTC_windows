#include <stdio.h>
#include <stdlib.h>



/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void showArray(int *nums, int numsSize){
    int i;
    for(i = 0; i<numsSize; i++){
        printf("[%d]", nums[i]);
    }
    printf("\n");
}

int factorial(int n){
    if(n == 0){
        return 1;
    }
    return n * factorial(n-1);
}

void copyArray(int *src, int *dest, int size){
    int i, j;
    for(i = 0; i<size; i++){
        dest[i] = src[i];
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permutations(int *nums, int numsSize, int **possiblePermutations, int *count, int **returnColumnSizes, int start, int end){
    int i;
    if(start == end){
        possiblePermutations[*count] = (int *)malloc(sizeof(int) * numsSize);
        copyArray(nums, possiblePermutations[*count], numsSize);
        showArray(possiblePermutations[*count], numsSize);
        (*count)++;
        (*returnColumnSizes)[*count] = numsSize;
    }    
    else {
        for(i = start; i <= end; i++){
            swap((nums+start), (nums + i));
            permutations(nums, numsSize, possiblePermutations, count, returnColumnSizes, start+1, end);
            swap((nums+start), (nums + i));
        }
    }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int i, j;
    int numberOfPossiblePermutations;
    int **possiblePermutations = NULL;
    int *count = NULL;
    count = (int *)malloc(sizeof(int));
    *count = 0;
    numberOfPossiblePermutations = factorial(numsSize);
    possiblePermutations = (int **)malloc(sizeof(int *) * numberOfPossiblePermutations);
    *returnSize = numberOfPossiblePermutations;
    *returnColumnSizes = (int *)malloc(sizeof(int) * numberOfPossiblePermutations);
    permutations(nums, numsSize, possiblePermutations, count, returnColumnSizes, 0, numsSize-1);
    return possiblePermutations;
}

int main(void){
    int *arr = NULL;
    int **permutations = NULL;
    int size;
    int i;
    int *columnSize = NULL;

    columnSize = (int *)malloc(sizeof(int *));

    arr = (int *)malloc(sizeof(int) * 6);
    for(i = 0; i<6; i++){
        *(arr+i) = i;
    }
    permutations = permute(arr, 6, &size, &columnSize);
    return (EXIT_SUCCESS);
}