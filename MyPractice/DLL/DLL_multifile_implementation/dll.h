#ifndef _DLL_H
#define _DLL_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0
#define LIST_DATA_NOT_EMPTY 2
#define LIST_EMPTY 3

typedef int data_t;
typedef int status_t;
typedef int len_t;
typedef int bool;
typedef struct dll_node dll_node_t;
typedef dll_node_t dll_list_t;

struct dll_node{
    data_t data;
    struct dll_node *next;
    struct dll_node *prev;
};

status_t dll_insert_beg(dll_list_t *p_list, data_t new_data);
status_t dll_insert_end(dll_list_t *p_list, data_t new_data);
status_t dll_insert_after(dll_list_t *p_list, data_t e_data, data_t new_data);
status_t dll_insert_before(dll_list_t *p_list, data_t e_data, data_t new_data);

status_t dll_get_beg(dll_list_t *p_list, data_t *p_data);
status_t dll_get_end(dll_list_t *p_list, data_t *p_data);

status_t dll_pop_beg(dll_list_t *p_list, data_t *p_data);
status_t dll_pop_end(dll_list_t *p_list, data_t *p_data);

status_t dll_remove_beg(dll_list_t *p_list);
status_t dll_remove_end(dll_list_t *p_list);
status_t dll_remove_data(dll_list_t *p_list, data_t r_data);

bool dll_is_list_empty(dll_list_t *p_list);
bool dll_contains(dll_list_t *p_list, data_t e_data);
len_t dll_get_length(dll_list_t *p_list);
int dll_get_repeat_count(dll_list_t *p_list, data_t e_data);
dll_node_t* locate_node(dll_list_t *p_list, data_t e_data);

dll_list_t* dll_merge_lists(dll_list_t *p_list1, dll_list_t *p_list2);
dll_list_t* dll_concat_lists(dll_list_t *p_list1, dll_list_t *p_list2);
dll_list_t* dll_reversed_list(dll_list_t *p_list);
dll_list_t* dll_array_to_list(data_t *p_array, len_t len);

status_t dll_list_to_array(dll_list_t *p_list, data_t **pp_array, len_t *p_len);
status_t dll_reverse_list(dll_list_t *p_list);
status_t dll_append_lists(dll_list_t *p_list1, dll_list_t *p_list2);

void dll_show_list(dll_list_t *p_list, const char *msg);

dll_node_t* dll_get_last_node(dll_node_t *p_list);
dll_node_t* dll_get_node_location(dll_list_t *p_list, data_t e_data);

void dll_generic_insert(dll_node_t *p_node_beg, dll_node_t *p_node_mid, dll_node_t *p_node_end);
void dll_generic_delete(dll_node_t *p_delete_node);

dll_node_t* dll_get_list_node(data_t new_data);
dll_list_t* create_dll();
status_t destroy_dll(dll_list_t **pp_list);

void* xmalloc(size_t size_in_bytes);

#endif