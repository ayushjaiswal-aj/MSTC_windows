#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define ARRAY_EMPTY -1

typedef int status_t;
typedef int data_t;
typedef int index_t;

status_t bubble_sort(data_t *array, index_t start, index_t end);
void show_array(data_t *array, size_t size);

int main(void){
    data_t *array = NULL;
    array = (int *)malloc(sizeof(int) *  10);
    int i;
    for(i = 0; i < 10; i++){
        array[i] = (rand() % 10) * 4;
    }
    show_array(array, 10);
    if(bubble_sort(array, 0, 9) == SUCCESS){
        printf("bubble sort successful\n");
    }
    show_array(array, 10);
    
    return (EXIT_SUCCESS);
}

void show_array(data_t *array, size_t size){
    int i;
    for(i = 0; i < size; i++){
        printf("[%d] ", array[i]);
    }
    printf("\n");
}

status_t bubble_sort(data_t *array, index_t start, index_t end){
    int i, j;
    data_t temp;
    for(i = end; i >= 0; i--){
        for(j = 0; j < i; j++){
            if(array[j] > array[j+1]){
            temp = array[j];
            array[j] = array[j+1];
            array[j+1] = temp;
            }
        }
    }
    return SUCCESS;
}