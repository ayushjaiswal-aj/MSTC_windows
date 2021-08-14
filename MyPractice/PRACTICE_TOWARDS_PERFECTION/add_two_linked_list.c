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
typedef int carry_t;
typedef int bool;
typedef struct list_node node_t;
typedef node_t list_t;

struct list_node {
    data_t data;
    struct list_node *next;
    struct list_node *prev;
};

status_t add_list(list_t *p_list1, list_t *p_list2, list_t *p_list_sum);
carry_t add_node(node_t *p_node1, node_t *p_node2, data_t *sum, carry_t *carry);

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
void generic_delete(node_t *p_delete_node);

/* memory auxillary routine */
void* xcalloc(int nr_elements, int size_per_element);

int main(void){
    list_t *p_list1 = NULL;
    list_t *p_list2 = NULL;
    list_t *p_list_sum = NULL;
    node_t *p_fork_node = NULL;
    int fork_point;
    status_t s;
    data_t data;
    int i;

    p_list1 = create_list();
    p_list2 = create_list();
    p_list_sum = create_list();
    
    for(i = 1; i <= 9; i++){
        insert_end(p_list1, i);
    }

    for (i = 9; i >= 1; i--){
        insert_end(p_list2, i);
    }
    printf("list1: ");
    show_list(p_list1);
    printf("list2: ");
    show_list(p_list2);

    add_list(p_list1, p_list2, p_list_sum);

    printf("list_sum: ");
    show_list(p_list_sum);

    return (EXIT_SUCCESS);
}

status_t add_list(list_t *p_list1, list_t *p_list2, list_t *p_list_sum){
    node_t *p_node1 = NULL;
    node_t *p_node2 = NULL;
    data_t sum = 0;
    carry_t carry = 0;
    p_node1 = p_list1->prev;
    p_node2 = p_list2->prev;

    while (!(p_node1 == p_list1 && p_node2 == p_list2)){
        if(add_node(p_node1, p_node2, &sum, &carry) != SUCCESS){
            return (FAILURE);
        }

        insert_beg(p_list_sum, sum);

        if(p_list1 == p_node1){
            p_node2 = p_node2->prev;
        }
        else if(p_list2 == p_node2){
            p_node1 = p_node1->prev;
        }
        else {
            p_node1 = p_node1->prev;
            p_node2 = p_node2->prev;
        }
    }
    if(carry == 1){
        insert_beg(p_list_sum, carry);
    }
    return (SUCCESS);
}

status_t add_node(node_t *p_node1, node_t *p_node2, data_t *sum, carry_t *c){
    *sum = p_node1->data + p_node2->data + *c;
    if(*sum > 9){
        *c = 1;
        *sum  = *sum % 10;
    }
    return SUCCESS;
}

/* list interface */
void show_list(list_t *p_list){
    node_t *p_run = NULL;
    p_run = p_list->next;
    printf("[head]->");
    while(p_run != p_list){
        printf("[%d]->", p_run->data);
        p_run = p_run->next;
    }
    printf("[end]\n");
}

list_t* create_list(){
    list_t *p_new_list = NULL;
    p_new_list = get_list_node(0);
    p_new_list->next = p_new_list;
    p_new_list->prev = p_new_list;
    return (p_new_list);
}

status_t destroy_list(list_t **pp_list){
    node_t *p_run = NULL;
    node_t *p_run_next = NULL;
    list_t *p_list = NULL;
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

/* list auxillary */
node_t* get_list_node(data_t data){
    node_t *p_new_node = NULL;
    p_new_node = (node_t*)xcalloc(1, sizeof(node_t));
    p_new_node->data = data;
    p_new_node->next = NULL;
    p_new_node->prev = NULL;
    return p_new_node;
}

node_t* get_last_node(list_t *p_list){
    return p_list->prev;
}

node_t* get_data_node(list_t *p_list, data_t search_data){
    node_t *p_run = NULL;
    p_run = p_list->next;
    while(p_run != p_list){
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
    p_end->prev = p_mid;
    p_mid->prev = p_beg;
}

void generic_delete(node_t *p_delete_node){
    p_delete_node->next->prev = p_delete_node->prev;
    p_delete_node->prev->next = p_delete_node->next;
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
