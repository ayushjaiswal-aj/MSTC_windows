#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int* allocate_array(int);
void input_array(int *, int);
void output_array(int *, int);
void deallocate_array(int *);

int main(void){
    int *p_arr = NULL;
    int arr_size = 0;
    printf("Enter size of array: \n");
    scanf("%d", &arr_size);

    p_arr = allocate_array(arr_size);
    assert(p_arr != NULL);
    
    input_array(p_arr, arr_size);
    output_array(p_arr, arr_size);

    deallocate_array(p_arr);
    p_arr = NULL;
    return 0;
}

int* allocate_array(int size){
    int *p_arr = NULL;
    if(size <= 0){
        printf("Invalid size array. Array size must be positive number\n");
        return NULL;
    }

    p_arr = (int *)malloc(size * sizeof(int));
    memset(p_arr, 0, size * sizeof(int));

    return (p_arr);
}

void input_array(int *p_arr, int size){
    int i;
    for(i=0; i<size; i++){
        *(p_arr + i) = rand();
    }
}

void output_array(int *p_arr, int size){
    int i;
    for(i=0; i<size; i++){
        printf("p_arr[%d]: %d\n", i, *(p_arr + i));
    }
}

void deallocate_array(int *p_arr){
    free(p_arr);
    p_arr = NULL;
}