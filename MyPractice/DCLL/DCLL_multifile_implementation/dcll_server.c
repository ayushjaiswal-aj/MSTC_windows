#include "dcll.h"

status_t dcll_insert_beg(dcll_list_t *p_list, data_t new_data){
    dcll_generic_insert(p_list, dcll_get_list_node(new_data), p_list->next);
    return (SUCCESS);
}

status_t dcll_insert_end(dcll_list_t *p_list, data_t new_data){
    dcll_generic_insert(p_list->prev, dcll_get_list_node(new_data), p_list);
    return (SUCCESS);
}

status_t dcll_insert_after(dcll_list_t *p_list, data_t e_data, data_t new_data){
    dcll_node_t *p_node = NULL;
    p_node = dcll_get_node_location(p_list, e_data);
    dcll_generic_insert(p_node, dcll_get_list_node(new_data), p_node->next);
    return (SUCCESS);
}

status_t dcll_insert_before(dcll_list_t *p_list, data_t e_data, data_t new_data){
    dcll_node_t *p_node = NULL;
    p_node = dcll_get_node_location(p_list, e_data);
    dcll_generic_insert(p_node->prev, dcll_get_list_node(new_data), p_node);
    return (SUCCESS);
}

status_t dcll_get_beg(dcll_list_t *p_list, data_t *p_data){
    *p_data = p_list->next->data;
    return (SUCCESS);
}

status_t dcll_get_end(dcll_list_t *p_list, data_t *p_data){
    *p_data = p_list->prev->data;
    return (SUCCESS);
}

status_t dcll_pop_beg(dcll_list_t *p_list, data_t *p_data){
    *p_data = p_list->next->data;
    dcll_generic_delete(p_list->next);
    return (SUCCESS);
}

status_t dcll_pop_end(dcll_list_t *p_list, data_t *p_data){
    *p_data = p_list->prev->data;
    dcll_generic_delete(p_list->prev);
    return (SUCCESS);
}

status_t dcll_remove_beg(dcll_list_t *p_list){
    dcll_generic_delete(p_list->next);
    return (SUCCESS);
}

status_t dcll_remove_end(dcll_list_t *p_list){
    dcll_generic_delete(p_list->prev);
    return (SUCCESS);
}

status_t dcll_remove_data(dcll_list_t *p_list, data_t r_data){
    dcll_node_t *p_node = dcll_get_node_location(p_list, r_data);
    dcll_generic_delete(p_node);
    return (SUCCESS);
}

len_t dcll_get_length(dcll_list_t *p_list){
    len_t list_len = 0;
    dcll_node_t *p_run = p_list->next;
    while(p_run != p_list){
        list_len ++;
        p_run = p_run->next;
    }
    return (list_len);
}

int dcll_get_repeat_count(dcll_list_t *p_list, data_t e_data){
    int repeat_count = 0;
    dcll_node_t *p_run = p_list->next;
    while(p_run  != p_list){
        if(p_run->data == e_data){
            repeat_count++;
        }
        p_run = p_run->next;
    }
    return (repeat_count);
}

bool dcll_contains(dcll_list_t *p_list, data_t e_data){
    dcll_node_t *p_run = p_list->next;
    while(p_run != p_list){
        if(p_run->data != e_data){
            return(TRUE);
        }
        p_run = p_run->next;
    }
    return (FALSE);
}

bool dcll_is_list_empty(dcll_list_t *p_list){
    if(p_list->next == p_list && p_list->prev == p_list){
        return (TRUE);
    }
    return (SUCCESS);
}

dcll_node_t* dcll_locate_node(dcll_list_t *p_list, data_t e_data){
    dcll_node_t *p_run = p_list->next;
    while(p_run != p_list){
        if(p_run->data == e_data){
            return (p_run);
        }
        p_run = p_run->next;
    }
    return (NULL);
}

dcll_list_t* dcll_concat_lists(dcll_list_t *p_list1, dcll_list_t *p_list2){
    dcll_list_t *p_new_list = create_dcll();
    dcll_node_t *p_run = p_list1->next;
    status_t s;
    while(p_run != p_list1){
        s = dcll_insert_end(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    p_run = p_list2->next;
    while(p_run != p_list2){
        s = dcll_insert_end(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    return (p_new_list);
}

dcll_list_t* dcll_merge_lists(dcll_list_t *p_list1, dcll_list_t *p_list2){
    dcll_list_t *p_new_list = create_dcll();
    dcll_node_t *p_run1 = NULL, *p_run2 = NULL;
    status_t s;
    p_run1 = p_list1->next;
    p_run2 = p_list2->next;
    while(TRUE){
        if(p_run1 == p_list1){
            while(p_run2 != p_list2){
                s = dcll_insert_end(p_new_list, p_run2->data);
                assert(s == SUCCESS);
                p_run2 = p_run2->next;
            }
            break;
        }
        if(p_run2 == p_list2){
            while(p_run1 != p_list1){
                s = dcll_insert_end(p_new_list, p_run1->data);
                assert(s == SUCCESS);
                p_run1 = p_run1->next;
            }
            break;
        }
        if(p_run1->data <= p_run2->data){
            s = dcll_insert_end(p_new_list, p_run1->data);
            assert(s == SUCCESS);
            p_run1 = p_run1->next;
        }
        else {
            s = dcll_insert_end(p_new_list, p_run2->data);
            assert(s == SUCCESS);
            p_run2 = p_run2->next;
        }
    }
    return (p_new_list);
}

dcll_list_t* dcll_reversed_list(dcll_list_t *p_list){
    dcll_list_t *p_new_list = create_dcll();
    dcll_node_t *p_run = p_list->next;
    status_t s;
    while(p_run != p_list){
        s = dcll_insert_beg(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    return (p_new_list);
}

dcll_list_t* dcll_array_to_list(data_t *p_array, len_t len){
    dcll_list_t *p_new_list = create_dcll();
    int i;
    status_t s;
    for(i = 0; i<len; i++){
        s = dcll_insert_end(p_new_list, p_array[i]);
        assert(s == SUCCESS);
    }
    return (p_new_list);
}

status_t dcll_list_to_array(dcll_list_t *p_list, data_t **pp_array, len_t *p_len){
    data_t *p_array = NULL;
    len_t list_length = dcll_get_length(p_list);
    p_array = (data_t*)xmalloc(sizeof(data_t) * list_length);
    dcll_node_t *p_run = p_list->next;
    int i = 0;
    while(p_run != p_list){
        p_array[i] = p_run->data;
        p_run = p_run->next;
        i++;
    }
    *pp_array = p_array;
    *p_len = list_length;
    p_array = NULL;
    return (SUCCESS);
}

status_t dcll_append_lists(dcll_list_t *p_list1, dcll_list_t *p_list2){
    p_list1->prev->next = p_list2->next;
    p_list2->next->prev = p_list1->prev;
    p_list2->prev->next = p_list1;
    p_list1->prev = p_list2->prev;
    free(p_list2);
    p_list2 = NULL;
    return (SUCCESS);
}

status_t dcll_reverse_list(dcll_list_t *p_list){
    dcll_node_t *p_run = NULL,
                *p_new_last = NULL,
                *p_last = NULL,
                *p_node = NULL;
    p_run = p_list->next;
    p_last = p_new_last = p_list->prev;
    while(p_run != p_last){
        p_node = p_run;
        p_list->next = p_list->next->next;
        dcll_generic_insert(p_new_last, p_node, p_list);
        p_new_last = p_node;
        p_run = p_list->next;
    }
    return (SUCCESS);
}

dcll_node_t* dcll_get_node_location(dcll_list_t *p_list, data_t e_data){
    dcll_node_t *p_run = p_list->next;
    while(p_list != p_run){
        if(p_run->data == e_data){
            return (p_run);
        }
        p_run = p_run->next;
    }
    return (NULL);
}

void dcll_show_list(dcll_list_t *p_list, const char *msg){
    if(msg){
        puts(msg);
    }
    dcll_node_t *p_run = p_list->next;
    printf("[end]<->[beg]<->");
    while(p_run != p_list){
        printf("[%d]<->", p_run->data);
        p_run = p_run->next;
    }
    printf("[end]<->[beg]\n");
}

void dcll_generic_insert(dcll_node_t* p_node_beg, dcll_node_t* p_node_mid, dcll_node_t* p_node_end){
    p_node_beg->next = p_node_mid;
    p_node_end->prev = p_node_mid;
    p_node_mid->next = p_node_end;
    p_node_mid->prev = p_node_beg;
}

void dcll_generic_delete(dcll_node_t* p_delete_node){
    p_delete_node->prev->next = p_delete_node->next;
    p_delete_node->next->prev = p_delete_node->prev;
    free(p_delete_node);
    p_delete_node = NULL;
}

dcll_node_t* dcll_get_list_node(data_t new_data){
    dcll_node_t *p_new_node = NULL;
    p_new_node = (dcll_node_t *)xmalloc(sizeof(dcll_node_t));
    p_new_node->data = new_data;
    p_new_node->next = NULL;
    p_new_node->prev = NULL;
    return (p_new_node);
}

dcll_list_t* create_dcll(){
    dcll_list_t *p_new_list = NULL;
    p_new_list = dcll_get_list_node(0);
    p_new_list->next = p_new_list;
    p_new_list->prev = p_new_list;
    return (p_new_list);
}

status_t destroy_dcll(dcll_list_t **pp_list){
    dcll_list_t *p_list = *pp_list;
    dcll_node_t *p_run = NULL, *p_run_next = NULL;
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
    return p;
}
