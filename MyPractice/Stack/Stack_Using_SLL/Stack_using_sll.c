#include "sll.h"

typedef struct stack_sll sll_stack_t;

struct stack_sll{
    sll_list_t *p_list;
    size_t size;
};

sll_stack_t* create_stack();
void show_stack(sll_stack_t *p_stack);
status_t destroy_sll_stack(sll_stack_t **pp_stack);
status_t push(sll_stack_t *p_stack, data_t new_data);
status_t pop(sll_stack_t *p_stack, data_t *p_data);
status_t get_stack_top(sll_stack_t *p_stack, data_t *p_data);
bool is_stack_empty(p_stack);


int main(void){
    sll_stack_t *p_stack = NULL;
    int i;
    status_t s;
    data_t data;
    p_stack = create_stack();
    
    if(is_stack_empty(p_stack)){
        printf("stack is empty... \n");
    }
    for(i = 0; i<10; i++){
        s = push(p_stack, (i+1)*10);
        assert(s == SUCCESS);
    }
    show_stack(p_stack);

    pop(p_stack, &data);
    printf("poped data: %d\n", data);

    get_stack_top(p_stack, &data);
    printf("new top of stack: %d\n", data);

    show_stack(p_stack);

    s = destroy_sll_stack(&p_stack);
    if(s == SUCCESS){
        printf("stack is destroy\n");
    }

    return (EXIT_SUCCESS);
}

void show_stack(sll_stack_t *p_stack){
    sll_node_t *p_run = NULL;
    p_run = p_stack->p_list->next;
    printf("Top->");
    while(p_run != NULL){
        printf("%d\n", p_run->data);
        p_run = p_run->next;
    }
}

status_t push(sll_stack_t *p_stack, data_t new_data){
    status_t s;
    s = sll_insert_beg(p_stack->p_list, new_data);
    p_stack->size ++;
    assert(s == SUCCESS);
    return (SUCCESS);
}

status_t pop(sll_stack_t *p_stack, data_t *p_data){
    status_t s;
    s = sll_pop_beg(p_stack->p_list, p_data);
    p_stack->size --;
    assert(s == SUCCESS);
    return (SUCCESS);
}

status_t get_stack_top(sll_stack_t *p_stack, data_t *top){
    if(is_stack_empty(p_stack)){
        return (FAILURE);
    }
    status_t s;
    s = sll_get_beg(p_stack->p_list, top);
    assert(s == SUCCESS);
    return (SUCCESS);
}

bool is_stack_empty(sll_stack_t *p_stack){
    if(sll_is_list_empty(p_stack->p_list)){
        return (TRUE);
    }
    return (FALSE);
}

sll_stack_t* create_stack(){
    sll_stack_t *p_stack = (sll_stack_t*)xmalloc(sizeof(sll_stack_t));
    p_stack->p_list = create_sll();
    p_stack->size = 0;
    return (p_stack);
}

status_t destroy_sll_stack(sll_stack_t **pp_stack){
    sll_stack_t *p_stack = *pp_stack;
    status_t s;
    s = sll_destroy_list(&(p_stack->p_list));
    assert(s == SUCCESS);
    free(p_stack);
    *pp_stack = NULL;
    return (SUCCESS);
}
