#ifndef _SCLL_H
#define _SCLL_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0
#define LIST_EMPTY 3
#define LIST_NODE_NOW_FOUND  2

typedef int data_t;
typedef int status_t;
typedef int bool;
typedef int len_t;
typedef struct scll_node scll_node_t;
typedef scll_node_t scll_list_t;

struct scll_node{
    data_t data;
    struct scll_node *next;
};

status_t scll_insert_beg(scll_list_t *p_list, data_t new_data);
status_t scll_insert_end(scll_list_t *p_list, data_t new_data);
status_t scll_insert_after(scll_list_t *p_list, data_t e_data, data_t new_data);
status_t scll_insert_before(scll_list_t *p_list, data_t e_data, data_t new_data);

status_t scll_get_beg(scll_list_t *p_list, data_t *p_data);
status_t scll_get_end(scll_list_t *p_list, data_t *p_data);

status_t scll_pop_beg(scll_list_t *p_list, data_t *p_data);
status_t scll_pop_end(scll_list_t *p_list, data_t *p_data);

status_t scll_remove_beg(scll_list_t *p_list);
status_t scll_remove_end(scll_list_t *p_list);
status_t scll_remove_data(scll_list_t *p_list, data_t r_data);

bool scll_is_list_empty(scll_list_t *p_list);
bool scll_contains(scll_list_t *p_list, data_t e_data);
len_t scll_get_length(scll_list_t *p_list);
scll_node_t* scll_locate_node(scll_list_t *p_list, data_t e_data);

int scll_repeat_count(scll_list_t *p_list, data_t e_data);

scll_list_t* scll_merge_lists(scll_list_t *p_list1,scll_list_t *p_list2);
scll_list_t* scll_concat_lists(scll_list_t *p_list1,scll_list_t *p_list2);
scll_list_t* scll_reversed_list(scll_list_t *p_list);
scll_list_t* scll_array_to_list(data_t *p_array, len_t len);

status_t scll_list_to_array(scll_list_t *p_list, data_t **pp_data, len_t *len);
status_t scll_reverse_list(scll_list_t *p_list);
status_t scll_append_list(scll_list_t *p_list1, scll_list_t *p_list2);

scll_node_t* scll_get_location(scll_list_t *p_list, data_t e_data);
scll_node_t* scll_get_prev_location(scll_list_t *p_list, data_t e_data);
scll_node_t* scll_get_last_node(scll_list_t *p_list);
scll_node_t* scll_get_prev_to_last_node(scll_list_t *p_list);

void scll_show_list(scll_list_t *p_list, const char* msg);

void scll_generic_insert(scll_node_t *p_beg_node, scll_node_t *p_mid_node, scll_node_t *p_end_node);
void scll_generic_delete(scll_node_t *p_prev_node, scll_node_t *p_delete_node);

scll_node_t* scll_get_list_node(data_t new_data);
scll_list_t* create_scll();
status_t destroy_scll(scll_list_t **pp_list);

void* xmalloc(size_t size_in_bytes);

#endif