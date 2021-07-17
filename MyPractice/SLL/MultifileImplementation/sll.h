#ifndef _SLL_H
#define _SLL_H

#define SUCCESS 1
#define FAILURE 0

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define LIST_DATA_NOT_FOUND 2
#define LIST_EMPTY 3

typedef int data_t;
typedef int status_t;
typedef int len_t;
typedef int bool;
typedef struct sll_node sll_node_t;
typedef sll_node_t sll_list_t;

struct sll_node{
    data_t data;
    struct sll_node *next;
};

sll_list_t* create_sll(void);

status_t sll_insert_beg(sll_list_t *p_list, data_t new_data);
status_t sll_insert_end(sll_list_t *p_list, data_t new_data);
status_t sll_insert_after(sll_list_t *p_list, data_t r_data, data_t new_data);
status_t sll_insert_before(sll_list_t *p_list, data_t r_data, data_t new_data);

status_t sll_get_beg(sll_list_t *p_list, data_t *p_data);
status_t sll_get_end(sll_list_t *p_list, data_t *p_data);
status_t sll_pop_beg(sll_list_t *p_list, data_t *p_data);
status_t sll_pop_end(sll_list_t *p_list, data_t *p_data);

status_t sll_remove_beg(sll_list_t *p_list);
status_t sll_remove_end(sll_list_t *p_list);
status_t sll_remove_data(sll_list_t *p_list, data_t r_data);

len_t sll_get_length(sll_list_t *p_list);
bool sll_contains(sll_list_t *p_list, data_t search_data);
bool sll_is_list_empty(sll_list_t *p_list);
sll_node_t* sll_get_location(sll_list_t *p_list, data_t search_data);
int sll_get_repeat_count(sll_list_t *p_list, data_t search_data);
void sll_show_list(sll_list_t *p_list, const char *msg);

sll_list_t* sll_concat_lists(sll_list_t *p_list1, sll_list_t *p_list2);
sll_list_t* sll_merge_lists(sll_list_t *p_list1, sll_list_t *p_list2);
sll_list_t* sll_get_reversed_list(sll_list_t *p_list);
status_t sll_list_to_array(sll_list_t *p_list, data_t **pp_array, size_t *p_size);
sll_list_t* sll_array_to_list(data_t *p_array, len_t len);

status_t sll_append_list(sll_list_t *p_list1, sll_list_t *p_list2);
status_t sll_reverse_list(sll_list_t *p_list);

status_t sll_destroy_list(sll_list_t **p_list);

void sll_generic_insert(sll_node_t *p_beg, sll_node_t *p_mid, sll_node_t *p_end);
void sll_generic_delete(sll_node_t *p_node_prev, sll_node_t *p_delete_node);
sll_node_t* sll_get_list_node(data_t new_data);
sll_node_t* sll_locate_node(sll_list_t *p_list, data_t search_data);
sll_node_t* sll_get_node(sll_list_t *p_list, data_t e_data);
sll_node_t* sll_get_prev_node(sll_list_t *p_list, data_t e_data);
sll_node_t* sll_get_prev_to_last_node(sll_list_t *p_list);
sll_node_t* sll_get_last_node(sll_list_t *p_list);

void* xmalloc(size_t size_in_bytes);

#endif