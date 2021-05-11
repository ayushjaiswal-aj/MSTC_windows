#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void test_function(void);

int main(void){
    test_function();
    return 0;
}

void test_function(void){
    int arr_size = 0;
    int *p_arr = NULL;
    int i;

    printf("Enter the size of an array: \n");
    scanf("%d", &arr_size);

    if(arr_size <= 0){
        puts("Invalid size of an array: exiting...");
        exit(-1);
    }

    p_arr = malloc(arr_size * sizeof(int));
    assert(p_arr != NULL);
    memset(p_arr, 0, arr_size * sizeof(int));

    for(i=0; i<arr_size; i++){
        *(p_arr + i) = rand();
    }

    for(i=0; i<arr_size; i++){
        printf("p_arr[%d]: %d\n", i, *(p_arr + i));
    }

    free(p_arr);
    p_arr = NULL;
}