/* doubly linked list */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* symbolic constants */
#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0
#define LIST_EMPTY 2
#define LIST_DATA_NOT_FOUND 3

/* typedefs */

typedef int data_t;
typedef int status_t;
typedef int len_t;
typedef int bool;
typedef struct node node_t;
typedef node_t list_t;

struct node {
    data_t data;
    struct node *next;
    struct node *prev;
};

list_t* create_dll(void);
status_t destroy_list(list_t **p_list);

status_t insert_beg(list_t *p_list, data_t new_data);
status_t insert_end(list_t *p_list, data_t new_data);
status_t insert_after(list_t *p_list, data_t e_data, data_t new_data);
status_t insert_before(list_t *p_list, data_t e_data, data_t new_data);

status_t remove_beg(list_t *p_list);
status_t remove_end(list_t *p_list);
status_t remove_data(list_t *p_List, data_t r_data);

status_t get_beg(list_t *p_list, data_t *beg_data);
status_t get_end(list_t *p_list, data_t *end_data);
status_t pop_beg(list_t *p_list, data_t *poped_data);
status_t pop_end(list_t *p_list, data_t *poped_data);

bool is_list_empty(list_t *p_list);
bool contains(list_t *p_list, data_t search_data);
node_t* locate_node(list_t *p_list, data_t search_data);
len_t get_length(list_t *p_list);
int get_repeat_count(list_t *p_list, data_t search_data);
void show_list(list_t *p_list, const char* msg);

list_t* concat_lists(list_t *p_list1, list_t *p_list2);
list_t* merge_lists(list_t *p_list1, list_t *p_list2);
list_t* reversed_list(list_t *p_list);
list_t* array_to_list(data_t *p_array, len_t len);
status_t list_to_array(list_t *p_list, data_t **pp_array, len_t *len);

status_t append_list(list_t *p_list1, list_t *p_list2);
status_t reverse_list(list_t *p_list);

void generic_insert(node_t *p_node_beg, node_t *p_node_mid, node_t *p_node_end);
void generic_delete(node_t *p_delete_node);
node_t* get_node_location(list_t *p_list, data_t search_data);
node_t* get_list_node(data_t new_data);
node_t* get_last_node(list_t *p_list);
void* xmalloc(size_t size_in_bytes);

int main(void){
    list_t *p_list = NULL, *p_list1 = NULL, *p_list2 = NULL;
    list_t *p_concat_list = NULL, *p_reversed_list = NULL, *p_merged_list = NULL, *p_array_to_list = NULL;
    p_list = create_dll();
    status_t s;
    data_t data;

    show_list(p_list, "After create list: ");
    for(data = 1; data <= 10; data++){
        s = insert_beg(p_list, data);
        assert(s == SUCCESS);
    }
    show_list(p_list, "after insert_beg(): ");

    for(data = 11; data <= 20; data++){
        s = insert_end(p_list, data);
        assert(s == SUCCESS);
    }
    show_list(p_list, "After insert end(): ");

    s = insert_after(p_list, 20, 100);
    assert(s == SUCCESS);
    show_list(p_list, "after insert_after(): ");

    s = insert_before(p_list, 10, 200);
    assert(s  == SUCCESS);
    show_list(p_list, "after insert_before(): ");

    s = get_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("beg data of p_list = %d\n", data);

    s = get_end(p_list, &data);
    assert(s == SUCCESS);
    printf("end data of p_list = %d\n", data);

    s = pop_beg(p_list, &data);
    assert(s == SUCCESS);
    printf("begining poped data: %d\n", data);
    show_list(p_list, "pop_bed(): ");

    s = pop_end(p_list, &data);
    assert(s == SUCCESS);
    printf("end poped data: %d\n", data);
    show_list(p_list, "after pop_end(): ");

    printf("length of p_list = %d\n", get_length(p_list));

    printf("repeat count of 8 is: %d\n", get_repeat_count(p_list, 8));

    p_list1 = create_dll();
    p_list2 = create_dll();
    
    for(data = 1; data < 10; data ++){
        s = insert_end(p_list1, (data * 10));
        assert(s == SUCCESS);
        s = insert_end(p_list2, (data * 10) + 5);
        assert(s == SUCCESS);
    }

    show_list(p_list1, "list1: ");
    show_list(p_list2, "list2: ");

    p_concat_list = concat_lists(p_list1, p_list2);
    show_list(p_concat_list, "list1 and list2 are concatinated: ");

    p_merged_list = merge_lists(p_list1, p_list2);
    show_list(p_merged_list, "list1 and list2 are merged: ");

    show_list(p_list, "list p_list: ");
    p_reversed_list = reversed_list(p_list);
    show_list(p_reversed_list, "reversed version of p_list: ");

    s = append_list(p_list1, p_list2);
    assert(s == SUCCESS);
    show_list(p_list1, "list2 is appended to list1: ");

    s = reverse_list(p_list1);
    assert(s == SUCCESS);
    show_list(p_list1, "after reversing p_list1: ");

    return (EXIT_SUCCESS);
}

status_t insert_beg(list_t *p_list, data_t new_data){
    generic_insert(p_list, get_list_node(new_data), p_list->next);
    return (SUCCESS);
}

status_t insert_end(list_t *p_list, data_t new_data){
    node_t *p_last_node = get_last_node(p_list);
    generic_insert(p_last_node, get_list_node(new_data), p_last_node->next);
    return (SUCCESS);
}

status_t insert_after(list_t *p_list, data_t e_data, data_t new_data){
    node_t *p_e_node = NULL;
    p_e_node = get_node_location(p_list, e_data);
    generic_insert(p_e_node, get_list_node(new_data), p_e_node->next);
    return (SUCCESS);
}

status_t insert_before(list_t *p_list, data_t e_data, data_t new_data){
    node_t *p_e_node = NULL;
    p_e_node = get_node_location(p_list, e_data);
    generic_insert(p_e_node->prev, get_list_node(new_data), p_e_node);
    return (SUCCESS);
}

status_t remove_beg(list_t *p_list){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    generic_delete(p_list->next);
    return (SUCCESS);
}

status_t remove_end(list_t *p_list){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    generic_delete(get_last_node(p_list));
    return (SUCCESS);
}

status_t remove_data(list_t *p_list, data_t r_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    node_t *p_node = NULL;
    p_node = get_node_location(p_list, r_data);
    generic_delete(p_node);
    return (SUCCESS);
}

status_t get_beg(list_t *p_list, data_t *beg_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    *beg_data = p_list->next->data;
    return (SUCCESS);
}

status_t get_end(list_t *p_list, data_t *end_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    node_t *p_node = get_last_node(p_list);
    *end_data = p_node->data;
    return (SUCCESS);
}

status_t pop_beg(list_t *p_list, data_t *poped_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    *poped_data = p_list->next->data;
    generic_delete(p_list->next);
    return (SUCCESS);
}

status_t pop_end(list_t *p_list, data_t *poped_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    node_t *p_last_node = get_last_node(p_list);
    *poped_data =p_last_node->data;
    generic_delete(p_last_node);
    return (SUCCESS);
}

bool is_list_empty(list_t *p_list){
    if(p_list->next == NULL && p_list->prev == NULL){
        return (TRUE);
    }
    return(FALSE);
}

bool contains(list_t *p_list, data_t search_data){
    if(is_list_empty(p_list)){
        return (FALSE);
    }
    node_t *p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data = search_data){
            return TRUE;
        }
    }
    return(FALSE);
}

len_t get_length(list_t *p_list){
    if(is_list_empty(p_list)){
        return (0);
    }
    len_t len = 0;
    node_t *p_run = p_list->next;
    while(p_run != NULL){
        len++;
        p_run = p_run->next;
    }
    return (len);
}

int get_repeat_count(list_t *p_list, data_t search_data){
    if(is_list_empty(p_list)){
        return (0);
    }
    int repeat_count = 0;
    node_t *p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == search_data){
            repeat_count ++;
        }
        p_run = p_run->next;
    }
    return (repeat_count);
}

void show_list(list_t *p_list, const char *msg){
    if(msg){
        puts(msg);
    }
    node_t *p_node = p_list->next;
    printf("[beg]<->");
    while(p_node != NULL){
        printf("[%d]->", p_node->data);
        p_node = p_node->next;
    }
    printf("[end]\n");
}

node_t* locate_node(list_t *p_list, data_t search_data){
    return (get_node_location(p_list, search_data));
}

list_t* concat_lists(list_t *p_list1, list_t *p_list2){
    list_t *p_new_list = NULL;
    p_new_list = create_dll();
    node_t *p_run = p_list1->next;
    status_t s;
    while(p_run != NULL){
        s = insert_end(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    p_run = p_list2->next;
    while(p_run != NULL){
        s = insert_end(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    return (p_new_list);
}

list_t* merge_lists(list_t *p_list1, list_t *p_list2){
    list_t *p_new_list = NULL;
    p_new_list = create_dll();
    node_t *p_run1 = p_list1->next, *p_run2 = p_list2->next;
    status_t s;
    while(TRUE){
        if(p_run1 == NULL){
            while(p_run2 != NULL){
                s = insert_end(p_new_list, p_run2->data);
                assert(s == SUCCESS);
                p_run2 = p_run2->next;
            }
            break;
        }
        if(p_run2 == NULL){
            while(p_run1 != NULL){
                s = insert_end(p_new_list, p_run1->data);
                assert(s == SUCCESS);
                p_run1 = p_run1->next;
            }
            break;
        }
        if(p_run1->data <= p_run2->data){
            s = insert_end(p_new_list, p_run1->data);
            assert(s == SUCCESS);
            p_run1 = p_run1->next;
        }
        else{
            s = insert_end(p_new_list, p_run2->data);
            assert(s == SUCCESS);
            p_run2 = p_run2->next;
        }
    }
    return (p_new_list);
}

list_t* reversed_list(list_t *p_list){
    list_t *p_new_list = NULL;
    p_new_list = create_dll();
    node_t *p_run = p_list->next;
    status_t s;
    while(p_run != NULL){
        s = insert_beg(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    return (p_new_list);
}

list_t* array_to_list(data_t *p_array, len_t len){
    list_t *p_new_list = create_dll();
    int i;
    status_t s;
    for(i = 0; i<len; i++){
        s = insert_end(p_new_list, *(p_array + i));
        assert(s == SUCCESS);
    }
    return (p_new_list);
}

status_t list_to_array(list_t *p_list, data_t **pp_array, len_t *len){
    len_t list_len = get_length(p_list);
    data_t *p_array = NULL;
    p_array = (data_t *)xmalloc(sizeof(data_t) * list_len);
    node_t *p_run = p_list->next;
    int i = 0;
    while(p_run != NULL){
        *(p_array + i) = p_run->data;
        p_run = p_run->next;
        i++;
    }
    *len = list_len;
    *pp_array = p_array;
    return (SUCCESS);
}


status_t append_list(list_t *p_list1, list_t *p_list2){
    node_t *p_last_node_list1 = NULL;
    p_last_node_list1 = get_last_node(p_list1);
    p_last_node_list1->next = p_list2->next;
    p_list2->next->prev = p_last_node_list1;
    return (SUCCESS);
}

status_t reverse_list(list_t *p_list){
    node_t *p_node = NULL;
    node_t *p_next_node = NULL;
    node_t *p_run = p_list->next;
    p_list->next->prev = NULL;
    while(p_run != NULL){
        p_next_node = p_run;
        p_run = p_run->next;
        p_node = p_next_node->next;
        p_next_node->next = p_next_node->prev;
        p_next_node->prev = p_node;
    }
    p_list->next = p_next_node;
    return (SUCCESS);
}

list_t* create_dll(void){
    list_t *p_new_list = NULL;
    p_new_list = get_list_node(0);
    p_new_list->next = NULL;
    p_new_list->prev = NULL;
    return p_new_list;
}

status_t destroy_list(list_t **pp_list){
    node_t *p_run = NULL, *p_run_next = NULL;
    p_run = (*pp_list)->next;
    while(p_run != NULL){
        p_run_next = p_run->next;
        free(p_run);
        p_run = p_run_next;
    }
    free(*pp_list);
    *pp_list = NULL;
    return (SUCCESS);
}

node_t* get_list_node(data_t new_data){
    node_t *p_node = NULL;
    p_node = (node_t *)xmalloc(sizeof(node_t));
    assert(p_node != NULL);
    p_node->data = new_data;
    p_node->next = NULL;
    p_node->prev = NULL;
    return (p_node);
}

node_t* get_last_node(list_t *p_list){
    if(is_list_empty(p_list)){
        return (p_list);
    }
    node_t *p_run = NULL;
    p_run = p_list->next;
    while(p_run->next != NULL){
        p_run = p_run->next;
    }
    return p_run;
}

node_t* get_node_location(list_t *p_list, data_t search_data){
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

void generic_insert(node_t *p_node_beg, node_t *p_node_mid, node_t *p_node_end){
    p_node_mid->prev = p_node_beg;
    p_node_mid->next = p_node_end;
    p_node_beg->next = p_node_mid;
    if(p_node_end != NULL){
        p_node_end->prev = p_node_mid;
    }
}
void generic_delete(node_t *p_delete_node){
    p_delete_node->prev->next = p_delete_node->next;
    if(p_delete_node->next != NULL){
        p_delete_node->next->prev = p_delete_node->prev;
    }
    free(p_delete_node);
    p_delete_node = NULL;
}

void* xmalloc(size_t size_in_bytes){
    void *p = NULL;
    p = malloc(size_in_bytes);
    assert(p != NULL);
    return p;
}  