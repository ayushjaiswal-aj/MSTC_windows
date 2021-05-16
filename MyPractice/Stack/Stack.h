#ifndef _STACK_H
#define _STACK_H

#define SUCCESS 0
#define FAILURE -1

struct Stack{
    int iTop;
    unsigned int uiLimit;
    int *pArr;
};

struct Stack* CreateStack(unsigned int);

int Top(struct Stack* pStack);
int IsFull(struct Stack* pStack);
int IsEmpty(struct Stack* pStack);

int Push(struct Stack* pStack, int iMember);
int Pop(struct Stack* pStack);


#endif