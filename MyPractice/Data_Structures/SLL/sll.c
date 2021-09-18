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

list_t *concat_lists(list_t *p_list1, list_t *p_list2);
list_t *merge_lists(list_t *p_list1, list_t *p_list2);
list_t *get_reversed_list(list_t *p_list);
status_t list_to_array(list_t *p_list, data_t **pp_array, size_t *p_size);
list_t *array_to_list(data_t *p_array, len_t len);

status_t append_list(list_t *p_list1, list_t *p_list2);
status_t reverse_list(list_t *p_list);
status_t reverse_list_recurrsive(list_t *p_list);

status_t destroy_list(list_t **p_list);

/* list auxilary routines */
void __recursive_reverse(node_t *p_curr, node_t *p_prev);
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
    list_t *p_list1 = NULL, *p_list2 = NULL;
    list_t *p_concat_lists = NULL, *p_merged_list = NULL;
    list_t *p_reversed_list = NULL;
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

    printf("lenght of p_list = %d\n", get_length(p_list));

    if(contains(p_list, 7)){
        printf("list contains 7\n");
    }

    printf("repeat count of 8 = %d\n", get_repeat_count(p_list, 8));

    p_list1 = create_sll();
    p_list2 = create_sll();
    p_concat_lists = create_sll();
    p_merged_list = create_sll();

    for(data = 1; data <= 10; data++){
        s = insert_end(p_list1, data * 10);
        assert(s == SUCCESS);
        s = insert_end(p_list2, (data * 10) + 5);
        assert(s == SUCCESS);
    }

    show_list(p_list1, "list1: ");
    show_list(p_list2, "list2: ");

    p_concat_lists = concat_lists(p_list1, p_list2);
    show_list(p_concat_lists, "concat version of list1 and list2: ");
    p_merged_list = merge_lists(p_list1, p_list2);
    show_list(p_merged_list, "merged version of list1 and list2: ");

    p_reversed_list = create_sll();
    p_reversed_list = get_reversed_list(p_list1);
    show_list(p_reversed_list, "reversed version of list1: ");

    s = append_list(p_list1, p_list2);
    assert(s == SUCCESS);
    show_list(p_list1, "list2 is appended to list1: ");

    show_list(p_list, "list before reversing");
    s = reverse_list(p_list);
    assert(s == SUCCESS);
    show_list(p_list, "list after reversing: ");

    s = reverse_list_recurrsive(p_list);
    assert(s == SUCCESS);
    show_list(p_list, "list after recursive reversing");

    destroy_list(&p_list);
    destroy_list(&p_list1);
    destroy_list(&p_reversed_list);

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

len_t get_length(list_t *p_list){
    node_t *p_run = p_list->next;
    len_t len = 0;
    while(p_run != NULL){
        len++;
        p_run = p_run->next;
    }
    return (len);
}

bool contains(list_t *p_list, data_t search_data){
    node_t *p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == search_data){
            return TRUE;
        }
        p_run = p_run->next;
    }
    return FALSE;
}

int get_repeat_count(list_t *p_list, data_t search_data){
    int repeat_count = 0;
    node_t *p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == search_data){
            repeat_count++;
        }
        p_run = p_run->next;
    }
    return repeat_count;
}

list_t* concat_lists(list_t *p_list1, list_t *p_list2){
    list_t *new_list = NULL;
    new_list = create_sll();
    assert(new_list != NULL);
    status_t s;
    node_t *p_run = p_list1->next;

    printf("before inserting\n");
    while(p_run != NULL){
        s = insert_end(new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    p_run = p_list2->next;

    while(p_run != NULL){
        s = insert_end(new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }

    return new_list;
}

list_t* merge_lists(list_t *p_list1, list_t *p_list2){
    list_t *p_merge_list = NULL;
    p_merge_list = create_sll();
    node_t *p_run1 = p_list1->next, *p_run2 = p_list2->next;
    while(TRUE){
        if(p_run1->data <= p_run2->data){
            insert_end(p_merge_list, p_run1->data);
            p_run1 = p_run1->next;
        }
        else {
            insert_end(p_merge_list, p_run2->data);
            p_run2 = p_run2->next;
        }

        if(p_run1 == NULL){
            while(p_run2 != NULL){
                insert_end(p_merge_list, p_run2->data);
                p_run2 = p_run2->next;
            }
            break;
        }
        if(p_run2 == NULL){
            while(p_run1 != NULL){
                insert_end(p_merge_list, p_run1->data);
                p_run1 = p_run1->next;
            }
            break;
        }
    }
    return p_merge_list;
}

list_t *get_reversed_list(list_t *p_list){
    list_t *p_reversed_list = create_sll();
    node_t *p_run = p_list->next;
    status_t s;
    while(p_run != NULL){
        s = insert_beg(p_reversed_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    return (p_reversed_list);
}

status_t list_to_array(list_t *p_list, data_t **pp_array, size_t *p_size){
    data_t *p_array = NULL;
    len_t len;
    len = get_length(p_list);
    node_t *p_run = p_list->next;
    int i;
    p_array = (data_t *)xmalloc(len * sizeof(data_t));
    for(i = 0; i < len; i++){
        p_array[i] = p_run->data;
        p_run = p_run->next;
    }
    *pp_array = p_array;
    *p_size = len;
    return (SUCCESS);
}

list_t* array_to_list(data_t *p_array, len_t len){
    list_t *p_list = create_sll();
    int i;
    status_t s;
    for(i = 0; i < len; i ++){
        s = insert_end(p_list, *(p_array + i));
        assert(s == SUCCESS);
    }
    return (p_list);
}

status_t append_list(list_t *p_list1, list_t *p_list2){
    node_t *p_run = NULL;
    p_run = get_last_node(p_list1);
    p_run->next = p_list2->next;
    free(p_list2);
    p_list2 = NULL;
    return (SUCCESS);
}

status_t reverse_list(list_t *p_list){
    node_t *p_run = NULL;
    node_t *p_run_next = NULL;
    node_t *p_new_node = NULL;
    node_t *p_last_node = NULL;
    p_last_node = get_last_node(p_list);
    p_new_node = p_list->next;
    p_list->next = p_list->next->next;
    p_run = p_list->next;
    p_last_node->next = p_new_node;
    p_new_node->next = NULL;
    while(p_run != p_last_node){
        p_run_next = p_run->next;
        generic_insert(p_last_node, p_run, p_new_node);
        p_new_node = p_run;
        p_run = p_run_next;
    }
    p_list->next = p_last_node;
    return (SUCCESS);
}

status_t reverse_list_recurrsive(list_t *p_list){
    __recursive_reverse(p_list, p_list->next, p_list->next->next);
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

void __recursive_reverse(list_t *p_list, node_t *p_curr, node_t *p_next){
    if(p_next == NULL){
        return;
    }
    p_list->next = p_next;
    p_curr->next = NULL;
    __recursive_reverse(p_list, p_next, p_next->next);
    p_next->next = p_curr;
    
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

status_t destroy_list(list_t **pp_list){
    list_t *p_list = *pp_list;
    node_t *p_run = p_list->next, *p_run_next;
    while(p_run != NULL){
        p_run_next = p_run->next;
        free(p_run);
        p_run = p_run_next;
    }
    free(p_list);
    *pp_list = NULL;
    return (SUCCESS);
}