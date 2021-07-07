/* Singly linked list */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Symbolic constants */

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define LIST_DATA_NOT_FOUND 2
#define LIST_EMPTY 3

/* typedefs */
typedef int data_t;
typedef int status_t;
typedef int len_t;
typedef int bool;
typedef struct node node_t;
typedef node_t list_t;

/* node layout defination */

struct node{
    data_t data;
    struct node *next;
};

/* interface routines declarations */

list_t* create_sll(void);

status_t insert_beg(list_t *p_list, data_t new_data);
status_t insert_end(list_t *p_list, data_t new_data);
status_t insert_after(list_t *p_list, data_t r_data, data_t new_data);
status_t insert_before(list_t *p_list, data_t r_data, data_t new_data);

status_t get_beg(list_t *p_list, data_t *p_data);
status_t get_end(list_t *p_list, data_t *p_data);
status_t pop_beg(list_t *p_list, data_t *p_data);
status_t pop_end(list_t *p_list, data_t *p_data);

status_t remove_beg(list_t *p_list);
status_t remove_end(list_t *p_list);
status_t remove_data(list_t *p_list, data_t r_data);

len_t get_length(list_t *p_list);
bool contains(list_t *p_list, data_t search_data);
bool is_list_empty(list_t *p_list);
node_t *get_location(list_t *p_list, data_t search_data);
int get_repeat_count(list_t *p_list, data_t search_data);
void show_list(list_t *p_list, const char *msg);

list_t *concat_lists(list_t *p_list1, list_t p_list2);
list_t *merge_lists(list_t *p_list1, list_t *p_list2);
list_t *get_reversed_list(list_t *p_list);
status_t list_to_array(list_t *p_list, data_t **pp_array, size_t *p_size);
list_t *array_to_list(list_t *p_list, data_t *p_array, size_t size);

status_t append_list(list_t *p_list1, list_t *p_list2);
status_t reverse_list(list_t *p_list);

status_t destroy_list(list_t *p_list);

/* list auxilary routines */
void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end);
void generic_delete(node_t *p_node_prev, node_t *p_delete_node);
node_t *get_list_node(data_t new_data);
node_t *locate_node(list_t *p_list, data_t search_data);
node_t *get_node(list_t *p_list, data_t e_data);
node_t *get_prev_node(list_t *p_list, data_t e_data);
node_t *get_prev_to_last_node(list_t *p_list);
node_t* get_last_node(list_t *p_list);

void *xmalloc(size_t size_in_bytes);

int main (void){
    list_t *p_list = NULL;
    p_list = create_sll();
    int data;
    status_t s;

    show_list(p_list, "Before insert_end(): ");
    for(data = 1; data <= 5; data++){
        s = insert_end(p_list, data);
        assert(s == SUCCESS);
    }
    show_list(p_list, "After insert_end(): ");
    
    for(data = 6; data <= 10; data++){
        s = insert_beg(p_list, data);
        assert(s == SUCCESS);
    }
    show_list(p_list, "After insert_beg(): ");

    s = insert_after(p_list, 5, 100);
    assert(s == SUCCESS);
    show_list(p_list, "After insert_after(): ");
    
    s = insert_before(p_list, 5, 200);
    assert(s == SUCCESS);
    show_list(p_list, "After insert_before(): ");

    s = get_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("beg_data: %d\n", data);

    s = get_end(p_list, &data);
    assert(s == SUCCESS);
    printf("end_data: %d\n", data);

    s = pop_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("poped begining: %d\n", data);
    show_list(p_list, "After pop_beg(): ");

    s = pop_end(p_list, &data);
    assert(s == SUCCESS);
    printf("poped end: %d\n", data);
    show_list(p_list, "After pop_end(): ");

    s = remove_beg(p_list);
    assert(s == SUCCESS);
    show_list(p_list, "After remove_beg(): ");
    
    s = remove_end(p_list);
    assert(s == SUCCESS);
    show_list(p_list, "After remove_end(): ");

    s = remove_data(p_list, 6);
    assert(s == SUCCESS);
    show_list(p_list, "After remove_data(6): ");

    return (EXIT_SUCCESS);
}

list_t* create_sll(void){
    node_t *p_new_node = NULL;
    p_new_node = get_list_node(0);
    p_new_node->next = NULL;
    return (p_new_node);
}

status_t insert_beg(list_t *p_list, data_t new_data){
    generic_insert(p_list, get_list_node(new_data), p_list->next);
    p_list->data ++;
    return (SUCCESS);
}

status_t insert_end(list_t *p_list, data_t new_data){
    node_t *p_run = p_list;
    while(p_run->next != NULL){
        p_run = p_run->next;
    }
    generic_insert(p_run, get_list_node(new_data), p_run->next);
    return (SUCCESS);
}

status_t insert_after(list_t *p_list, data_t e_data, data_t new_data){
    node_t *p_new_node = NULL;
    p_new_node = locate_node(p_list, e_data);
    generic_insert(p_new_node, get_list_node(new_data), p_new_node->next);
    return (SUCCESS);
}

status_t insert_before(list_t *p_list, data_t e_data, data_t new_data){
    node_t *p_run = NULL, *p_run_next = NULL;
    p_run = p_list->next;
    p_run_next = p_list->next->next;
    while(p_run_next != NULL){
        if(p_run_next->data == e_data){
            generic_insert(p_run, get_list_node(new_data), p_run->next);
            return (SUCCESS);
        }
        p_run = p_run->next;
        p_run_next = p_run_next->next;
    }
    return (FAILURE);
}

status_t get_beg(list_t *p_list, data_t *p_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    *p_data = p_list->next->data;
    return (SUCCESS);
}

status_t get_end(list_t *p_list, data_t *p_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    node_t *last_node = get_last_node(p_list);
    *p_data = last_node->data;
    return (SUCCESS);
}

status_t pop_beg(list_t *p_list, data_t *p_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    *p_data = p_list->next->data;
    generic_delete(p_list, p_list->next);
    return (SUCCESS);
}

status_t pop_end(list_t *p_list, data_t *p_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    node_t *last_node = get_last_node(p_list);
    node_t *prev_to_last_node = get_prev_to_last_node(p_list);
    *p_data = last_node->data;
    generic_delete(prev_to_last_node, last_node);
    return (SUCCESS);
}

status_t remove_beg(list_t *p_list){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }

    generic_delete(p_list, p_list->next);
    return (SUCCESS);
}

status_t remove_end(list_t *p_list){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    node_t *p_last_node = get_last_node(p_list);
    node_t *p_prev_to_last_node = get_prev_to_last_node(p_list);
    generic_delete(p_prev_to_last_node, p_last_node);
    return (SUCCESS);
}

status_t remove_data(list_t *p_list, data_t r_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    node_t *prev_node = NULL;
    prev_node = get_prev_node(p_list, r_data);
    node_t *remove_node = NULL;
    remove_node = get_node(p_list, r_data);
    generic_delete(prev_node, remove_node);
    return (SUCCESS);
}

void show_list(list_t *p_list, const char *msg){
    node_t *p_run = p_list->next;
    if(msg){
        puts(msg);
    }
    printf("[beg]->");
    while(p_run != NULL){
        printf("[%d]->", p_run->data);
        p_run = p_run->next;
    }
    puts("[end]\n");
}

bool is_list_empty(list_t *p_list){
    if(p_list->next == NULL){
        return (TRUE);
    }
    return (FALSE);
}

node_t* get_node(list_t *p_list, data_t e_data){
    return (locate_node(p_list, e_data));
}

node_t* get_prev_node(list_t *p_list, data_t e_data){
    node_t *p_run = p_list->next;
    node_t *p_run_next = p_list->next->next;
    while(p_run_next->data != e_data){
        p_run = p_run->next;
        p_run_next = p_run_next->next;
    }
    return (p_run);
}

node_t *get_prev_to_last_node(list_t *p_list){
    node_t *p_run = p_list->next;
    node_t *p_run_next = p_list->next->next;
    while(p_run_next->next != NULL){
        p_run = p_run->next;
        p_run_next = p_run_next->next;
    }
    return (p_run);
}

node_t* get_last_node(list_t *p_list){
    node_t *p_run = p_list->next;
    while(p_run->next != NULL){
        p_run = p_run->next;
    }
    return (p_run);
}

void generic_insert(node_t *p_node_beg, node_t *p_node_mid, node_t *p_node_end){
    p_node_beg->next = p_node_mid;
    p_node_mid->next = p_node_end;
}

void generic_delete(node_t *p_node_prev, node_t *p_delete_node){
    p_node_prev->next = p_delete_node->next;
    free(p_delete_node);
    p_delete_node = NULL;
}

node_t *locate_node(list_t *p_list, data_t search_data){
    node_t *p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == search_data){
            return (p_run);
        }
        p_run = p_run->next;
    }
    return (NULL);
}

node_t *get_list_node(data_t new_data){
    node_t *p_new_node = NULL;
    p_new_node = (node_t *)xmalloc(sizeof(node_t));
    p_new_node->next = NULL;
    p_new_node->data = new_data;
    return (p_new_node);
}

void *xmalloc(size_t size_in_bytes){
    void *p = NULL;
    p = malloc(size_in_bytes);
    assert(p != NULL);
    return p;
}