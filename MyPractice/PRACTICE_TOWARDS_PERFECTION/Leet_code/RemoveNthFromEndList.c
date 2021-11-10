#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int val;
    struct ListNode *next;
};

struct Stack {
    struct ListNode *top;
    int count;
};

void push(struct Stack *stack, struct ListNode *newNode);
struct ListNode* pop(struct Stack *stack);
struct ListNode* removeNthFromEnd(struct ListNode *head, int n);
struct ListNode* getListNode(int newVal);

int main(void){
    struct ListNode *head = NULL;
    struct ListNode *ptr = NULL;
    int i;
    for(i=1; i<=5; i++){
        ptr = getListNode(i);
        ptr->next = head;
        head = ptr;
    }
    ptr = head;
    while(ptr != NULL){
        printf("[%d]->", ptr->val);
        ptr = ptr->next;
    }
    printf("[end]\n");
    head = removeNthFromEnd(head, 2);
    ptr = head;
    while(ptr != NULL){
        printf("[%d]->", ptr->val);
        ptr = ptr->next;
    }
    printf("[end]\n");
    return 0;
}

void push(struct Stack *stack, struct ListNode *newNode) {
    newNode->next = stack->top;
    stack->top = newNode;
    stack->count = stack->count + 1;
}

struct ListNode* pop(struct Stack *stack){
    struct ListNode *ptr = stack->top;
    stack->top = stack->top->next;
    (stack->count) --;
    return ptr;
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode *run = NULL, *runNext = NULL;
    struct ListNode *ptr;
    int max;
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack)); 
    stack->count = 0;
    run = head;
    while(run != NULL){
        runNext = run->next;
        push(stack, run);
        run = runNext;
    }
    max = stack->count;
    head = NULL;
    int i = 0;
    while(stack->count != 0){
        ptr = pop(stack);
        if(max - stack->count  == n){
            continue;
        }
        else {
            ptr->next = head;
            head = ptr;
        }
    }
    return head;
}

struct ListNode* getListNode(int newVal){
    struct ListNode *ptr = (struct ListNode *)malloc(sizeof(struct ListNode));
    ptr->val = newVal;
    ptr->next = NULL;
    return ptr;
}