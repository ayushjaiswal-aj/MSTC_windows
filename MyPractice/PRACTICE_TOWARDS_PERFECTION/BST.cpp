#include <iostream>
#include <assert.h>

using namespace std;

#define SUCCESS 1
#define TRUE 1
#define FAILURE 0
#define FALSE 0
#define NODE_NOT_FOUND 2

typedef int data_t;
typedef int status_t;

class BST_NODE{
    private:
        data_t data;
        BST_NODE *parent;
        BST_NODE *left;
        BST_NODE *right;    
    
        BST_NODE(data_t new_data){
            this->data = new_data;
            this->parent = NULL;
            this->left = NULL;
            this->right = NULL;
        }
    
    friend class BST;
};

class BST{
    private:
        BST_NODE *root;
        size_t nr_nodes;

    public:
        BST(){
            this->root = NULL;
            this->nr_nodes = 0;
        }

    private:
        void __preorder_r(BST_NODE *p_root){
            if(p_root == NULL){
                return;
            }
            cout << "[" << p_root->data << "]";
            __preorder_r(p_root->left);
            __preorder_r(p_root->right);
        }

    public:
        status_t insert_bst(data_t new_data){
            BST_NODE *p_new_node = new BST_NODE(new_data);
            
            if(this->root == NULL){
                this->root = p_new_node;
                this->nr_nodes ++;
                return SUCCESS;
            }
            
            BST_NODE* p_run = this->root;
            while(TRUE){
                if(new_data <= p_run->data){
                    if(p_run->left == NULL){
                        p_run->left = p_new_node;
                        this->nr_nodes ++;
                        p_new_node->parent = p_run;
                        return (SUCCESS);
                    }
                    else {
                        p_run = p_run->left;
                        continue;
                    }
                }
                else {
                    if(p_run->right == NULL){
                        p_run->right = p_new_node;
                        this->nr_nodes ++;
                        p_new_node->parent = p_run;
                        return (SUCCESS);
                    }
                    else {
                        p_run = p_run->right;
                        continue;
                    }
                }
            }
        }

        void preorder_recurrsive(){
            cout << "Preorder traversal:" << endl << "[root]->";
            __preorder_r(this->root);
            cout << "[end]" << endl;
        }
};

int main(void){
    data_t data_array[] = {100, 150, 50, 120, 80, 75, 45, 30, 175, 160, 135, 190};
    BST *p_bst = new BST();
    int i = 0;
    while(i < sizeof(data_array)/sizeof(data_array[0])){
        assert(p_bst->insert_bst(data_array[i]) == SUCCESS);
        i++;
    }
    p_bst->preorder_recurrsive();
    return (EXIT_SUCCESS);
}