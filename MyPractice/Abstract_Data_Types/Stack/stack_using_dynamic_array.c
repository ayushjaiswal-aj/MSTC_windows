#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0
#define EMPTY_STACK 2
#define FULL_STACK 3

typedef unsigned int size;
typedef int index;
typedef int data;
typedef int status_t;
typedef int bool;

struct stack* create_stack(size stack_size);
int destroy_stack(struct stack* p_stack);
status_t push(struct stack *p_stack, data new_data);
status_t pop(struct stack *p_stack, data *poped_data);
status_t top(struct stack *p_stack, data *top_data);
bool is_full(struct stack *p_stack);
bool is_empty(struct stack *p_stack);

struct stack{
    int *pa;
    size size;
    index top_index;
};

int main(void){
    struct stack *p_stack = NULL;
    status_t s;
    p_stack = create_stack(10);
    int i = 0, top_stack, poped;
    while(!(is_full(p_stack))){
        s = push(p_stack, (i+1)*10);
        assert(s == SUCCESS);
        i++;
    }
    while(!(is_empty(p_stack))){
        s = top(p_stack, &top_stack);
        assert(s == SUCCESS);
        printf("top of stack: %d\n", top_stack);
        s = pop(p_stack, &poped);
        assert(s == SUCCESS);
        printf("poped from stack: %d\n", poped);
    }
    return (EXIT_SUCCESS);
}

status_t push(struct stack *p_stack, data new_data){
    if(is_full(p_stack)){
        return (FAILURE);
    }
    p_stack->top_index ++;
    p_stack->pa[p_stack->top_index] = new_data;
    return (SUCCESS);
}

status_t pop(struct stack *p_stack, data *poped_data){
    if(is_empty(p_stack)){
        return (FAILURE);
    }
    *poped_data = p_stack->pa[p_stack->top_index];
    p_stack->pa[p_stack->top_index] = 0;
    p_stack->top_index --;
    return (SUCCESS);
}

status_t top(struct stack *p_stack, data *top_data){
    if(is_empty(p_stack) == TRUE){
        return (FAILURE);
    }
    *top_data = p_stack->pa[p_stack->top_index];
    return (SUCCESS);
} 

bool is_empty(struct stack *p_stack){
    if(p_stack->top_index == -1){
        return (TRUE);
    }

    return (FALSE);
}

bool is_full(struct stack *p_stack){
    if(p_stack->top_index == p_stack->size){
        return (TRUE);
    }

    return (FALSE);
}

struct stack* create_stack(size stack_size){
    assert(stack_size > 0);
    struct stack* p_stack = (struct stack*)malloc(sizeof(struct stack));
    assert(p_stack);
    memset(p_stack, 0, sizeof(struct stack));
    p_stack->pa = (int *)malloc(stack_size * sizeof(int));
    memset(p_stack->pa, 0, stack_size * sizeof(int));
    p_stack->size = stack_size;
    p_stack->top_index = -1;
    return (p_stack);
}

int destroy_stack(struct stack *p_stack){
    free(p_stack->pa);
    p_stack->pa = NULL;
    free(p_stack);
    p_stack = NULL;
    return (SUCCESS);
}