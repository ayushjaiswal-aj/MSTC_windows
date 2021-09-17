#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst2.h"

/* bst interface */

ret_t insert_bst_node(bst_t *p_bst, data_t new_data)
{
    bst_node_t *p_run = NULL;
    bst_node_t *p_new_node = NULL;

    p_new_node = get_bst_node(new_data);
    p_run = p_bst->p_root_node;

    if(p_run == NULL)
    {
        p_bst->p_root_node = p_new_node;
        p_bst->nr_elements = 1;
        return (SUCCESS);
    }

    while (TRUE)
    {
        if(p_run->data <= new_data)
        {
            if(p_run->left == NULL)
            {
                p_run->left = p_new_node;
                p_new_node->parent = NULL;
                p_bst->nr_elements ++;
                return (SUCCESS);
            }
            else 
            {
                p_run = p_run->left;
                continue;
            }
        }
        else 
        {
            if(p_run->right == NULL)
            {
                p_run->right = p_new_node;
                p_new_node->parent = p_run;
                p_bst->nr_elements ++;
                return (SUCCESS);
            }
            else 
            {
                p_run = p_run->right;
                continue;
            }
        }
    }
    return (FAILURE);
}

void inorder_r(bst_t *p_bst)
{
    printf("[start]<->");
    __inorder_r(p_bst->p_root_node);
    printf("[end]\n");
}

void preorder_r(bst_t *p_bst)
{
    printf("[start]<->");
    __preorder_r(p_bst->p_root_node);
    printf("[end]\n");
}

void postorder_r(bst_t *p_bst)
{
    printf("[start]<->");
    __postorder_r(p_bst->p_root_node);
    printf("[end]\n");
}

void inorder_nrc(bst_t *p_bst)
{
    stack_t *p_stack = NULL;
    bst_node_t *p_run = NULL;

    p_stack = create_bstptr_stack();
    p_run = p_bst->p_root_node;

    printf("[start]<->");
    while(TRUE)
    {
        while(p_run != NULL)
        {
            push_bstptr(p_stack, p_run);
            p_run = p_run->left;
        }

        if(pop_bstptr(p_stack, &p_run) == STACK_EMPTY)
        {
            break;
        }

        printf("[%d]<->", p_run->data);
        p_run = p_run->right;
    }
    printf("[end]\n");
    destroy_bstptr_stack(&p_stack);
}

void preorder_nrc(bst_t *p_bst)
{
    stack_t *p_stack = NULL;
    bst_node_t *p_run = NULL;

    p_stack = create_bstptr_stack();
    p_run = p_bst->p_root_node;

    printf("[START]<->");
    while(TRUE)
    {
        while(p_run != NULL)
        {
            printf("[%d]<->", p_run->data);
            push_bstptr(p_stack, p_run);
            p_run = p_run->left;
        }

        if(pop_bstptr(p_stack, &p_run) == STACK_EMPTY)
        {
            break;
        }

        p_run = p_run->right;
    }
    printf("[end]\n");
    destroy_bstptr_stack(&p_stack);
}

void postorder_nrc(bst_t *p_bst)
{
    bst_node_t *p_run = NULL;
    stack_t *p_stack = NULL;
    color_t color;

    p_stack = create_bstptr_stack();
    p_run = p_bst->p_root_node;

    printf("[START]<->");
    while(TRUE)
    {
        while(p_run != NULL)
        {
            push_bstptr(p_stack, p_run);
            set_bstptr_top_color(p_stack, GREY);
            p_run = p_run->left;
        }

        if(get_bstptr_top_color(p_stack, &color) == STACK_EMPTY)
        {
            break;
        }

        if(color == GREY)
        {
            set_bstptr_top_color(p_stack, BLACK);
            top_bstptr(p_stack, &p_run);
            p_run = p_run->right;
            continue;
        }
        
        if(color == BLACK)
        {
            pop_bstptr(p_stack, &p_run);
            printf("[%d]<->", p_run->data);
            p_run = NULL;
        }
    }
    printf("[end]\n");
    destroy_bstptr_stack(&p_stack);
}

ret_t maximum_bst(bst_t *p_bst, data_t *p_max_data)
{
    if(is_bst_empty(p_bst))
    {
        return (BST_EMPTY);
    }
    bst_node_t *p_run = NULL;
    p_run = p_bst->p_root_node;

    while(p_run->right != NULL)
    {
        p_run = p_run->right;
    }

    *p_max_data = p_run->data;
    return (SUCCESS);
}

ret_t minimum_bst(bst_t *p_bst, data_t *p_min_data)
{
    if(is_bst_empty(p_bst))
    {
        return (BST_EMPTY);
    }
    bst_node_t *p_run = NULL;
    p_run = p_bst->p_root_node;
    while(p_run->left != NULL)
    {
        p_run = p_run->left;
    }
    *p_min_data = p_run->data;
    return (SUCCESS);
}

ret_t inorder_successor(bst_t *p_bst, data_t e_data, data_t *p_succ_data)
{
    bst_node_t *p_succ_node = NULL;
    bst_node_t *p_search_node = NULL;

    p_search_node = search_bst_node(p_bst->p_root_node, e_data);
    if(p_search_node == NULL)
    {
        return (BST_DATA_NOT_FOUND);
    }

    p_succ_node = get_successor_bst_node(p_search_node);
    
    if(p_succ_node != NULL)
    {
        *p_succ_data = p_succ_node->data;
        return (SUCCESS);
    }
    return (FAILURE);
}

ret_t inorder_predecessosr(bst_t *p_bst, data_t e_data, data_t *p_pred_data)
{
    bst_node_t *p_pred_node = NULL;
    bst_node_t *p_search_node = NULL;

    p_search_node = search_bst_node(p_bst->p_root_node, e_data);
    if(p_search_node == NULL)
    {
        return (BST_DATA_NOT_FOUND);
    }
    
    p_pred_node = get_predecessor_bst_node(p_search_node);

    if(p_pred_node != NULL)
    {
        *p_pred_data = p_pred_node->data;
        return (SUCCESS);
    }
    return (FAILURE);
}

ret_t search_bst_data(bst_t *p_bst, data_t search_data)
{
    bst_node_t *p_run = NULL;
    p_run = p_bst->p_root_node;

    while(p_run != NULL)
    {
        if(p_run->data == search_data)
            return SUCCESS;
        else if (search_data < p_run->data)
            p_run = p_run->left;
        else 
            p_run = p_run->right;
    }

    return (FAILURE);
}

ret_t remove_bst_node(bst_t *p_bst, data_t r_data)
{
    bst_node_t *z = NULL;
    bst_node_t *y = NULL;

    z = search_bst_node(p_bst->p_root_node, r_data);
    
    if(z == NULL)
    {
        return (BST_DATA_NOT_FOUND);
    }

    if(z->left == NULL)
    {
        transplant_bst(p_bst, z, z->right);
    }
    else if (z->right == NULL)
    {
        transplant_bst(p_bst, z, z->left);
    }
    else 
    {
        y = get_successor_bst_node(z);
        if (z->right != y)
        {
            transplant_bst(p_bst, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant_bst(p_bst, z, y);
        y->left = z->left;
        y->left->parent = y;
    }

    free(z);
    z = NULL;

    p_bst->nr_elements --;
    return (SUCCESS);
}

ret_t remove_bst_extended(bst_t *p_bst, data_t r_data)
{
    bst_node_t *x = NULL;
    bst_node_t *y = NULL;
    x = search_bst_node(p_bst->p_root_node, r_data);

    /* case 1 : right subtree is absent */
    if(x->right == NULL)
    {
        if(x->parent == NULL)
        {
            p_bst->p_root_node = x->left;    
        }
        else if(x == x->parent->left)
        {
            x->parent->left = x->left;
        }
        else 
        {
            x->parent->right = x->left;
        }
        if(x->left != NULL)
        {
            x->left->parent = x->parent;
        }
    }
    else if(x->left == NULL)
    {
        if(x->parent == NULL)
        {
            p_bst->p_root_node = x->right;
        }
        else if(x == x->parent->left)
        {
            x->parent->left = x->right;
        }
        else 
        {
            x->parent->right = x->right;
        }
        if (x->right != NULL)
        {
            x->right->parent = x->parent;
        }
    }
    else 
    {
        y = x->right;
        while(y->left != NULL)
        {
            y = y->left;
        }
        
        if(x->right != y)
        {
            if(y->parent->left == y)
            {
                y->parent->left = y->right;
            }
            else 
            {
                y->parent->right = y->right;
            }
            y->right = x->right;
            y->right->parent = y;
        }

        if(x->parent == NULL)
        {
            p_bst->p_root_node = y;
        }
        else if(x == x->parent->left)
        {
            x->parent->left = y;
        }
        else 
        {
            x->parent->right = y;
        }

        y->parent = x->parent;
        y->left = x->left;
        y->left->parent = y;
    }

    free(x);
    x = NULL;

    p_bst->nr_elements --;
    return (SUCCESS);
}

bst_t* create_bst()
{
    return ((bst_t*)xcalloc(1, sizeof(bst_t)));
}

ret_t destroy_bst(bst_t **pp_bst)
{
    bst_t *p_bst = NULL;
    p_bst = *pp_bst;
    __destroy_bst_r(p_bst->p_root_node);
    free(p_bst);
    *pp_bst = NULL;
    return (SUCCESS);
}

/* bst auxillary */

void __inorder_r(bst_node_t *p_root_node)
{
    if(p_root_node == NULL)
    {
        return;
    }
    __inorder_r(p_root_node->left);
    printf("[%d]<->", p_root_node->data);
    __inorder_r(p_root_node->right);
}
void __preorder_r(bst_node_t *p_root_node)
{
    if(p_root_node == NULL)
    {
        return;
    }
    printf("[%d]<->", p_root_node->data);
    __preorder_r(p_root_node->left);
    __preorder_r(p_root_node->right);
}

void __postorder_r(bst_node_t *p_root_node)
{
    if(p_root_node == NULL)
    {
        return;
    }
    __postorder_r(p_root_node->left);
    __postorder_r(p_root_node->right);
    printf("[%d]<->", p_root_node->data);
    
}

void __destroy_bst_r(bst_node_t *p_root_node)
{
    if(p_root_node == NULL)
    {
        return;
    }    
    __destroy_bst_r(p_root_node->left);
    __destroy_bst_r(p_root_node->right);
    free(p_root_node);
}

bool is_bst_empty(bst_t *p_bst)
{
    return (p_bst->p_root_node == NULL);
}

bst_node_t* get_successor_bst_node(bst_node_t *p_bst_node)
{
    bst_node_t *x = NULL;
    bst_node_t *y = NULL;
    bst_node_t *p_run = NULL;

    x = p_bst_node;
    
    /* case 1 : when right sub three is present*/
    if(x->right != NULL)
    {
        p_run = x->right;
        while(p_run->left != NULL)
        {
            p_run = p_run->left;
        }
        return p_run;
    }

    /* case 2 : when right sub tree is absent */
    y = x->parent;
    while(y != NULL && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

bst_node_t* get_predecessor_bst_node(bst_node_t *p_bst_node)
{
    bst_node_t *x = NULL;
    bst_node_t *y = NULL;
    bst_node_t *p_run = NULL;

    x = p_bst_node;
    
    /* case 1 : if left subtree is present */
    if(x->left != NULL)
    {
        p_run = x->left;
        while(p_run->right != NULL)
        {
            p_run = p_run->right;
        }
        return p_run;
    }

    /* case 2: if left subtree is absent */
    y = x->parent;
    while (y != NULL && x == y->left)
    {
        x = y;
        y = y->parent;
    }
    return (y);
}

bst_node_t* search_bst_node(bst_node_t *p_root_node, data_t search_data)
{
    bst_node_t *p_run = NULL;
    p_run = p_root_node;
    while(p_run != NULL)
    {
        if(search_data == p_run->data)
            return p_run;
        else if(search_data < p_run->data)  
            p_run = p_run->left;
        else 
            p_run = p_run->right;
    }

    return (p_run);
}

bst_node_t* get_bst_node(data_t new_data)
{
    bst_node_t *p_bst_node = NULL;
    p_bst_node = (bst_node_t*)xcalloc(1, sizeof(bst_node_t));
    assert(p_bst_node != NULL);
    p_bst_node->left = NULL;
    p_bst_node->right = NULL;
    p_bst_node->parent = NULL;

    return (p_bst_node);
}

void transplant_bst(bst_t *p_bst, bst_node_t *u, bst_node_t *v)
{
    if(u->parent == NULL)
    {
        p_bst->p_root_node = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else 
    {
        u->parent->right = v;
    }
    if(v)
    {
        v->parent = u->parent;
    }
}

/* BST auxillary - stack interface */

ret_t push_bstptr(stack_t *p_stack, bst_node_t *p_bst_node)
{
    return (insert_bstptr_end(p_stack, p_bst_node));
}

ret_t top_bstptr(stack_t *p_stack, bst_node_t **pp_bst_node)
{
    return (examine_bstptr_end(p_stack, pp_bst_node));
}

ret_t pop_bstptr(stack_t *p_stack, bst_node_t **pp_bst_node)
{
    return (examine_and_delete_bstptr_end(p_stack, pp_bst_node));
}

ret_t set_bstptr_top_color(stack_t *p_stack, color_t new_color)
{
    if(is_bstptr_stack_empty(p_stack))
    {
        return (STACK_EMPTY);
    }
    p_stack->prev->color = new_color;
    return (SUCCESS);
}

ret_t get_bstptr_top_color(stack_t *p_stack, color_t *p_color)
{
    if(is_bstptr_stack_empty)
    {
        return (STACK_EMPTY);
    }
    *p_color = p_stack->prev->color;
    return (SUCCESS);
}

ret_t destroy_bstptr_stack(stack_t **pp_stack)
{
    return (destroy_bstptr_list(pp_stack));
}

stack_t* create_bstptr_stack()
{
    return (create_bstptr_list());
}

bool is_bstptr_stack_empty(stack_t *p_stack)
{
    return (is_bstptr_list_empty(p_stack));
}

/* BST auxillary - list interface */

ret_t insert_bstptr_end(list_t *p_list, bst_node_t *p_bst_node)
{
    generic_bstptr_insert(p_list->prev, get_bstptr_node(p_bst_node), p_list);
    return (SUCCESS);
}

ret_t examine_bstptr_end(list_t *p_list, bst_node_t **pp_bst_node)
{
    if(is_bstptr_list_empty(p_list))
    {
        return (LIST_EMPTY);
    }
    *pp_bst_node = p_list->prev->p_bst_node;
    return (SUCCESS);
}

ret_t examine_and_delete_bstptr_end(list_t *p_list, bst_node_t **pp_bst_node)
{
    if(is_bstptr_list_empty(p_list))
    {
        return (LIST_EMPTY);
    }
    *pp_bst_node = p_list->prev->p_bst_node;
    generic_bstptr_delete(p_list->prev);
    return (SUCCESS);
}

ret_t destroy_bstptr_list(list_t **pp_list)
{
    list_t *p_list = NULL;
    bstptr_node_t *p_run = NULL, *p_run_next = NULL;
    
    p_list = *pp_list;
    p_run = p_list->next;
    while(p_run != p_list)
    {
        p_run_next = p_run->next;
        free(p_run);
        p_run = p_run_next;
    }
    free(p_list);
    *pp_list = NULL;

    return (SUCCESS);
}

list_t* create_bstptr_list(void)
{
    list_t *p_list = NULL;
    p_list = get_bstptr_node(NULL);
    p_list->next = p_list;
    p_list->prev = p_list;

    return (p_list);
}

bool is_bstptr_list_empty(list_t *p_list)
{
    return (p_list->next == p_list && p_list->prev == p_list);
}

/* BST auxillary - list auxillary */

void generic_bstptr_insert(bstptr_node_t *p_beg, bstptr_node_t *p_mid, bstptr_node_t *p_end)
{
    p_beg->next = p_mid;
    p_mid->next = p_end;
    p_end->prev = p_mid;
    p_mid->prev = p_beg;
}

void generic_bstptr_delete(bstptr_node_t *p_delete_node)
{
    p_delete_node->next->prev = p_delete_node->prev;
    p_delete_node->prev->next = p_delete_node->next;
    free(p_delete_node);
    p_delete_node = NULL;
}

bstptr_node_t* search_bstptr_node(list_t *p_list, bst_node_t *p_bst_node)
{
    bstptr_node_t *p_run = NULL;
    p_run = p_list->next;
    while(p_run != p_list)
    {
        if(p_run->p_bst_node == p_bst_node)
        {
            return p_run;
        }
        p_run = p_run->next;
    }
    return (NULL);
}

bstptr_node_t* get_bstptr_node(bst_node_t *p_bst_node)
{
    bstptr_node_t *p_new_node = NULL;
    p_new_node = (bstptr_node_t *)xcalloc(1, sizeof(bstptr_node_t));
    p_new_node->p_bst_node = p_bst_node;
    p_new_node->next = NULL;
    p_new_node->prev = NULL;

    return (p_new_node);
}

/* auxillary memory allocation */
void* xcalloc(size_t n, size_t s)
{
    void *p = NULL;
    p = calloc(n, s);
    assert(p != NULL);
    return p;
}