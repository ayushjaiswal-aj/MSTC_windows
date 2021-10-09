#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 2
#define ARRAY_EMPTY -2

typedef int data_t;
typedef int status_t;
typedef int index_t;

status_t merge(data_t *array, index_t l, index_t m, index_t r);
status_t merge_sort(data_t *array, index_t start, index_t end);
void show_array(data_t *array, size_t size);

int main(void){
    data_t *array = (data_t *)malloc(sizeof(int) * 10);
    int i;
    for(i = 0; i < 10; i++){
        array[i] = (rand() % 10) * 3;
    }
    show_array(array, 10);
    if(merge_sort(array, 0, 9) == SUCCESS){
        printf("merge sort successful\n");
    }
    show_array(array, 10);

    return (EXIT_SUCCESS);
}

status_t merge(data_t *array, index_t l, index_t m, index_t n){
    int i, j, k;
    
    int n1 = m - l + 1; 
    int n2 = n - m;
    
    int *left = (int *)malloc(sizeof(int) * n1);
    int *right = (int *)malloc(sizeof(int) * n2);

    for(i = 0; i<n1; i++){
        left[i] = array[l + i];
    }
    for(i = 0; i<n2; i++){
        right[i] = array[m + i + 1];
    }

    i = 0;
    j = 0;
    k = l;
    while(i < n1 && j < n2){
        if(left[i] < right[j]){
            array[k] = left[i];
            i++;
            k++;
        }
        else {
            array[k] = right[j];
            j++;
            k++;
        }
    }
    if(i < n1){
        array[k] = left[i];
        i++;
        k++;
    }
    
    if(j < n2){
        array[k] = right[j];
        j++;
        k++;
    }
    free(left);
    free(right);
    
    return (SUCCESS);
}

status_t merge_sort(data_t *array, index_t start, index_t end){
    if(start < end){
        int mid = start + (end - start) / 2;

        merge_sort(array, start, mid);
        merge_sort(array, mid+1, end);

        merge(array, start, mid, end);
    }
}

void show_array(data_t *array, size_t size){
    int i;
    for(i = 0; i<size; i++){
        printf("[%d] ", array[i]);
    }
    printf("\n");
}