/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

int combinationCount = 0;

int factorial(int num);
int numberOfPermutations(int num);
void swap(int *p, int *q);
void helper(int *nums, int numsSize, int ***retArray, int *returnSize, int **returnColumnSizes, int l, int n);
int** permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes);

int main(void){
    int *array = malloc(sizeof(int) * 4);
    int **retArray = NULL;
    int *columnSizes = NULL;
    int i, j, retSize;
    
    for(i = 0; i < 4; i++){
        *(array + i) = i;
        printf("[%d] ", *(array + i));
    }

    retArray = permute(array, 4, &retSize, &columnSizes);
    printf("\n[\n");
    for(i = 0; i < retSize; i++){
        printf("[");
        for(j = 0; j < columnSizes[i]; j++){
            printf("%d ", retArray[i][j]);
        }
        printf("]\n");
    }
    printf("]");
    return 0;
}

int factorial(int num){
    if(num == 0){
        return 1;
    }
    return num * factorial(num - 1);
}


int numberOfPermutations(int num){
    return factorial(num);
}

void swap(int *p, int *q){
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

void helper(int *nums, int numsSize, int ***retArray, int *returnSize, int **returnColumnSizes, int l, int r){
    int i;
    if(l == r){
        (*retArray)[combinationCount] = (int *)malloc(sizeof(int) * numsSize);
        (*returnColumnSizes)[combinationCount] = numsSize;
        int j;
        for(j = 0; j < numsSize; j++){
            (*retArray)[combinationCount][j] = nums[j];
        }
        combinationCount++;
    }
    else {
        for(i = l; i <= r; i ++){
            swap((nums+l), (nums+i));
            helper(nums, numsSize, retArray, returnSize, returnColumnSizes, l+1, r);
            swap((nums+l), (nums+i));
        }
    }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int **retArray = NULL;
    *returnSize = numberOfPermutations(numsSize);
    retArray = (int **)malloc(sizeof(int *) * (*returnSize));
    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    helper(nums, numsSize, &retArray, returnSize, returnColumnSizes, 0, numsSize - 1);
    return retArray;
}