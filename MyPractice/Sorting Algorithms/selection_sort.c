#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef int status_t;
typedef int data_t;
typedef int index_t;

status_t selection_sort(data_t *array, index_t start, index_t end);
void show_array(data_t *array, size_t size);

int main(void){
    data_t *array = NULL;
    array = (int *)malloc(sizeof(int) * 10);
    int i;
    for(i=0; i<10; i++){
        array[i] = (rand() % 10) * 6;
    }
    show_array(array, 10);
    if(selection_sort(array, 0, 9) == SUCCESS){
        printf("selection sort algorithm successful\n");
    }
    show_array(array, 10);

    return (EXIT_SUCCESS);
}

status_t selection_sort(data_t *array, index_t start, index_t end){
    int i, j;
    index_t min;
    data_t temp;
    for(i=0; i<end; i++){
        min = i;
        for(j = i+1; j<= end; j++){
            if(array[min] > array[j]){
                min = j;
            }
        }
        temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
    return (SUCCESS);
}

void show_array(data_t *array, size_t size){
    int i;
    for(i = 0; i<size; i++){
        printf("[%d] ", array[i]);
    }
    printf("\n");
}