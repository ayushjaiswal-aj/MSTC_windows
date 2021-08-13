#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define LIST_EMPTY 2

typedef int status_t;
typedef int data_t;
typedef int bool;
typedef struct list_node node_t;
typedef node_t list_t;

struct list_node {
    data_t data;
    struct list_node *next;
};

bool is_cycle_present(list_t *p_list);
status_t create_cycle(list_t *p_list, data_t cycle_data);

/* list interface */
void show_list(list_t *p_list);
list_t* create_list();
status_t destroy_list(list_t **pp_list);
status_t insert_beg(list_t *p_list, data_t new_data);
status_t insert_end(list_t *p_list, data_t new_data);

/* list auxillary */
node_t* get_list_node(data_t data);
node_t* get_last_node(list_t *p_list);
node_t* get_data_node(list_t *p_list, data_t search_data);
node_t* get_prev_to_last_node(list_t *p_list);
node_t* get_prev_node(list_t *p_list, data_t data);

void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end);
void generic_delete(node_t *p_prev_node, node_t *p_delete_node);

/* memory auxillary routine */
void* xcalloc(int nr_elements, int size_per_element);

int main(void){
    list_t *p_list1 = NULL;
    list_t *p_list2 = NULL;
    node_t *p_fork_node = NULL;
    int fork_point;
    status_t s;
    data_t data;
    int i;

    p_list1 = create_list();
    p_list2 = create_list();
    
    for(i = 1; i <= 10; i++){
        insert_end(p_list1, i*10);
    }

    for (i = 1; i <= 10; i++){
        insert_end(p_list2, i*100);
    }
    printf("list1: ");
    show_list(p_list1);
    printf("list2: ");
    show_list(p_list2);

    create_cycle(p_list1, 50);

    if(is_cycle_present(p_list1)){
        printf("list1 : cycle status : present\n");
    }
    else {
        printf("list1 : cycle status : absent\n");
    }

    if(is_cycle_present(p_list2)){
        printf("list2 : cycle status : present\n");
    }
    else {
        printf("list2 : cycle status : absent\n");
    }

    return (EXIT_SUCCESS);
}

bool is_cycle_present(list_t *p_list){
    node_t *p_run = NULL;
    node_t *p_run_ahead = NULL;
    p_run = p_list->next;
    p_run_ahead = p_list->next->next;
    printf("cheak point 1\n");
    while(p_run != NULL && p_run_ahead != NULL && p_run_ahead->next != NULL){
        printf("cheak point 2\n");
        if(p_run == p_run_ahead){
            return (TRUE);
        }
        p_run = p_run->next;
        p_run_ahead = p_run_ahead->next->next;
    }
    return (FALSE);
}

status_t create_cycle(list_t *p_list, data_t cycle_data){
    node_t *p_cycle_node = NULL;
    node_t *p_last_node = NULL;
    p_cycle_node = get_data_node(p_list, cycle_data);
    assert(p_cycle_node != NULL);
    p_last_node = get_last_node(p_list);
    assert(p_last_node != NULL);
    p_last_node->next = p_cycle_node;
    return (SUCCESS);
}

/* list interface */
void show_list(list_t *p_list){
    node_t *p_run = NULL;
    p_run = p_list->next;
    printf("[head]->");
    while(p_run != NULL){
        printf("[%d]->", p_run->data);
        p_run = p_run->next;
    }
    printf("[end]\n");
}

list_t* create_list(){
    list_t *p_new_list = NULL;
    p_new_list = get_list_node(0);
    return (p_new_list);
}

status_t destroy_list(list_t **pp_list){
    node_t *p_run = NULL;
    node_t *p_run_next = NULL;
    list_t *p_list = NULL;
    p_list = *pp_list;
    p_run = p_list->next;
    while(p_run != NULL){
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
    node_t *p_last_node = NULL;
    p_last_node = get_last_node(p_list);
    generic_insert(p_last_node, get_list_node(new_data), p_last_node->next);
    return (SUCCESS);
}

/* list auxillary */
node_t* get_list_node(data_t data){
    node_t *p_new_node = NULL;
    p_new_node = (node_t*)xcalloc(1, sizeof(node_t));
    p_new_node->data = data;
    p_new_node->next = NULL;
    return p_new_node;
}

node_t* get_last_node(list_t *p_list){
    if(p_list->next == NULL){
        return p_list;
    }
    node_t *p_prev_to_last_node = NULL;
    p_prev_to_last_node = get_prev_to_last_node(p_list);
    return p_prev_to_last_node->next;
}

node_t* get_prev_to_last_node(list_t *p_list){
    if(p_list->next->next == NULL){
        return (p_list);
    }
    node_t *p_run = p_list->next;
    node_t *p_run_next = p_list->next->next;
    while(p_run_next->next != NULL){
        p_run = p_run->next;
        p_run_next = p_run_next->next;
    }
    return (p_run);
}

node_t* get_prev_node(list_t *p_list, data_t data){
    node_t *p_run = NULL;
    node_t *p_prev_node = NULL;
    p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == data){
            return p_prev_node;
        }
        p_prev_node = p_run;
        p_run = p_run->next;
    }
    return NULL;
}

node_t* get_data_node(list_t *p_list, data_t search_data){
    node_t *p_run = NULL;
    p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == search_data){
            return (p_run);
        }
        p_run = p_run->next;
    }
    return (NULL);
}

void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end){
    p_beg->next = p_mid;
    p_mid->next = p_end;
}

void generic_delete(node_t *p_prev_node, node_t *p_delete_node){
    p_prev_node->next = p_delete_node->next;
    free(p_delete_node);
    p_delete_node = NULL;
}

/* memory auxillary routine */
void* xcalloc(int nr_elements, int size_per_element){
    void *p = NULL;
    p = calloc(nr_elements, size_per_element);
    assert(p != NULL);
    return p;
}
