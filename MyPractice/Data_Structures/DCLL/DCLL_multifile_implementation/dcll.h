#ifndef _DCLL_H
#define _DCLL_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0
#define LIST_DATA_NOT_FOUND 2
#define LIST_EMPTY  3

typedef int data_t;
typedef int status_t;
typedef int len_t;
typedef int bool;
typedef struct dcll_node dcll_node_t;
typedef dcll_node_t dcll_list_t;

struct dcll_node {
    data_t data;
    struct dcll_node *next;
    struct dcll_node *prev;
};

status_t dcll_insert_beg(dcll_list_t *p_list, data_t new_data);
status_t dcll_insert_end(dcll_list_t *p_list, data_t new_data);
status_t dcll_insert_after(dcll_list_t *p_list, data_t e_data, data_t new_data);
status_t dcll_insert_before(dcll_list_t *p_list, data_t e_data, data_t new_data);

status_t dcll_get_beg(dcll_list_t *p_list, data_t *p_data);
status_t dcll_get_end(dcll_list_t *p_list, data_t *p_data);
status_t dcll_pop_beg(dcll_list_t *p_list, data_t *p_data);
status_t dcll_pop_end(dcll_list_t *p_list, data_t *p_data);

status_t dcll_remove_beg(dcll_list_t *p_list);
status_t dcll_remove_end(dcll_list_t *p_list);
status_t dcll_remove_data(dcll_list_t *p_list, data_t r_data);

len_t dcll_get_length(dcll_list_t *p_list);
int dcll_get_repeat_count(dcll_list_t *p_list, data_t e_data);
bool dcll_contains(dcll_list_t *p_list, data_t e_data);
bool dcll_is_list_empty(dcll_list_t *p_list);
dcll_node_t* dcll_locate_node(dcll_list_t *p_list, data_t e_data);

dcll_list_t* dcll_concat_lists(dcll_list_t *p_list1, dcll_list_t *p_list2);
dcll_list_t* dcll_merge_lists(dcll_list_t *p_list1, dcll_list_t *plist2);
dcll_list_t* dcll_reversed_list(dcll_list_t *p_list);
dcll_list_t* dcll_array_to_list(data_t *p_array, len_t len);

status_t dcll_list_to_array(dcll_list_t *p_list, data_t **pp_array, len_t *p_len);
status_t dcll_append_lists(dcll_list_t *p_list1, dcll_list_t *p_list2);
status_t dcll_reverse_list(dcll_list_t *p_list);

dcll_node_t* dcll_get_node_location(dcll_list_t *p_list, data_t e_data);

void dcll_show_list(dcll_list_t *p_list, const char *msg);
void dcll_generic_insert(dcll_node_t* p_node_beg, dcll_node_t* p_node_mid, dcll_node_t* p_node_end);
void dcll_generic_delete(dcll_node_t* p_delete_node);

dcll_node_t* dcll_get_list_node(data_t new_data);
dcll_list_t* create_dcll();
status_t destroy_dcll(dcll_list_t **pp_list);

void* xmalloc(size_t size_in_bytes);

#endif