#include "sll.h"


sll_list_t* create_sll(void){
    sll_node_t *p_new_node = NULL;
    p_new_node = sll_get_list_node(0);
    p_new_node->next = NULL;
    return (p_new_node);
}

status_t sll_insert_beg(sll_list_t *p_list, data_t new_data){
    sll_generic_insert(p_list, sll_get_list_node(new_data), p_list->next);
    p_list->data ++;
    return (SUCCESS);
}

status_t sll_insert_end(sll_list_t *p_list, data_t new_data){
    sll_node_t *p_run = p_list;
    while(p_run->next != NULL){
        p_run = p_run->next;
    }
    sll_generic_insert(p_run, sll_get_list_node(new_data), p_run->next);
    return (SUCCESS);
}

status_t sll_insert_after(sll_list_t *p_list, data_t e_data, data_t new_data){
    sll_node_t *p_new_node = NULL;
    p_new_node = sll_locate_node(p_list, e_data);
    sll_generic_insert(p_new_node, sll_get_list_node(new_data), p_new_node->next);
    return (SUCCESS);
}

status_t sll_insert_before(sll_list_t *p_list, data_t e_data, data_t new_data){
    sll_node_t *p_run = NULL, *p_run_next = NULL;
    p_run = p_list->next;
    p_run_next = p_list->next->next;
    while(p_run_next != NULL){
        if(p_run_next->data == e_data){
            sll_generic_insert(p_run, sll_get_list_node(new_data), p_run->next);
            return (SUCCESS);
        }
        p_run = p_run->next;
        p_run_next = p_run_next->next;
    }
    return (FAILURE);
}

status_t sll_get_beg(sll_list_t *p_list, data_t *p_data){
    if(sll_is_list_empty(p_list)){
        return (FAILURE);
    }
    *p_data = p_list->next->data;
    return (SUCCESS);
}

status_t sll_get_end(sll_list_t *p_list, data_t *p_data){
    if(sll_is_list_empty(p_list)){
        return (FAILURE);
    }
    sll_node_t *last_node = sll_get_last_node(p_list);
    *p_data = last_node->data;
    return (SUCCESS);
}

status_t sll_pop_beg(sll_list_t *p_list, data_t *p_data){
    if(sll_is_list_empty(p_list)){
        return (FAILURE);
    }
    *p_data = p_list->next->data;
    sll_generic_delete(p_list, p_list->next);
    return (SUCCESS);
}

status_t sll_pop_end(sll_list_t *p_list, data_t *p_data){
    if(sll_is_list_empty(p_list)){
        return (FAILURE);
    }
    sll_node_t *last_node = sll_get_last_node(p_list);
    sll_node_t *prev_to_last_node = sll_get_prev_to_last_node(p_list);
    *p_data = last_node->data;
    sll_generic_delete(prev_to_last_node, last_node);
    return (SUCCESS);
}

status_t sll_remove_beg(sll_list_t *p_list){
    if(sll_is_list_empty(p_list)){
        return (FAILURE);
    }

    sll_generic_delete(p_list, p_list->next);
    return (SUCCESS);
}

status_t sll_remove_end(sll_list_t *p_list){
    if(sll_is_list_empty(p_list)){
        return (FAILURE);
    }
    sll_node_t *p_last_node = sll_get_last_node(p_list);
    sll_node_t *p_prev_to_last_node = sll_get_prev_to_last_node(p_list);
    sll_generic_delete(p_prev_to_last_node, p_last_node);
    return (SUCCESS);
}

status_t sll_remove_data(sll_list_t *p_list, data_t r_data){
    if(sll_is_list_empty(p_list)){
        return (FAILURE);
    }
    sll_node_t *prev_node = NULL;
    prev_node = sll_get_prev_node(p_list, r_data);
    sll_node_t *remove_node = NULL;
    remove_node = sll_get_node(p_list, r_data);
    sll_generic_delete(prev_node, remove_node);
    return (SUCCESS);
}

len_t sll_get_length(sll_list_t *p_list){
    sll_node_t *p_run = p_list->next;
    len_t len = 0;
    while(p_run != NULL){
        len++;
        p_run = p_run->next;
    }
    return (len);
}

bool sll_contains(sll_list_t *p_list, data_t search_data){
    sll_node_t *p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == search_data){
            return TRUE;
        }
        p_run = p_run->next;
    }
    return FALSE;
}

int sll_get_repeat_count(sll_list_t *p_list, data_t search_data){
    int repeat_count = 0;
    sll_node_t *p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == search_data){
            repeat_count++;
        }
        p_run = p_run->next;
    }
    return repeat_count;
}

sll_list_t* sll_concat_lists(sll_list_t *p_list1, sll_list_t *p_list2){
    sll_list_t *new_list = NULL;
    new_list = create_sll();
    assert(new_list != NULL);
    status_t s;
    sll_node_t *p_run = p_list1->next;

    printf("before inserting\n");
    while(p_run != NULL){
        s = sll_insert_end(new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    p_run = p_list2->next;

    while(p_run != NULL){
        s = sll_insert_end(new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }

    return new_list;
}

sll_list_t* sll_merge_lists(sll_list_t *p_list1, sll_list_t *p_list2){
    sll_list_t *p_merge_list = NULL;
    p_merge_list = create_sll();
    sll_node_t *p_run1 = p_list1->next, *p_run2 = p_list2->next;
    while(TRUE){
        if(p_run1->data <= p_run2->data){
            sll_insert_end(p_merge_list, p_run1->data);
            p_run1 = p_run1->next;
        }
        else {
            sll_insert_end(p_merge_list, p_run2->data);
            p_run2 = p_run2->next;
        }

        if(p_run1 == NULL){
            while(p_run2 != NULL){
                sll_insert_end(p_merge_list, p_run2->data);
                p_run2 = p_run2->next;
            }
            break;
        }
        if(p_run2 == NULL){
            while(p_run1 != NULL){
                sll_insert_end(p_merge_list, p_run1->data);
                p_run1 = p_run1->next;
            }
            break;
        }
    }
    return p_merge_list;
}

sll_list_t* sll_get_reversed_list(sll_list_t *p_list){
    sll_list_t *p_reversed_list = create_sll();
    sll_node_t *p_run = p_list->next;
    status_t s;
    while(p_run != NULL){
        s = sll_insert_beg(p_reversed_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    return (p_reversed_list);
}

status_t sll_list_to_array(sll_list_t *p_list, data_t **pp_array, size_t *p_size){
    data_t *p_array = NULL;
    len_t len;
    len = sll_get_length(p_list);
    sll_node_t *p_run = p_list->next;
    int i;
    p_array = (data_t*)xmalloc(len * sizeof(data_t));
    for(i = 0; i < len; i++){
        p_array[i] = p_run->data;
        p_run = p_run->next;
    }
    *pp_array = p_array;
    *p_size = len;
    return (SUCCESS);
}

sll_list_t* sll_array_to_list(data_t *p_array, len_t len){
    sll_list_t *p_list = create_sll();
    int i;
    status_t s;
    for(i = 0; i < len; i ++){
        s = sll_insert_end(p_list, *(p_array + i));
        assert(s == SUCCESS);
    }
    return (p_list);
}

status_t sll_append_list(sll_list_t *p_list1, sll_list_t *p_list2){
    sll_node_t *p_run = NULL;
    p_run = sll_get_last_node(p_list1);
    p_run->next = p_list2->next;
    return (SUCCESS);
}

void sll_show_list(sll_list_t *p_list, const char *msg){
    sll_node_t *p_run = p_list->next;
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

bool sll_is_list_empty(sll_list_t *p_list){
    if(p_list->next == NULL){
        return (TRUE);
    }
    return (FALSE);
}

sll_node_t* sll_get_node(sll_list_t *p_list, data_t e_data){
    return (sll_locate_node(p_list, e_data));
}

sll_node_t* sll_get_prev_node(sll_list_t *p_list, data_t e_data){
    sll_node_t *p_run = p_list->next;
    sll_node_t *p_run_next = p_list->next->next;
    while(p_run_next->data != e_data){
        p_run = p_run->next;
        p_run_next = p_run_next->next;
    }
    return (p_run);
}

sll_node_t* sll_get_prev_to_last_node(sll_list_t *p_list){
    sll_node_t *p_run = p_list->next;
    sll_node_t *p_run_next = p_list->next->next;
    while(p_run_next->next != NULL){
        p_run = p_run->next;
        p_run_next = p_run_next->next;
    }
    return (p_run);
}

sll_node_t* sll_get_last_node(sll_list_t *p_list){
    sll_node_t *p_run = p_list->next;
    while(p_run->next != NULL){
        p_run = p_run->next;
    }
    return (p_run);
}

void sll_generic_insert(sll_node_t *p_node_beg, sll_node_t *p_node_mid, sll_node_t *p_node_end){
    p_node_beg->next = p_node_mid;
    p_node_mid->next = p_node_end;
}

void sll_generic_delete(sll_node_t *p_node_prev, sll_node_t *p_delete_node){
    p_node_prev->next = p_delete_node->next;
    free(p_delete_node);
    p_delete_node = NULL;
}

sll_node_t* sll_locate_node(sll_list_t *p_list, data_t search_data){
    sll_node_t *p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == search_data){
            return (p_run);
        }
        p_run = p_run->next;
    }
    return (NULL);
}

sll_node_t* sll_get_list_node(data_t new_data){
    sll_node_t *p_new_node = NULL;
    p_new_node = (sll_node_t*)xmalloc(sizeof(sll_node_t));
    p_new_node->next = NULL;
    p_new_node->data = new_data;
    return (p_new_node);
}

void* xmalloc(size_t size_in_bytes){
    void *p = NULL;
    p = malloc(size_in_bytes);
    assert(p != NULL);
    return p;
}

status_t sll_destroy_list(sll_list_t **pp_list){
    sll_list_t *p_list = *pp_list;
    sll_node_t *p_run = p_list->next, *p_run_next;
    while(p_run != NULL){
        p_run_next = p_run->next;
        free(p_run);
        p_run = p_run_next;
    }
    free(p_list);
    *pp_list = NULL;
    return (SUCCESS);
}