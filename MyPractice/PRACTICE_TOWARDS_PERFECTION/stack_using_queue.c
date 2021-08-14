#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define LIST_EMPTY 2
#define QUEUE_EMPTY LIST_EMPTY
#define STACK_EMPTY LIST_EMPTY

typedef int status_t;
typedef int bool;
typedef int data_t;
typedef struct list_node node_t;
typedef node_t list_t;
typedef struct Stack stack_t;
typedef struct Queue queue_t;

struct list_node{
    data_t data;
    struct list_node *next;
    struct list_node *prev;
};

struct Queue{
    list_t *p_list;
    size_t size;
};

struct Stack{
    queue_t *p_queue;
    size_t size;
};

void show_stack(stack_t *p_stack);
stack_t* create_stack();
status_t destroy_stack(stack_t *p_stack);
status_t push(stack_t *p_stack, data_t new_data);
status_t pop(stack_t *p_stack, data_t *p_data);

void show_queue(queue_t *p_queue);
queue_t* create_queue();
status_t destroy_queue(queue_t *p_queue);
status_t enqueue(queue_t *p_queue, data_t new_data);
status_t dequeue(queue_t *p_queue, data_t *p_data);

void show_list(list_t *p_list);

list_t* create_list();
status_t destroy_list(list_t **pp_list);

status_t insert_beg(list_t *p_list, data_t new_data);
status_t insert_end(list_t *p_list, data_t new_data);
status_t pop_end(list_t *p_list, data_t *p_data);
status_t pop_beg(list_t *p_list, data_t *p_data);

void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end);
void generic_delete(node_t *p_delete_Node);

node_t* get_list_node(data_t new_data);

void* xcalloc(int nr_elements, int size_per_element);

int main(void){
    stack_t *p_stack = NULL;
    status_t s;
    data_t data;
    int i;
    p_stack = create_stack();

    for(i = 0; i < 10; i++){
        push(p_stack, i);
    }

    show_stack(p_stack);

    pop(p_stack, &data);
    printf("poped data = %d\n", data);

    show_stack(p_stack);

    pop(p_stack, &data);
    printf("poped data = %d\n", data);
    
    show_stack(p_stack);

    pop(p_stack, &data);
    printf("poped data = %d\n", data);
    
    show_stack(p_stack);

    return (EXIT_SUCCESS);
}

void show_stack(stack_t *p_stack){
    show_queue(p_stack->p_queue);
}

stack_t* create_stack(){
    stack_t *p_stack = NULL;
    p_stack = (stack_t *)xcalloc(1, sizeof(stack_t));
    p_stack->p_queue = create_queue();
    p_stack->size = 0;
    return (p_stack);
}

status_t destroy_stack(stack_t *p_stack){
    destroy_queue(p_stack->p_queue);
    free(p_stack);
    p_stack = NULL;
    return (SUCCESS);
}

status_t push(stack_t *p_stack, data_t new_data){
    enqueue(p_stack->p_queue, new_data);
    p_stack->size ++;
    return (SUCCESS);
}

status_t pop(stack_t *p_stack, data_t *p_data){
    queue_t *p_temp_queue = NULL;
    data_t data;
    p_temp_queue = create_queue();
    while(dequeue(p_stack->p_queue, &data) != QUEUE_EMPTY){
        assert(enqueue(p_temp_queue, data) == SUCCESS);
        *p_data = data;
    }
    while(dequeue(p_temp_queue, &data) != QUEUE_EMPTY){
        if(data == *p_data){
            break;
        }
        assert(enqueue(p_stack->p_queue, data) == SUCCESS);
    }
    return (SUCCESS);
}

void show_queue(queue_t *p_queue){
    show_list(p_queue->p_list);
}

queue_t* create_queue(){
    queue_t *p_queue = NULL;
    p_queue = (queue_t *)xcalloc(1, sizeof(queue_t));
    p_queue->p_list = create_list();
    p_queue->size = 0;
    return p_queue;
}

status_t destroy_queue(queue_t *p_queue){
    destroy_list(&(p_queue->p_list));
    free(p_queue);
    p_queue = NULL;
    return (SUCCESS);
}

status_t enqueue(queue_t *p_queue, data_t new_data){
    insert_end(p_queue->p_list, new_data);
    p_queue->size ++;
    return (SUCCESS);
}

status_t dequeue(queue_t *p_queue, data_t *p_data){
    if(pop_beg(p_queue->p_list, p_data) == LIST_EMPTY){
        return QUEUE_EMPTY;
    }
    p_queue->size --;
    return (SUCCESS);
}

void show_list(list_t *p_list){
    node_t *p_run = NULL;
    p_run = p_list->next;
    printf("[end]<->");
    while(p_run != p_list){
        printf("[%d]<->", p_run->data);
        p_run = p_run->next;
    }
    printf("[head]\n");
}

list_t* create_list(){
    list_t *p_list = NULL;
    p_list = get_list_node(0);
    p_list->next = p_list;
    p_list->prev = p_list;
    return (p_list);
}

status_t destroy_list(list_t **pp_list){
    list_t *p_list = NULL;
    node_t *p_run = NULL;
    node_t *p_run_next = NULL;
    p_list = *pp_list;
    p_run = p_list->next;
    while(p_run != p_list){
        p_run_next = p_run->next;
        free(p_run);
        p_run = p_run_next;
    }
    free(p_list);
    *pp_list = NULL;
    return (SUCCESS);
}

status_t insert_beg(list_t *p_list, data_t new_data){
    generic_insert(p_list, get_list_node(new_data), p_list->next);
    return (SUCCESS);
}

status_t insert_end(list_t *p_list, data_t new_data){
    generic_insert(p_list->prev, get_list_node(new_data), p_list);
    return (SUCCESS);
}

status_t pop_end(list_t *p_list, data_t *p_data){
    if(p_list->next == p_list && p_list->prev == p_list){
        return (LIST_EMPTY);
    }
    *p_data = p_list->prev->data;
    generic_delete(p_list->prev);
    return (SUCCESS);
}

status_t pop_beg(list_t *p_list, data_t *p_data){
    if(p_list->next == p_list && p_list->prev == p_list){
        return (LIST_EMPTY);
    }
    *p_data = p_list->next->data;
    generic_delete(p_list->next);
    return (SUCCESS);
}

void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end){
    p_beg->next = p_mid;
    p_mid->next = p_end;
    p_end->prev = p_mid;
    p_mid->prev = p_beg;
}

void generic_delete(node_t *p_delete_node){
    p_delete_node->next->prev = p_delete_node->prev;
    p_delete_node->prev->next = p_delete_node->next;
    free(p_delete_node);
    p_delete_node = NULL;
}

node_t* get_list_node(data_t new_data){
    node_t *p_new_node = NULL;
    p_new_node = (node_t *)xcalloc(1, sizeof(node_t));
    p_new_node->data = new_data;
    p_new_node->next = NULL;
    p_new_node->prev = NULL;
    return (p_new_node);
}

void* xcalloc(int nr_elements, int size_per_element){
    void *p = NULL;
    p = calloc(nr_elements, size_per_element);
    assert(p != NULL);
    return (p);
}