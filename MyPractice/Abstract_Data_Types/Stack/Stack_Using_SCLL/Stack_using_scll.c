#include "scll.h"

typedef struct scll_stack scll_stack_t;

struct scll_stack{
    scll_list_t *p_list;
    size_t size;
};

scll_stack_t* create_scll_stack();
status_t destroy_scll_stack(scll_stack_t **p_stack);
status_t push(scll_stack_t *p_stack, data_t data);
status_t pop(scll_stack_t *p_stack, data_t *data);
status_t get_top(scll_stack_t *p_stack, data_t *p_top);
bool is_stack_empty(scll_stack_t *p_stack);
void show_scll_stack(scll_stack_t *p_stack);

int main(void){
    scll_stack_t *p_stack = NULL;
    p_stack = create_scll_stack();
    int i;
    status_t s;
    data_t data;
    for(i = 0; i<10; i++){
        s = push(p_stack, (i+1)*10);
        assert(s == SUCCESS);
    }
    show_scll_stack(p_stack);

    s = pop(p_stack, &data);
    if(s == SUCCESS){
        printf("poped data: %d\n", data);
    }

    show_scll_stack(p_stack);

    s = get_top(p_stack, &data);
    if(s == SUCCESS){
        printf("top of stack -> %d\n", data);
    }

    s = destroy_scll_stack(&p_stack);
    if(s == SUCCESS){
        printf("stack is destroyed\n");
    }

    return (EXIT_SUCCESS);
}



scll_stack_t* create_scll_stack(){
    scll_stack_t *p_stack = (scll_stack_t*)xmalloc(sizeof(scll_stack_t));
    assert(p_stack != NULL);
    p_stack->p_list = create_scll();
    assert(p_stack->p_list != NULL);
    p_stack->size = 0;
    return p_stack;
}

status_t destroy_scll_stack(scll_stack_t **pp_stack){
    scll_stack_t *p_stack = *pp_stack;
    status_t s;
    s = destroy_scll(&(p_stack->p_list));
    if(s == SUCCESS){
        printf("list is destroyed\n");
    }
    free(p_stack);
    *pp_stack = NULL;
    return (SUCCESS);
}

status_t push(scll_stack_t *p_stack, data_t data){
    status_t s;
    s = scll_insert_beg(p_stack->p_list, data);
    assert(s == SUCCESS);
    return (SUCCESS);
}

status_t pop(scll_stack_t *p_stack, data_t *p_data){
    status_t s;
    s = scll_pop_beg(p_stack->p_list, p_data);
    assert(s == SUCCESS);
    return (SUCCESS);
}

status_t get_top(scll_stack_t *p_stack, data_t *p_top){
    status_t s;
    s = scll_get_beg(p_stack->p_list, p_top);
    assert(s == SUCCESS);
    return (SUCCESS);
}

bool is_stack_empty(scll_stack_t *p_stack){
    if(scll_is_list_empty(p_stack->p_list)){
        return (TRUE);
    }
    return (FALSE);
}

void show_scll_stack(scll_stack_t *p_stack){
    scll_node_t *p_run = NULL;
    p_run = p_stack->p_list->next;
    printf("Top-> ");
    while(p_run != p_stack->p_list){
        printf("%d\n", p_run->data);
        p_run = p_run->next;
    }
}