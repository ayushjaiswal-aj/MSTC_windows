#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"

int main(void){
    bst_t *p_bst = NULL;
    data_t d_array[] = {500, 250, 750, 150, 600, 350, 400, 450, 650, 850, 900, 300, 370};
    data_t data;
    ret_t ret;
    int i;

    p_bst = create_bst();
    for(i=0; i<sizeof(d_array)/sizeof(d_array[0]); i++){
        assert(insert_bst(p_bst, d_array[i]) == SUCCESS);
    }

    puts("preorder recursive: ");
    preorder_r(p_bst);

    puts("\ninorder recursive: ");
    inorder_r(p_bst);

    puts("\npostorder recursive: ");
    postorder_r(p_bst);

    puts("\npreorder non-recursive: ");
    preorder_nrc(p_bst);

    puts("\ninorder non-recursive: ");
    inorder_nrc(p_bst);

    puts("\npostorder non-recursive: ");
    postorder_nrc(p_bst);

    if(maximum_bst(p_bst, &data) == SUCCESS){
        printf("max in bst = %d\n", data);
    }

    if(minimum_bst(p_bst, &data) == SUCCESS){
        printf("min in bst = %d\n", data);
    }

    if(inorder_successor(p_bst, 250, &data) == SUCCESS){
        printf("inorder successor of 250 is = %d\n", data);
    }

    if(preorder_successor(p_bst, 450, &data) == SUCCESS){
        printf("preoderd successor of 450 is = %d\n", data);
    }

    if(inorder_predecessor(p_bst, 250, &data) == SUCCESS){
        printf("inorder_predecessor of 250 is = %d\n", data);
    }

    if(remove_bst(p_bst, 70) == SUCCESS){
        printf("70 is removed from list\n");
    }

    puts("inorder bst after removing 70: \n");
    inorder_r(p_bst);

    ret = destroy_bst(&p_bst);

    if(ret == SUCCESS && p_bst == NULL){
        printf("bst p_bst is destroyed\n");
    }

    return (EXIT_SUCCESS);
}