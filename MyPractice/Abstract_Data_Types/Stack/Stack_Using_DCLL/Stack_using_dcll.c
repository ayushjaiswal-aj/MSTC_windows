#include "dcll.h"

typedef struct dcll_stack dcll_stack_t;

struct dcll_stack{
    dcll_list_t *p_list;
    size_t size;
};

dcll_stack_t* create_dcll_stack();
status_t destroy_dcll_stack(dcll_stack_t **pp_stack);
status_t push(dcll_stack_t *p_stack, data_t new_data);
status_t pop(dcll_stack_t *p_stack, data_t *p_poped);
status_t top(dcll_stack_t *p_stack, data_t *p_top);
size_t get_sizeof_dcll_stack(dcll_stack_t *p_stack);
bool is_dcll_stack_empty(dcll_stack_t *p_stack);
void show_dcll_stack(dcll_stack_t *p_stack);

int main(void){
    dcll_stack_t *p_stack = NULL;
    p_stack = create_dcll_stack();
    data_t data;
    status_t s;
    int i;
    for(i = 1; i <= 10; i++){
        s = push(p_stack, i*10);
        assert(s == SUCCESS);
    }
    show_dcll_stack(p_stack);

    s = top(p_stack, &data);
    if(s == SUCCESS){
        printf("top of stack = %d\n", data);
    }

    printf("size of stack = %zd\n", get_sizeof_dcll_stack(p_stack));

    s = pop(p_stack, &data);
    if(s == SUCCESS){
        printf("poped data = %d\n", data);
    }

    printf("sizeof of stack after pop: %zd\n", get_sizeof_dcll_stack(p_stack));

    show_dcll_stack(p_stack);

    s = destroy_dcll_stack(&p_stack);
    if(s == SUCCESS){
        printf("stack destroyed....\n");
    }

    return (EXIT_SUCCESS);
}

dcll_stack_t* create_dcll_stack(){
    dcll_stack_t *p_stack = NULL;
    p_stack = (dcll_stack_t *)xmalloc(sizeof(dcll_stack_t));
    assert(p_stack != NULL);
    p_stack->p_list = create_dcll();
    p_stack->size = 0;
    return (p_stack);
}

status_t destroy_dcll_stack(dcll_stack_t **pp_stack){
    dcll_stack_t *p_stack = *pp_stack;
    status_t s;
    s = destroy_dcll(&(p_stack->p_list));
    assert(s == SUCCESS);
    free(p_stack);
    *pp_stack = NULL;
    return (SUCCESS);
}

status_t push(dcll_stack_t *p_stack, data_t new_data){
    status_t s;
    s = dcll_insert_beg(p_stack->p_list, new_data);
    assert(s == SUCCESS);
    p_stack->size ++;
    return (SUCCESS);
}

status_t pop(dcll_stack_t *p_stack, data_t *p_poped){
    status_t s;
    s = dcll_pop_beg(p_stack->p_list, p_poped);
    assert(s == SUCCESS);
    p_stack->size --;
    return (SUCCESS);
}

status_t top(dcll_stack_t *p_stack, data_t *p_top){
    status_t s;
    s = dcll_get_beg(p_stack->p_list, p_top);
    assert(s == SUCCESS);
    return(SUCCESS);
}

size_t get_sizeof_dcll_stack(dcll_stack_t *p_stack){
    return (p_stack->size);
}

bool is_dcll_stack_empty(dcll_stack_t *p_stack){
    if(dcll_is_list_empty(p_stack->p_list)){
        return (TRUE);
    }
    return (FALSE);
}

void show_dcll_stack(dcll_stack_t *p_stack){
    dcll_node_t *p_run = p_stack->p_list->next;
    printf("Top-> ");
    while(p_run != p_stack->p_list){
        printf("%d\n", p_run->data);
        p_run = p_run->next;
    }
}