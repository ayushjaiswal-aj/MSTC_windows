#include "dll.h"

typedef struct dll_stack dll_stack_t;

struct dll_stack{
    dll_list_t *p_list;
    size_t size;
};

dll_stack_t* create_dll_stack();
status_t destroy_dll_stack(dll_stack_t **pp_stack);

status_t push(dll_stack_t *p_stack, data_t new_data);
status_t pop(dll_stack_t *p_stack, data_t *p_poped_data);
status_t get_dll_stack_top(dll_stack_t *p_stack, data_t *p_top_data);
bool is_dll_stack_empty(dll_stack_t *p_stack);

size_t get_sizeof_dll_stack(dll_stack_t *p_stack);

void show_dll_stack(dll_stack_t *p_stack);

int main(void){
    dll_stack_t *p_stack = NULL;
    p_stack = create_dll_stack();
    int i;
    data_t data;
    status_t s;

    if(is_dll_stack_empty(p_stack)){
        printf("stack is empty...\n");
    }

    for(i=1; i<=10; i++){
        s = push(p_stack, i*10);
        assert(s == SUCCESS);
    }

    show_dll_stack(p_stack);
    
    s = get_dll_stack_top(p_stack, &data);
    if(s == SUCCESS){
        printf("top data: %d\n", data);
    }

    s = pop(p_stack, &data);
    if(s == SUCCESS){
        printf("poped data: %d\n", data);
    }
    printf("size of stack: %zd\n", get_sizeof_dll_stack(p_stack));

    show_dll_stack(p_stack);

    return (EXIT_SUCCESS);
}

dll_stack_t* create_dll_stack(){
    dll_stack_t *p_new_stack = NULL;
    p_new_stack = (dll_stack_t*)xmalloc(sizeof(dll_stack_t));
    assert(p_new_stack != NULL);
    p_new_stack->p_list = create_dll();
    p_new_stack->size = 0;
    return (p_new_stack);
}

status_t destroy_dll_stack(dll_stack_t **pp_stack){
    dll_stack_t *p_stack = *pp_stack;
    status_t s;
    s = destroy_dll(&(p_stack->p_list));
    assert(s == SUCCESS);
    free(p_stack);
    *pp_stack = NULL;
    return (SUCCESS);
}

status_t push(dll_stack_t *p_stack, data_t new_data){
    status_t s;
    s = dll_insert_beg(p_stack->p_list, new_data);
    p_stack->size ++;
    return (SUCCESS);
}

status_t pop(dll_stack_t *p_stack, data_t *p_poped_data){
    status_t s;
    s = dll_pop_beg(p_stack->p_list, p_poped_data);
    assert(s == SUCCESS);
    p_stack->size --;
    return (SUCCESS);
}

status_t get_dll_stack_top(dll_stack_t *p_stack, data_t *p_top_data){
    if(is_dll_stack_empty(p_stack)){
        return (FAILURE);
    }
    status_t s;
    s = dll_get_beg(p_stack->p_list, p_top_data);
    assert(s == SUCCESS);
    return (SUCCESS);
}

bool is_dll_stack_empty(dll_stack_t *p_stack){
    if(dll_is_list_empty(p_stack->p_list)){
        return (TRUE);
    }
    return (FALSE);
}

size_t get_sizeof_dll_stack(dll_stack_t *p_stack){
    return p_stack->size;
}

void show_dll_stack(dll_stack_t *p_stack){
    dll_list_t *p_run = NULL;
    p_run = p_stack->p_list->next;
    printf("Top-> ");
    while(p_run != NULL){
        printf("%d\n", p_run->data);
        p_run = p_run->next;
    }
}