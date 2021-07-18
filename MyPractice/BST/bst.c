#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0

typedef int data_t;
typedef int status_t;
typedef struct bst_node bst_node_t;
typedef struct bst bst_t;

struct bst_node{
    data_t data;
    bst_node_t *left;
    bst_node_t *right;
    bst_node_t *parent;
};

struct bst{
    bst_node_t *p_root;
    int nr_elements;
};

bst_t* create_bst(void);
status_t insert_bst(bst_t *p_bst, data_t new_data);
void preorder_r(bst_t *p_bst);
void inorder_r(bst_t *p_bst);
void postorder_r(bst_t *p_bst);
status_t delete_bst(bst_t *p_bst);

void preorder_node_r(bst_node_t *p_node);
void inorder_node_r(bst_node_t *p_node);
void postorder_node_r(bst_node_t *p_node);
void destroy_bst_nodes_r(bst_node_t *p_node);

bst_node_t* get_bst_node(data_t new_data);
void* xmalloc(size_t size_in_bytes);

int main(void){
    bst_t *p_bst = NULL;
    data_t data[] = {100, 50, 150, 25, 65, 125, 175, 60, 130};
    int nr_elements = sizeof(data) / sizeof(data[0]);
    int i;
    status_t s;

    p_bst = create_bst();
    for(i = 0; i<nr_elements; i++){
        s = insert_bst(p_bst, data[i]);
        assert(s == SUCCESS);
    }

    puts("INORDER TRAVERSAL: ");
    inorder_r(p_bst);

    puts("PREORDER TRAVERSAL: ");
    preorder_r(p_bst);

    puts("POSTORDER TRAVERSAL: ");
    postorder_r(p_bst);

    s = delete_bst(p_bst);
    assert(s == SUCCESS);

    p_bst = NULL;
    return (EXIT_SUCCESS);
}

bst_t* create_bst(){
    bst_t *p_bst = NULL;
    p_bst = (bst_t*)xmalloc(sizeof(bst_t));
    p_bst->p_root = NULL;
    p_bst->nr_elements = 0;
    return (p_bst);
}

status_t insert_bst(bst_t *p_bst, data_t new_data){
    bst_node_t *p_new_node = NULL;
    bst_node_t *p_run = NULL;
    
    p_new_node = get_bst_node(new_data);
    p_run = p_bst->p_root;

    if(p_run == NULL){
        p_bst->p_root = p_new_node;
        p_bst->nr_elements ++;
        return (SUCCESS);
    }

    while(TRUE){
        if(new_data <= p_run->data){
            if(p_run->left == NULL){
                p_run->left = p_new_node;
                p_new_node->parent = p_run;
                p_bst->nr_elements ++;
                return (SUCCESS);
            }
            else {
                p_run = p_run->left;
                continue;
            }
        }
        else{
            if(p_run->right == NULL){
                p_run->right = p_new_node;
                p_new_node->parent = p_run;
                p_bst->nr_elements ++;
                return (SUCCESS);
            }
            else{
                p_run = p_run->right;
                continue;
            }
        }
    }
}

void preorder_r(bst_t *p_bst){
    printf("[start]<->");
    preorder_node_r(p_bst->p_root);
    puts("[end]\n");
}

void inorder_r(bst_t *p_bst){
    printf("[start]<->");
    inorder_node_r(p_bst->p_root);
    puts("[end]\n");
}

void postorder_r(bst_t *p_bst){
    printf("[start]<->");
    postorder_node_r(p_bst->p_root);
    puts("[end]\n");
}

status_t delete_bst(bst_t *p_bst){
    destroy_bst_nodes_r(p_bst->p_root);
    free(p_bst);
    p_bst = NULL;
    return (SUCCESS);
}

void preorder_node_r(bst_node_t *p_node){
    if(p_node == NULL){
        return ;
    }
    printf("[%d]<->", p_node->data);
    preorder_node_r(p_node->left);
    preorder_node_r(p_node->right);
}

void inorder_node_r(bst_node_t *p_node){
    if(p_node == NULL){
        return ;
    }
    inorder_node_r(p_node->left);
    printf("[%d]<->", p_node->data);
    inorder_node_r(p_node->right);
}

void postorder_node_r(bst_node_t *p_node){
    if(p_node == NULL){
        return;
    }
    postorder_node_r(p_node->left);
    postorder_node_r(p_node->right);
    printf("[%d]<->", p_node->data);
}

void destroy_bst_nodes_r(bst_node_t *p_node){
    if(p_node == NULL){
        return ;
    } 
    destroy_bst_nodes_r(p_node->left);
    destroy_bst_nodes_r(p_node->right);
    free(p_node);
}

bst_node_t* get_bst_node(data_t new_data){
    bst_node_t *p_new_node = NULL;
    p_new_node = (bst_node_t*)xmalloc(sizeof(bst_node_t));
    p_new_node->data = new_data;
    p_new_node->left = NULL;
    p_new_node->right = NULL;
    p_new_node->parent = NULL;
    return (p_new_node);
}

void* xmalloc(size_t size_in_bytes){
    void* p_new_block = NULL;
    p_new_block = malloc(size_in_bytes);
    if(p_new_block == NULL){
        fprintf(stderr, "out of virtual memory... exiting...");
        exit(EXIT_FAILURE);
    }
    return p_new_block;
}