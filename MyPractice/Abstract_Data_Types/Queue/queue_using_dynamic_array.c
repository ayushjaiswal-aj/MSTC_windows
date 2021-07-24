#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0
#define QUEUE_FULL 2
#define QUEUE_EMPTY 3

typedef int data_t;
typedef int status_t;
typedef int bool;
typedef int index;
typedef unsigned int size;

struct queue{
    data_t *p_data_array;
    size size;
    int inside_queue;
    index front_index;
    index rear_index;
};

struct queue* create_queue(size queue_size);
status_t destroy_queue(struct queue* p_queue);
status_t insert(struct queue* p_queue, data_t new_data);
status_t remove(struct queue* p_queue, data_t *removed_data);
void peek(struct queue* p_queue);
status_t front(struct queue* p_queue, data_t *p_frout);
status_t rear(struct queue* p_queue, data_t *p_rear);
bool is_empty(struct queue* p_queue);
bool is_full(struct queue* p_queue);

int main(Void){
    struct queue *p_queue = NULL;
    p_queue = create_queue(10);
    data_t test_data;
    int i = 0;
    status_t s;
    while(!(is_full(p_queue))){
        s = insert(p_queue, (i + 1) * 10);
        assert(s == SUCCESS);
        i++;
    }
    peek(p_queue);
    
    s = remove(p_queue, &test_data);
    assert(s == SUCCESS);
    printf("removed test_data: %d\n", test_data);

    peek(p_queue);

    s = insert(p_queue, test_data);
    assert(s == SUCCESS);
    printf("After inserting test data again into the queue: %d\n", test_data);
    peek(p_queue);
    
    while(!(is_empty(p_queue))){
        data_t removed_data, front_data, rear_data;
        peek(p_queue);
        s = remove(p_queue, &removed_data);
        assert(s == SUCCESS);
        printf("removed from queue: %d\n", removed_data);
    }
    return EXIT_SUCCESS;
}

status_t insert(struct queue* p_queue, data_t new_data){
    if(is_full(p_queue)){
        return (FAILURE);
    }
    p_queue->rear_index = p_queue->rear_index + 1;
    p_queue->p_data_array[p_queue->rear_index] = new_data;
    p_queue->inside_queue += 1;
    return (SUCCESS);
}

status_t remove(struct queue* p_queue, data_t *removed_data){
    if(is_empty(p_queue)){
        return (FAILURE);
    }
    *removed_data = p_queue->p_data_array[p_queue->front_index];
    int i;
    for(i=0; i < p_queue->inside_queue - 1; i++){
        p_queue->p_data_array[i] = p_queue->p_data_array[i+1]; 
    }
    p_queue->rear_index = (p_queue->rear_index - 1);
    p_queue->inside_queue -= 1;
    return (SUCCESS);
}

void peek(struct queue* p_queue){
    if(is_empty(p_queue)){
        printf("Empty queue\n");
        return;
    }
    status_t s;
    data_t front_data, rear_data;
    s = front(p_queue, &front_data);
    assert(SUCCESS);
    s = rear(p_queue, &rear_data);
    assert(SUCCESS);
    printf("front of queue: %d\n", front_data);
    printf("rear of queue: %d\n", rear_data);
}

bool is_empty(struct queue* p_queue){
    if(p_queue->inside_queue == 0){
        return (TRUE);
    }
    return (FALSE);
}

bool is_full(struct queue* p_queue){
    if(p_queue->size == p_queue->inside_queue){
        return (TRUE);
    }
    return (FALSE);
}

status_t front(struct queue* p_queue, data_t *p_front){
    if(is_empty(p_queue)){
        return (FAILURE);
    }
    *p_front = p_queue->p_data_array[p_queue->front_index];
    return (SUCCESS);
}

status_t rear(struct queue* p_queue, data_t *p_rear){
    if(is_empty(p_queue)){
        return (FAILURE);
    }
    *p_rear = p_queue->p_data_array[p_queue->rear_index];
    return (SUCCESS);
}

struct queue* create_queue(size queue_size){
    assert(queue_size > 0);
    struct queue *p_queue = NULL;
    p_queue = (struct queue*)malloc(sizeof(struct queue));
    memset(p_queue, 0, sizeof(struct queue));
    assert(p_queue);
    p_queue->p_data_array = (data_t *)malloc(sizeof(data_t) * queue_size);
    memset(p_queue->p_data_array, 0, sizeof(int) * queue_size);
    p_queue->size = queue_size;
    p_queue->inside_queue = 0;
    p_queue->front_index = 0;
    p_queue->rear_index = -1;
    return (p_queue);
}

status_t destroy_queue(struct queue *p_queue){
    free(p_queue->p_data_array);
    p_queue->p_data_array = NULL;
    free(p_queue);
    p_queue = NULL;
    return (SUCCESS);
}