/* Singly circular linked list */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* symbolic constants */

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

/* node layout definition */

struct node {
    data_t data;
    struct node *prev;
    struct node *next;
};

/* interface routines declarations */

list_t* create_scll(void);

status_t insert_beg(list_t *p_list, data_t new_data);
status_t insert_end(list_t *p_list, data_t new_data);
status_t insert_after(list_t *p_list, data_t e_data, data_t new_data);
status_t insert_before(list_t *p_list, data_t e_data, data_t new_data);

status_t get_beg(list_t *p_list, data_t *p_data);
status_t get_end(list_t *p_list, data_t *p_data);
status_t pop_beg(list_t *p_list, data_t *p_data);
status_t pop_end(list_t *p_list, data_t *p_data);

status_t remove_beg(list_t *p_list);
status_t remove_end(list_t *p_list);
status_t remove_data(list_t *p_list);

len_t get_length(list_t *p_list);
bool contains(list_t *p_list, data_t search_data);
bool is_list_empty(list_t *p_list);
node_t* get_location(list_t *p_list, data_t search_data);
int get_repeat_count(list_t *p_list, data_t search_data);
void show_list(list_t *p_list, const char* msg);

list_t* concat_lists(list_t *p_list1, list_t *p_list2);
list_t* merge_lists(list_t *p_list1, list_t *p_list2);
list_t* get_reversed_list(list_t *p_list);
status_t list_to_array(list_t *p_list, data_t **pp_array, len_t *len);
list_t* array_to_list(data_t *p_array, len_t len);

status_t append_list(list_t *p_list1, list_t *p_list2);
status_t reverse_list(list_t *p_list);
status_t destroy_list(list_t **pp_list);

/* auxilary routines */
void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end);
void generic_delete(node_t *p_prev_node);
node_t* locate_node(list_t *p_list, data_t serach_data);
node_t* get_list_node(data_t new_data);
node_t* get_prev_node_location(list_t *p_list, data_t search_data);
node_t *get_prev_to_last_node(list_t *p_list);
node_t* get_last_node(list_t *p_list);

/* memory allocation routines */
void* xmalloc(size_t size_in_bytes);

int main(void){
    list_t *p_list = NULL, *p_list1 = NULL, *p_list2 = NULL;
    list_t *p_concat_list = NULL, *p_reversed_list = NULL, *p_merged_list = NULL, *p_array_to_list = NULL;
    p_list = create_scll();
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

    p_list1 = create_scll();
    p_list2 = create_scll();
    for(data = 1; data < 10; data ++){
        insert_end(p_list1, (data * 10));
        insert_end(p_list2, (data * 10) + 5);
    }

    show_list(p_list1, "list1: ");
    show_list(p_list2, "list2: ");

    p_concat_list = concat_lists(p_list1, p_list2);
    show_list(p_concat_list, "list1 and list2 are concatinated: ");

    p_merged_list = merge_lists(p_list1, p_list2);
    show_list(p_merged_list, "list1 and list2 are merged: ");

    show_list(p_list, "list p_list: ");
    p_reversed_list = get_reversed_list(p_list);
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
    node_t *p_last_node = NULL;
    p_last_node = get_last_node(p_list);
    generic_insert(p_last_node, get_list_node(new_data), p_list);
    return (SUCCESS);   
}

status_t insert_after(list_t *p_list, data_t e_data, data_t new_data){
    node_t *p_node = NULL;
    p_node = get_location(p_list, e_data);
    assert(p_node != NULL);
    generic_insert(p_node, get_list_node(new_data), p_node->next);
    return (SUCCESS);
}
 
status_t insert_before(list_t *p_list, data_t e_data, data_t new_data){
    node_t *p_prev_node = get_prev_node_location(p_list, e_data);
    assert(p_prev_node != NULL);
    generic_insert(p_prev_node, get_list_node(new_data), p_prev_node->next);
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
    node_t *p_last_node = get_last_node(p_list);
    *end_data = p_last_node->data;
    return (SUCCESS);
}

status_t pop_beg(list_t *p_list, data_t *poped_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    *poped_data = p_list->next->data;
    generic_delete(p_list);
    return (SUCCESS); 
}

status_t pop_end(list_t *p_list, data_t *poped_data){
    if(is_list_empty(p_list)){
        return (FAILURE);
    }
    node_t *p_prev_node = get_prev_to_last_node(p_list);
    *poped_data = p_prev_node->next->data;
    generic_delete(p_prev_node);
    return (SUCCESS);
}

node_t* get_location(list_t *p_list, data_t search_data){
    return (locate_node(p_list, search_data));
}

len_t get_length(list_t *p_list){
    if(is_list_empty(p_list)){
        return (0);
    }
    node_t *p_run = p_list->next;
    len_t len = 0;
    while(p_run != p_list){
        len ++;
        p_run = p_run->next;
    }
    return len;
}

bool contains(list_t *p_list, data_t search_data){
    node_t *p_run = p_list->next;
    while(p_run != p_list){
        if(p_run->data == search_data){
            return (TRUE);
        }
        p_run = p_run->next;
    }
    return (FALSE);
}

int get_repeat_count(list_t *p_list, data_t search_data){
    if(is_list_empty(p_list)){
        return (0);
    }
    int repeat_count = 0;
    node_t *p_run = p_list->next;
    while(p_run != p_list){
        if(p_run->data == search_data){
            repeat_count ++;
        }
        p_run = p_run->next;
    }
    return (repeat_count);
}

list_t *concat_lists(list_t *p_list1, list_t *p_list2){
    list_t *p_new_list = NULL;
    p_new_list = create_scll();
    assert(p_new_list != NULL);
    status_t s;
    node_t *p_run = NULL;
    p_run = p_list1->next;
    while(p_run != p_list1){
        s = insert_end(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    p_run = p_list2->next;
    while(p_run != p_list2){
        s = insert_end(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }

    return (p_new_list);
}

list_t* merge_lists(list_t *p_list1, list_t *p_list2){
    list_t *p_new_list = NULL;
    p_new_list = create_scll();
    assert(p_new_list != NULL);
    node_t *p_run1 = NULL, *p_run2 = NULL;
    p_run1 = p_list1->next;
    p_run2 = p_list2->next;
    status_t s;

    while(TRUE){
        if(p_run1 == p_list1){
            while(p_run2 != p_list2){
                s = insert_end(p_new_list, p_run2->data);
                assert(s == SUCCESS);
                p_run2 = p_run2->next;
            }
            break;
        }
        if(p_run2 == p_list2){
            while(p_run1 != p_list1){
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
        else {
            s = insert_end(p_new_list, p_run2->data);
            assert(s == SUCCESS);
            p_run2 = p_run2->next;
        }
    }
    return p_new_list;
}

list_t* get_reversed_list(list_t *p_list){
    list_t *p_new_list = NULL;
    p_new_list = create_scll();
    assert(p_new_list != NULL);
    status_t s;
    node_t *p_run = p_list->next;
    while(p_list != p_run){
        s = insert_beg(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    return (p_new_list);
}

list_t* array_to_list(data_t *p_array, len_t len){
    list_t *p_new_list = NULL;
    p_new_list = create_scll();
    assert(p_new_list != NULL);
    status_t s;
    int i;
    for(i=0; i<len; i++){
        s = insert_end(p_new_list, *(p_array + i));
        assert(s == SUCCESS);
    }

    return p_new_list;
}

status_t list_to_array(list_t *p_list, data_t **pp_array, len_t *len){
    node_t *p_run = NULL;
    p_run = p_list->next;
    data_t *p_array = NULL;
    int i = 0;
    len_t list_len = get_length(p_list);
    p_array = (data_t *)xmalloc(sizeof(data_t) * list_len);
    while(p_run != p_list){
        *(p_array + i) = p_run->data;
        i++;
        p_run = p_run->next;
    }
    *pp_array = p_array;
    *len = list_len;
    return (SUCCESS);
}

status_t append_list(list_t *p_list1, list_t *p_list2){
    node_t *p_list_node = NULL;
    node_t *p_last_node_list1 = NULL;
    node_t *p_last_node_list2 = NULL;
    p_last_node_list1 = get_last_node(p_list1);
    p_last_node_list2 = get_last_node(p_list2);
    p_last_node_list1->next = p_list2->next;
    p_last_node_list2->next = p_list1;
    free(p_list2);
    return (SUCCESS);
}

status_t reverse_list(list_t *p_list){
    node_t *p_node = NULL, *p_run = NULL;
    node_t *p_last_node = NULL, *p_new_node = NULL;
    p_last_node = get_last_node(p_list);
    p_new_node = p_list;
    p_run = p_list->next;
    int i = 0;
    while(p_run != p_last_node){
        p_node = p_run;
        p_list->next = p_list->next->next;
        generic_insert(p_last_node, p_node, p_new_node);
        p_new_node = p_node;
        p_run = p_list->next;
    }
    return (SUCCESS);
}

node_t* locate_node(list_t *p_list, data_t search_data){
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

node_t* get_prev_node_location(list_t *p_list, data_t search_data){
    node_t *p_run, *p_run_prev;
    p_run = p_list->next;
    p_run_prev = p_list;
    while(p_run != p_list){
        if(p_run->data == search_data){
            return (p_run_prev);
        }
        p_run_prev = p_run;
        p_run = p_run->next;
    }
    return (NULL);
}

node_t* get_last_node(list_t *p_list){
    node_t *p_run = NULL;
    p_run = p_list->next;
    while(p_run->next != p_list){
        p_run = p_run->next;
    }
    return (p_run);
}

node_t* get_prev_to_last_node(list_t *p_list){
    node_t *p_run = NULL, *p_prev = NULL;
    p_run = p_list->next;
    while(p_run->next != p_list){
        p_prev = p_run;
        p_run = p_run->next;
    }
    return (p_prev);
}

void show_list(list_t *p_list, const char *msg){
    if(msg){
        puts(msg);
    }
    node_t *p_run = p_list->next;
    printf("[beg]->");
    while(p_run != p_list){
        printf("[%d]->", p_run->data);
        p_run = p_run->next;
    }
    printf("[end]\n");
}

node_t* get_list_node(data_t new_data){
    node_t *p_node = NULL;
    p_node = (node_t*)xmalloc(sizeof(node_t));
    assert(p_node != NULL);
    p_node->data = new_data;
    p_node->next = NULL;
    return (p_node);
}

bool is_list_empty(list_t *p_list){
    if(p_list->next == p_list){
        return (TRUE);
    }

    return (FALSE);
}

void generic_insert(node_t *p_node_beg, node_t *p_node_mid, node_t *p_node_last){
    p_node_beg->next = p_node_mid;
    p_node_mid->next = p_node_last;
}

void generic_delete(node_t *p_node_prev){
    node_t *p_delete_node = NULL;
    p_delete_node = p_node_prev->next;
    p_node_prev->next = p_node_prev->next->next;
    free(p_delete_node);
}

list_t* create_scll(){
    list_t *p_new_list = NULL;
    p_new_list = get_list_node(0);
    assert(p_new_list != NULL);
    p_new_list->next = p_new_list;
    return (p_new_list);
}

status_t destroy_list(list_t **pp_list){
    list_t *p_list = *pp_list;
    node_t *p_run, *p_run_next;
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

void* xmalloc(size_t size_in_bytes){
    void *p = NULL;
    p = malloc(size_in_bytes);
    assert(p != NULL);
    return (p);
}