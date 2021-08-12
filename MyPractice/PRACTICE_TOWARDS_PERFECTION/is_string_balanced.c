#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define LIST_EMPTY 2
#define STACK_EMPTY LIST_EMPTY

typedef int status_t;
typedef int bool;
typedef char data_t;
typedef struct stack stack_t;
typedef struct list_node node_t;
typedef node_t list_t;

struct list_node{
    data_t data;
    struct list_node *next;
    struct list_node *prev;
};

struct stack{
    list_t *p_list_head;
    size_t size;
};

bool is_string_balance(const char *str);

/* stack interface routines */
stack_t* create_stack();
status_t destroy_stack(stack_t **pp_stack);
status_t push(stack_t *p_stack, data_t new_data);
status_t pop(stack_t *p_stack, data_t *poped_data); 

/* list interface routines */
list_t* create_list();
status_t destroy_list(list_t **pp_list);
status_t insert_beg(list_t *p_list, data_t new_data);
status_t remove_beg(list_t *p_list, data_t *p_removed_data);

/* list auxillary routines */
node_t* get_list_node(data_t new_data);
void generic_insert(node_t *p_node_beg, node_t *p_node_mid, node_t *p_node_end);
void generic_delete(node_t *p_delete_node);

/* memory auxillary routine */
void* xcalloc(size_t nr_elements, size_t size_per_element);

int main(void){
    char *str = "()(({{)}})";
    if(is_string_balance(str) == TRUE){
        printf("given string str: %s \nis balanced\n", str);
    }
    else {
        printf("given string str: %s \nis not balanced\n", str);
    }
    
    exit (EXIT_SUCCESS);
}

bool is_string_balance(const char *str){
    int i;
    int str_len = sizeof(str)/sizeof(str[0]);
    status_t s;
    data_t data;
    stack_t *p_stack = NULL;
    p_stack = create_stack();
    
    for(i = 0; str[i] != '\0'; i++){
        if(str[i] == '(' || str[i] == '{' || str[i] == '['){
            assert(push (p_stack, str[i]) == SUCCESS);
        }
        else if(str[i] == ')'){
            assert(pop(p_stack, &data) == SUCCESS);
            if(data != '('){
                return FALSE;
            }
        }
        else if(str[i] == '}'){
            assert(pop(p_stack, &data) == SUCCESS);
            if(data != '{'){
                return FALSE;
            }
        }
        else if(str[i] == ']'){
            assert(pop(p_stack, &data) == SUCCESS);
            if(data != '['){
                return FALSE;
            }
        }
    }
    return TRUE;
}

/* stack interface routines */
stack_t* create_stack(){
    stack_t *p_new_stack = NULL;
    p_new_stack = (stack_t *)xcalloc(1, sizeof(stack_t));
    p_new_stack->p_list_head = create_list();
    p_new_stack->size = 0;
    return p_new_stack;
}

status_t destroy_stack(stack_t **pp_stack){
    stack_t *p_stack = NULL;
    p_stack = *pp_stack;
    destroy_list(&(p_stack->p_list_head));
    free(p_stack);
    *pp_stack = NULL;
    return (SUCCESS);
}

status_t push(stack_t *p_stack, data_t new_data){
    if((insert_beg(p_stack->p_list_head, new_data)) == SUCCESS){
        p_stack->size ++;
        return SUCCESS;
    }
    return FAILURE;
}

status_t pop(stack_t *p_stack, data_t *poped_data){
    if((remove_beg(p_stack->p_list_head, poped_data)) == SUCCESS){
        p_stack->size --;
        return SUCCESS;
    }
    return FAILURE;
}

/* list interface routines */
list_t* create_list(){
    list_t *p_new_list = NULL;
    p_new_list = get_list_node(0);
    p_new_list->next = p_new_list;
    p_new_list->prev = p_new_list;
    return (p_new_list);
}

status_t destroy_list(list_t **pp_list){
    list_t *p_list = NULL;
    node_t *p_run = NULL;
    node_t *p_run_next = NULL;

    p_list = *pp_list;
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

status_t insert_beg(list_t *p_list, data_t new_data){
    generic_insert(p_list, get_list_node(new_data), p_list->next);
    return (SUCCESS);
}

status_t remove_beg(list_t *p_list, data_t *p_removed_data){
    if(p_list->next == p_list && p_list->prev == p_list){
        return LIST_EMPTY;
    }
    *p_removed_data = p_list->next->data;
    generic_delete(p_list->next);
    return (SUCCESS);
}

/* list auxillary routines */
node_t* get_list_node(data_t new_data){
    node_t *p_new_node = NULL;
    p_new_node = (node_t *)xcalloc(1, sizeof(node_t));
    p_new_node->data = new_data;
    p_new_node->next = NULL;
    p_new_node->prev = NULL;
    return (p_new_node);
}

void generic_insert(node_t *p_node_beg, node_t *p_node_mid, node_t *p_node_end){
    p_node_beg->next = p_node_mid;
    p_node_mid->next = p_node_end;
    p_node_end->prev = p_node_mid;
    p_node_mid->prev = p_node_beg;
}

void generic_delete(node_t *p_delete_node){
    p_delete_node->prev->next = p_delete_node->next;
    p_delete_node->next->prev = p_delete_node->prev;
    free(p_delete_node);
    p_delete_node = NULL;
}

/* memory auxillary routine */
void* xcalloc(size_t nr_elements, size_t size_per_element){
    void *p = NULL;
    p = calloc(nr_elements, size_per_element);
    assert(p != NULL);
    return p;
}
