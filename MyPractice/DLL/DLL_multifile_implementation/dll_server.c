#include "dll.h"

status_t dll_insert_beg(dll_list_t *p_list, data_t new_data){
    dll_generic_insert(p_list, dll_get_list_node(new_data), p_list->next);
    return (SUCCESS);
}

status_t dll_insert_end(dll_list_t *p_list, data_t new_data){
    dll_node_t *p_last_node = dll_get_last_node(p_list);
    dll_generic_insert(p_last_node, dll_get_list_node(new_data), p_last_node->next);
    return (SUCCESS);
}

status_t dll_insert_after(dll_list_t *p_list, data_t e_data, data_t new_data){
    dll_node_t *p_node = NULL;
    p_node = dll_get_node_location(p_list, e_data);
    assert(p_node != NULL);
    dll_generic_insert(p_node, dll_get_list_node(new_data), p_node->next);
    return (SUCCESS);
}

status_t dll_insert_before(dll_list_t *p_list, data_t e_data, data_t new_data){
    dll_node_t *p_node = NULL;
    p_node = dll_get_node_location(p_list, e_data);
    assert(p_node != NULL);
    dll_generic_insert(p_node->prev, dll_get_list_node(new_data), p_node);
    return (SUCCESS);
}

status_t dll_get_beg(dll_list_t *p_list, data_t *p_data){
    if(dll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    *p_data = p_list->next->data;
    return (SUCCESS);
}

status_t dll_get_end(dll_list_t *p_list, data_t *p_data){
    if(dll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    dll_node_t *p_last_node = dll_get_last_node(p_list);
    *p_data = p_last_node->data;
    return (SUCCESS);
}

status_t dll_pop_beg(dll_list_t *p_list, data_t *p_data){
    if(dll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    *p_data = p_list->next->data;
    dll_generic_delete(p_list->next);
    return (SUCCESS);
}

status_t dll_pop_end(dll_list_t *p_list, data_t *p_data){
    if(dll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    dll_node_t *p_last_node = dll_get_last_node(p_list);
    dll_generic_delete(p_last_node);
    return (SUCCESS);
}

status_t dll_remove_beg(dll_list_t *p_list){
    dll_generic_delete(p_list->next);
    return (SUCCESS);
}

status_t dll_remove_end(dll_list_t *p_list){
    if(dll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    dll_node_t *p_last_node = dll_get_last_node(p_list);
    dll_generic_delete(p_last_node);
    return (SUCCESS);
}

status_t dll_remove_data(dll_list_t *p_list, data_t r_data){
    if(dll_is_list_empty(p_list)){
        return (LIST_EMPTY);
    }
    dll_node_t *p_node = dll_get_node_location(p_list, r_data);
    dll_generic_delete(p_node);
    return (SUCCESS);
}

bool dll_is_list_empty(dll_list_t *p_list){
    if(p_list->next == NULL){
        return (TRUE);
    }
    return (FALSE);
}

bool dll_contains(dll_list_t *p_list, data_t e_data){
    dll_node_t *p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == e_data){
            return (TRUE);
        }
    }
    return (FALSE);
}

len_t dll_get_length(dll_list_t *p_list){
    len_t list_length = 0;
    dll_node_t *p_run = p_list->next;
    while(p_run != NULL){
        list_length ++;
        p_run = p_run->next;
    }
    return list_length;
}

int dll_get_repeat_count(dll_list_t *p_list, data_t e_data){
    int repeat_count = 0;
    dll_node_t *p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == e_data){
            repeat_count++;
        }
        p_run = p_run->next;
    }
    return repeat_count;
}

dll_node_t* locate_node(dll_list_t *p_list, data_t e_data){
    return(dll_get_node_location(p_list, e_data));
}

dll_list_t* dll_merge_lists(dll_list_t *p_list1, dll_list_t *p_list2){
    dll_list_t *p_new_list = create_dll();
    dll_node_t *p_run1 = p_list1->next,
                *p_run2 = p_list2->next;
    status_t s;
    while(TRUE){
        if(p_run1 == NULL){
            while(p_run2 != NULL){
                s = dll_insert_end(p_new_list, p_run2->data);
                assert(s == SUCCESS);
                p_run2 = p_run2->next;
            }
            break;
        }
        if(p_run2 == NULL){
            while(p_run1 != NULL){
                s = dll_insert_end(p_new_list, p_run1->data);
                assert(s == SUCCESS);
                p_run1 = p_run1->next;
            }
            break;
        }
        if(p_run1->data <= p_run2->data){
            s = dll_insert_end(p_new_list, p_run1->data);
            assert(s == SUCCESS);
            p_run1 = p_run1->next;
        }
        else {
            s = dll_insert_end(p_new_list, p_run2->data);
            assert(s == SUCCESS);
            p_run2 = p_run2->next;
        }
    }
    return p_new_list;
}

dll_list_t* dll_concat_lists(dll_list_t *p_list1, dll_list_t *p_list2){
    dll_list_t *p_new_list = create_dll();
    dll_node_t *p_run = p_list1->next;
    status_t s;
    while(p_run != NULL){
        s = dll_insert_end(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    p_run = p_list2->next;
    while(p_run != NULL){
        s = dll_insert_end(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    return (p_new_list);
}

dll_list_t* dll_reversed_list(dll_list_t *p_list){
    dll_list_t *p_new_list = create_dll();
    dll_node_t *p_run = p_list->next;
    status_t s;
    while(p_run != NULL){
        s = dll_insert_beg(p_new_list, p_run->data);
        assert(s == SUCCESS);
        p_run = p_run->next;
    }
    return (p_new_list);
}

dll_list_t* dll_array_to_list(data_t *p_array, len_t len){
    dll_list_t *p_new_list = create_dll();
    int i;
    status_t s;
    for(i=0; i<len; i++){
        s = dll_insert_end(p_new_list, p_array[i]);
        assert(s == SUCCESS);
    }
    return (p_new_list);
}

status_t dll_list_to_array(dll_list_t *p_list, data_t **pp_array, len_t *p_len){
    dll_node_t *p_run = p_list->next;
    data_t *p_array = NULL;
    len_t list_length = dll_get_length(p_list);
    p_array = (data_t *)xmalloc(list_length * sizeof(data_t));
    int i = 0;
    while(p_run != NULL){
        p_array[i] = p_run->data;
        p_run = p_run->next;
        i ++;
    }
    *pp_array = p_array;
    *p_len = list_length;
    p_array = NULL;
    return (SUCCESS);
}

status_t dll_reverse_list(dll_list_t *p_list){
    dll_node_t *p_node = NULL,
                *p_next_node = NULL,
                *p_run = p_list->next;
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
status_t dll_append_lists(dll_list_t *p_list1, dll_list_t *p_list2){
    dll_node_t *p_list1_last_node = NULL;
    p_list1_last_node = dll_get_last_node(p_list1);
    p_list1_last_node->next = p_list2->next;
    p_list2->next->prev = p_list1_last_node;
    free(p_list2);
    p_list2 = NULL;
    return (SUCCESS);
}

void dll_show_list(dll_list_t *p_list, const char *msg){
    if(msg){
        puts(msg);
    }
    dll_node_t *p_run = p_list->next;
    printf("[beg]<->");
    while(p_run != NULL){
        printf("[%d]<->", p_run->data);
        p_run = p_run->next;
    }
    printf("[end]\n\n");
}

dll_node_t* dll_get_last_node(dll_node_t *p_list){
    if(dll_is_list_empty(p_list)){
        return (p_list);
    }
    dll_node_t *p_run = p_list->next;
    while(p_run->next != NULL){
        p_run = p_run->next;
    }
    return p_run;
}

dll_node_t* dll_get_node_location(dll_list_t *p_list, data_t e_data){
    dll_node_t* p_run = NULL;
    p_run = p_list->next;
    while(p_run != NULL){
        if(p_run->data == e_data){
            return (p_run);
        }
        p_run = p_run->next;
    }
    return NULL;
}

void dll_generic_insert(dll_node_t *p_node_beg, dll_node_t *p_node_mid, dll_node_t *p_node_end){
    p_node_mid->prev = p_node_beg;
    p_node_mid->next = p_node_end;
    p_node_beg->next = p_node_mid;
    if(p_node_end != NULL){
        p_node_end->prev = p_node_mid;
    }
}

void dll_generic_delete(dll_node_t *p_delete_node){
    p_delete_node->prev->next = p_delete_node->next;
    if(p_delete_node->next != NULL){
        p_delete_node->next->prev = p_delete_node->prev; 
    }
    free(p_delete_node);
    p_delete_node = NULL;
}

dll_node_t* dll_get_list_node(data_t new_data){
    dll_node_t *p_node = NULL;
    p_node = (dll_node_t *)xmalloc(sizeof(dll_node_t));
    p_node->data = new_data;
    p_node->next = NULL;
    p_node->prev = NULL;
    return (p_node);
}

dll_list_t* create_dll(){
    dll_list_t *p_list = NULL;
    p_list = dll_get_list_node(0);
    assert(p_list != NULL);
    return p_list;
}

status_t destroy_dll(dll_list_t **pp_list){
    dll_list_t *p_list = NULL;
    dll_node_t *p_run = NULL, *p_run_next = NULL;
    p_list = *pp_list;
    p_run = p_list->next;
    p_run_next = p_list;
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
    void* p = NULL;
    p = malloc(size_in_bytes);
    assert(p != NULL);
    return p;
}