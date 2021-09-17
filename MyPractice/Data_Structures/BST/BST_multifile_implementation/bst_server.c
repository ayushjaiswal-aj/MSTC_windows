#include "bst.h"

status_t insert_bst_node(bst_t *p_bst, data_t new_data){
    bst_node_t *p_new_node = NULL;
    bst_node_t *p_run = NULL;

    p_new_node = get_bst_node(new_data);
    assert(p_new_node != NULL);

    if(p_bst->p_root == NULL){
        p_bst->p_root = p_new_node;
        p_bst->nr_elements ++;
        return (SUCCESS);
    }

    p_run = p_bst->p_root;

    while(TRUE){
        if(new_data <= p_run->data){
            if(p_run->p_left == NULL){
                p_run->p_left = p_new_node;
                p_new_node->p_parent = p_run;
                p_bst->nr_elements ++;
                return (SUCCESS);
            }else{
                p_run = p_run->p_left;
                continue;
            }
        }
        else{
            if(p_run->p_right == NULL){
                p_run->p_right = p_new_node;
                p_new_node->p_parent = p_run;
                p_bst->nr_elements ++;
                return (SUCCESS);
            }
            else {
                p_run = p_run->p_right;
                continue;
            }
        }
    }
    return (SUCCESS);
}

void inorder_r(bst_t *p_bst){
    printf("[start]<->");
    inorder_node_r(p_bst->p_root);
    printf("[end]\n");
}

void preorder_r(bst_t *p_bst){
    printf("[start]<->");
    preorder_node_r(p_bst->p_root);
    printf("[end]\n");
}
void postorder_r(bst_t *p_bst){
    printf("[start]<->");
    postorder_node_r(p_bst->p_root);
    printf("[end]\n");
}

void inorder_node_r(bst_node_t *p_node){
    if(p_node == NULL){
        return ;
    }
    inorder_node_r(p_node->p_left);
    printf("[%d]<->", p_node->data);
    inorder_node_r(p_node->p_right);
}

void preorder_node_r(bst_node_t *p_node){
    if(p_node == NULL){
        return ;
    }
    printf("[%d]<->", p_node->data);
    preorder_node_r(p_node->p_left);
    preorder_node_r(p_node->p_right);
}

void postorder_node_r(bst_node_t *p_node){
    if(p_node == NULL){
        return;
    }
    postorder_node_r(p_node->p_left);
    postorder_node_r(p_node->p_right);
    printf("[%d]<->", p_node->data);
}

status_t delete_bst(bst_t *p_bst){
    delete_bst_nodes_r(p_bst->p_root);
    free(p_bst);
    p_bst = NULL;
    return (SUCCESS);
}

void delete_bst_nodes_r(bst_node_t *p_node){
    if(p_node == NULL){
        return ;
    }
    delete_bst_nodes_r(p_node->p_left);
    delete_bst_nodes_r(p_node->p_right);
    free(p_node);
}

bst_node_t* get_bst_node(data_t new_data){
    bst_node_t *p_node = NULL;
    p_node = (bst_node_t*)xmalloc(sizeof(bst_node_t));
    p_node->data = new_data;
    p_node->p_left = NULL;
    p_node->p_right = NULL;
    p_node->p_parent = NULL;
    return (p_node);
}

bst_t* create_bst(){
    bst_t *p_bst = NULL;
    p_bst = (bst_t *)xmalloc(sizeof(bst_t));
    p_bst->p_root = NULL;
    p_bst->nr_elements = 0;
    return (p_bst);
}

void* xmalloc(size_t size_in_bytes){
    void *p = NULL;
    p = malloc(size_in_bytes);
    assert(p != NULL);
    return p;
}