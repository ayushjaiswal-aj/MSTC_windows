#include "bst.h"

int main(void){
    bst_t *p_bst = NULL;
    data_t data[] = {100, 50, 150, 25, 65, 125, 175, 60, 130};
    int nr_elements = sizeof(data) / sizeof(data[0]);
    int i;
    status_t s;

    p_bst = create_bst();
    for(i = 0; i<nr_elements; i++){
        s = insert_bst_node(p_bst, data[i]);
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