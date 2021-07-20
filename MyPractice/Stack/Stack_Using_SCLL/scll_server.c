#include "scll.h"

status_t scll_insert_beg(scll_list_t *p_list, data_t new_data){
    scll_generic_insert(p_list, scll_get_list_node(new_data), p_list->next);
    return (SUCCESS);
}

status_t scll_insert_end(scll_list_t *p_list, data_t new_data){
    scll_node_t *p_last_node = NULL;
    p_last_node = scll_get_last_node(p_list);
    scll_generic_insert(p_last_node, scll_get_list_node(new_data), p_last_node->next);
    return (SUCCESS);
}

status_t scll_insert_after(scll_list_t *p_list, data_t e_data, data_t new_data){
    scll_node_t *p_node = NULL;
    p_node = scll_get_location(p_list, e_data);
    scll_generic_insert(p_node, scll_get_list_node(new_data), p_node->next);
    return (SUCCESS);
}

status_t scll_insert_before(scll_list_t *p_list, data_t e_data, data_t new_data){
    scll_node_t *p_node = NULL;
    p_node = scll_get_prev_location(p_list, e_data);
    scll_generic_insert(p_node, scll_get_list_node(new_data), p_node->next);
    return (SUCCESS);
}

status_t scll_get_beg(scll_list_t *p_list, data_t *p_data){
    if(scll_is_list_empty(p_list)){
        return  (LIST_EMPTY);
    }
    *p_data = p_list->next->data;
    return (SUCCESS);
}

status_t scll_get_end(scll_list_t *p_list, data_t *p_data){
    if(scll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    scll_node_t *p_node = scll_get_last_node(p_list);
    *p_data = p_node->data;
    return (SUCCESS);
}

status_t scll_pop_beg(scll_list_t *p_list, data_t *p_data){
    if(scll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    *p_data = p_list->next->data;
    scll_generic_delete(p_list, p_list->next);
    return (SUCCESS);
}

status_t scll_pop_end(scll_list_t *p_list, data_t *p_data){
    if(scll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    scll_node_t *p_second_last_node = NULL;
    p_second_last_node = scll_get_prev_to_last_node(p_list);
    *p_data = p_second_last_node->next->data;
    scll_generic_delete(p_second_last_node, p_second_last_node->next);
    return (SUCCESS);
}

status_t scll_remove_beg(scll_list_t *p_list){
    if(scll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    scll_generic_delete(p_list, p_list->next);
    return (SUCCESS);
}

status_t scll_remove_end(scll_list_t *p_list){
    if(scll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    scll_node_t *p_node = scll_get_prev_to_last_node(p_list);
    scll_generic_delete(p_node, p_node->next);
    return (SUCCESS);
}

status_t scll_remove_data(scll_list_t *p_list, data_t r_data){
    if(scll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    scll_node_t *p_prev_node = scll_get_prev_location(p_list, r_data);
    scll_generic_delete(p_prev_node, p_prev_node->next);
    return (SUCCESS);
}

bool scll_is_list_empty(scll_list_t *p_list){
    if(p_list->next == p_list){
        return TRUE;
    }
    return FALSE;
}

bool scll_contains(scll_list_t *p_list, data_t e_data){
    scll_node_t *p_run = p_list->next;
    while(p_run != p_list){
        if(p_run->data == e_data){
            return (TRUE);
        }
        p_run = p_run->next;
    }
    return (FALSE);
}

len_t scll_get_length(scll_list_t *p_list){
    len_t list_length = 0;
    scll_node_t *p_run = NULL;
    p_run = p_list->next;
    while(p_run != p_list){
        p_run = p_run->next;
        list_length ++;
    }
    return (list_length);
}

scll_node_t* scll_locate_node(scll_list_t *p_list, data_t e_data){
    return (scll_get_location(p_list, e_data));
}

int scll_get_repeat_count(scll_list_t *p_list, data_t e_data){
    int repeat_count = 0;
    scll_node_t *p_run = p_list->next;
    while(p_run != p_list){
        if(p_run->data == e_data){
            repeat_count ++;
        }
        p_run = p_run->next;
    }
    return (repeat_count);
}

scll_list_t* scll_merge_lists(scll_list_t *p_list1, scll_list_t *p_list2){
    scll_list_t *p_new_list = NULL;
    p_new_list = create_scll();
    scll_node_t *p_run1 = p_list1->next, *p_run2 = p_list2->next;
    status_t s;
    while(TRUE){
        if(p_run1 == p_list1){
            while(p_run2 != p_list2){
                s = scll_insert_end(p_new_list, p_run2->data);
                assert(s == SUCCESS);
                p_run2 = p_run2->next;
            }
            break;
        }
        if(p_run2 == p_list2){
            while(p_run1 != p_list1){
                s = scll_insert_end(p_new_list, p_run1->data);
                assert(s == SUCCESS);
                p_run1 = p_run1->next;
            }
            break;
        }
        
        if(p_run1->data <= p_run2->data){
            s = scll_insert_end(p_new_list, p_run1->data);
            assert(s == SUCCESS);
            p_run1 = p_run1->next;
        }
        else {
            s = scll_insert_end(p_new_list, p_run2->data);
            assert(s == SUCCESS);
            p_run2 = p_run2->next;
        }
    }
    return (p_new_list);
}

scll_list_t* scll_concat_lists(scll_list_t *p_list1, scll_list_t *p_list2){
    scll_list_t *p_new_list = NULL;
    p_new_list = create_scll();
    status_t s;
    scll_node_t *p_run = NULL;
    p_run = p_list1->next;
    while(p_run != p_list1){
        s = scll_insert_end(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    p_run = p_list2->next;
    while(p_run != p_list2){
        s = scll_insert_end(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    return p_new_list;
}
scll_list_t* scll_reversed_list(scll_list_t *p_list){
    scll_list_t *p_new_list = NULL;
    p_new_list = create_scll();
    scll_node_t *p_run = p_list->next;
    status_t s;
    while(p_run != p_list){
        s = scll_insert_beg(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    return (p_new_list);
}

scll_list_t* scll_array_to_list(data_t *p_array, len_t len){
    scll_list_t *p_new_list = create_scll();
    status_t s;
    int i;
    for(i = 0; i<len; i++){
        s = scll_insert_end(p_new_list, p_array[i]);
        assert(s == SUCCESS);
    }
    return p_new_list;
}

status_t scll_list_to_array(scll_list_t *p_list, data_t **pp_array, len_t *len){
    data_t *p_array;
    len_t list_length = scll_get_length(p_list);
    p_array = (data_t *)xmalloc(list_length * sizeof(data_t));
    scll_node_t *p_run = p_list->next;
    int i = 0;
    while(p_list != p_run){
        p_array[i] = p_run->data;
        p_run = p_run->next;
    }
    *pp_array = p_array;
    p_array = NULL;
    *len = list_length;
    return (SUCCESS);
}

status_t scll_reverse_list(scll_list_t *p_list){
    if(scll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    scll_node_t *p_last_node = NULL, 
                *p_new_last_node = NULL,
                *p_run = NULL,
                *p_node = NULL;
    p_last_node = scll_get_last_node(p_list);
    p_run = p_list->next;
    p_new_last_node = p_list;
    while(p_run != p_last_node){
        p_node = p_run;
        p_list->next = p_list->next->next;
        p_run = p_list->next;
        scll_generic_insert(p_last_node, p_node, p_new_last_node);
        p_new_last_node = p_node;
    }
    return (SUCCESS);
}

status_t scll_append_list(scll_list_t *p_list1, scll_list_t *p_list2){
    scll_node_t *p_list1_last_node = NULL, *p_list2_last_node = NULL;
    p_list1_last_node = scll_get_last_node(p_list1);
    p_list2_last_node = scll_get_last_node(p_list2);
    p_list1_last_node->next = p_list2->next;
    p_list2_last_node->next = p_list1;
    free(p_list2);
    p_list2 = NULL;
    return (SUCCESS);
}

scll_node_t* scll_get_location(scll_list_t *p_list, data_t e_data){
    scll_node_t *p_run = NULL;
    p_run = p_list->next;
    while(p_run != p_list){
        if(p_run->data == e_data){
            return (p_run);
        }
        p_run = p_run->next;
    }
    return NULL;
}

scll_node_t* scll_get_prev_location(scll_list_t *p_list, data_t e_data){
    scll_node_t *p_run = NULL, *p_run_prev = NULL;
    p_run = p_list->next;
    p_run_prev = p_list;
    while(p_run != p_list){
        if(p_run->data == e_data){
            return p_run_prev;
        }
        p_run_prev = p_run;
        p_run = p_run->next;
    }
    return NULL;
}

scll_node_t* scll_get_last_node(scll_list_t *p_list){
    scll_node_t *p_run = NULL;
    p_run = p_list->next;
    while(p_run->next != p_list){
        p_run = p_run->next;
    }
    return p_run;
}

scll_node_t* scll_get_prev_to_last_node(scll_list_t *p_list){
    scll_node_t *p_run = NULL, *p_run_prev = NULL;
    p_run = p_list->next;
    p_run_prev = p_list;
    while(p_run->next != p_list){
        p_run_prev = p_run;
        p_run = p_run->next;
    }
    return (p_run_prev);
}

void scll_show_list(scll_list_t *p_list, const char* msg){
    if(msg){
        puts(msg);
    }
    scll_node_t *p_run = p_list->next;
    printf("[beg]->");
    while(p_list != p_run){
        printf("[%d]->", p_run->data);
        p_run = p_run->next;
    }
    printf("[end]\n");
}


void scll_generic_insert(scll_node_t *p_beg_node, scll_node_t *p_mid_node, scll_node_t *p_end_node){
    p_beg_node->next = p_mid_node;
    p_mid_node->next = p_end_node;
}

void scll_generic_delete(scll_node_t *p_prev_node, scll_node_t *p_delete_node){
    p_prev_node->next = p_delete_node->next;
    free(p_delete_node);
    p_delete_node = NULL;
}

scll_node_t* scll_get_list_node(data_t new_data){
    scll_node_t *p_node = NULL;
    p_node = (scll_node_t*)xmalloc(sizeof(scll_node_t));
    assert(p_node != NULL);
    p_node->data = new_data;
    p_node->next = NULL;
    return (p_node);
}

scll_list_t* create_scll(){
    scll_list_t *p_new_list = NULL;
    p_new_list = scll_get_list_node(0);
    assert(p_new_list != NULL);
    p_new_list->next = p_new_list;
    return p_new_list;
}

status_t destroy_scll(scll_list_t **pp_list){
    scll_list_t *p_list = *pp_list;
    scll_node_t *p_run = p_list->next;
    scll_node_t *p_run_next = NULL;
    while(p_run != NULL){
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
    return p;
}