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

status_t fork_list(list_t *p_list1, list_t *p_list2, int n);
bool find_fork_point(list_t *p_list1, list_t *p_list2, node_t **pp_fork_node, int *n);

/* list interface */
void show_list(list_t *p_list);
list_t* create_list();
status_t destroy_list(list_t **pp_list);
status_t insert_beg(list_t *p_list, data_t new_data);
status_t insert_end(list_t *p_list, data_t new_data);

/* list auxillary */
node_t* get_list_node(data_t data);
node_t* get_last_node(list_t *p_list);
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

    for (i = 1; i <= 5; i++){
        insert_end(p_list2, i*100);
    }
    printf("list1: ");
    show_list(p_list1);
    printf("list2: ");
    show_list(p_list2);

    assert(fork_list(p_list1, p_list2, 5) == SUCCESS);
    printf("list after fork: \n");
    printf("list1: ");
    show_list(p_list1);
    printf("list2: ");
    show_list(p_list2);

    if(find_fork_point(p_list1, p_list2, &p_fork_node, &fork_point) == TRUE){
        printf("fork point presnt at %d th node of list1\n", fork_point);
    }
    else {
        printf("fork point is absent... \n");
    }

    return (EXIT_SUCCESS);
}

status_t fork_list(list_t *p_list1, list_t *p_list2, int n){
    node_t *p_last_node_list2 = NULL;
    node_t *p_list1_nth_node = NULL;
    p_last_node_list2 = get_last_node(p_list2);
    int i;
    p_list1_nth_node = p_list1->next;
    for(i=1; i<n; i++){
        p_list1_nth_node = p_list1_nth_node->next;
    }
    p_last_node_list2->next = p_list1_nth_node;
    return (SUCCESS);
}

bool find_fork_point(list_t *p_list1, list_t *p_list2, node_t **pp_fork_node, int *n){
    node_t *p_run_list1 = NULL;
    node_t *p_run_list2 = NULL;
    int i = 0;
    p_run_list1 = p_list1->next;
    while (p_run_list1 != NULL){
        i++;
        printf("p_run_list1: %p :: p_run_list1->data: %d\n", p_run_list1, p_run_list1->data);
        p_run_list2 = p_list2->next;
        while(p_run_list2 != NULL){
            printf("p_run_list2: %p :: p_run_list2->data: %d\n", p_run_list2, p_run_list2->data);
            if(p_run_list2->data == p_run_list1->data){
                *pp_fork_node = p_run_list1;
                *n = i;
                printf("i : n = %d :: pp_fork_node = %p\n", i, *pp_fork_node);
                return TRUE;
            }
            p_run_list2 = p_run_list2->next;
        }
        p_run_list1 = p_run_list1->next;
    }
    return (FALSE);
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
