#include <stdio.h>
#include <stdlib.h>

void printTriplate(int *nums, int numsSize){
    int i, j, k;
    for(i = 0; i < numsSize - 2; i ++){
        for(j = i+1; j < numsSize - 1; j ++){
            for(k = j+1; k < numsSize; k ++){
                if(nums[i] + nums[j] + nums[k] == 0){
                    printf("%d, %d. %d\n",  nums[i], nums[j], nums[k]);
                }
            }
        }
    }
}

int main(void){
    int nums[] = {-1,0,1,2,-1,-4};
    printTriplate(nums, 6);
    return 0;
}