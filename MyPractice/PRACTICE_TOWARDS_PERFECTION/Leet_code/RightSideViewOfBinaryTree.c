/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#include <stdio.h>
#include <stdlib.h>

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxLevel = 0;
int count = 0;

void rightViewHelper(struct TreeNode *root, int *retArray, int level);
int* rightSideView(struct TreeNode *root, int *returnSize);

int main(void){
    
}

void rightViewHelper(struct TreeNode *root, int *retArray, int level){
    if(root == NULL){
        return;
    }
    if(maxLevel < level){
        retArray[count] = root->val;
        count++;
        maxLevel = level;
    }
    
    rightViewHelper(root->right, retArray, level+1);
    rightViewHelper(root->left, retArray, level+1);
}

int* rightSideView(struct TreeNode* root, int* returnSize){
    int *retArray = NULL;
    
    retArray = (int *)malloc(sizeof(int) * 100);
    count = 0;
    maxLevel = 0;
    rightViewHelper(root, retArray, 1);
    *returnSize = count;
    return retArray;
}