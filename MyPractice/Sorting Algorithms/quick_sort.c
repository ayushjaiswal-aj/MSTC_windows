#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1;
#define FAILURE 0;
#define ARRAY_EMPTY -2;

typedef int status_t;
typedef int data_t;
typedef int index_t;

status_t quick_sort(data_t *array, index_t start, index_t end);
index_t partition(data_t *array, index_t start, index_t end);
void show_array(data_t *array, size_t size);

int main(void){
    data_t *array = NULL;
    array = (data_t*) malloc (sizeof(int) * 10);
    int i;
    status_t s;
    for(i = 0; i < 10; i++){
        array[i] = (rand() % 10) * 8;
    }
    
    show_array(array, 10);
    
    s = quick_sort(array, 0, 9);
    
    show_array(array, 10);

    return (EXIT_SUCCESS);
}

status_t quick_sort(data_t *array, index_t start, index_t end){
    if(start < end){
        int pivot_index = partition(array, start, end);

        quick_sort(array, start, pivot_index - 1);
        quick_sort(array, pivot_index + 1, end);
    }
    return SUCCESS;
}

index_t partition(data_t *array, index_t start, index_t end){
    data_t pivot = array[end], temp;
    int i = start - 1;
    int j;
    for(j = start; j < end; j++){
        if(array[j] < pivot){
            i++;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    temp = array[i + 1];
    array[i + 1] = array[end];
    array[end] = temp;
    return (i+1);
}

void show_array(data_t *array, size_t size){
    int i;
    for(i = 0; i<size; i++){
        printf("[%d] ", array[i]);
    }
    printf("\n");
}