#ifndef _BST_H
#define _BST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0
#define TREE_EMPTY 3
#define TREE_NODE_NOT_FOUND 2

typedef int data_t;
typedef int status_t;
typedef struct bst_node bst_node_t;
typedef struct bst bst_t;

struct bst_node{
    data_t data;
    struct bst_node *p_left;
    struct bst_node *p_right;
    struct bst_node *p_parent;
};

struct bst{
    bst_node_t *p_root;
    int nr_elements;
};

status_t insert_bst_node(bst_t *p_bst, data_t new_data);

void inorder_r(bst_t *p_bst);
void preorder_r(bst_t *p_bst);
void postorder_r(bst_t *p_bst);

void inorder_node_r(bst_node_t *p_node);
void preorder_node_r(bst_node_t *p_node);
void postorder_node_r(bst_node_t *p_node);

status_t delete_bst(bst_t *p_bst);
void delete_bst_nodes_r(bst_node_t *p_node);

bst_node_t* get_bst_node(data_t new_data);
bst_t* create_bst();
void* xmalloc(size_t size_in_bytes);

#endif