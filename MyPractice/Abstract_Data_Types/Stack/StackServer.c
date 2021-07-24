#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Stack.h"


struct Stack* CreateStack(unsigned int limit){
    struct Stack* pStack = (struct Stack*) malloc(sizeof(struct Stack));
    pStack->iTop = -1;
    pStack->uiLimit = limit;
    pStack->pArr = (int *)malloc(sizeof(int) * pStack->uiLimit);
    return pStack;
}

int Peek(struct Stack* pStack){
    if(IsEmpty(pStack)){
        return FAILURE;
    }
    return pStack->pArr[pStack->iTop];
}

int IsFull(struct Stack* pStack){
    return pStack->iTop == pStack->uiLimit;
}

int IsEmpty(struct Stack* pStack){
    return pStack->iTop == -1;
}

int Push(struct Stack* pStack, int iNew){
    if(IsFull(pStack)){
        return FAILURE;
    }
    pStack->pArr[++(pStack->iTop)] = iNew;

    return SUCCESS;
}

int Pop(struct Stack* pStack){
    if(IsEmpty(pStack)){
        return FAILURE;
    }
    int ret = pStack->pArr[(pStack->iTop)];
    pStack->iTop --;
    return ret;
}

void ShowStack(struct Stack *pStack){
    if(IsEmpty(pStack)){
        printf("Stack Empty\n");
        return;
    }
    int i;
    for(i=0; i <= pStack->iTop; i++){
        printf("%d\t", pStack->pArr[i]);
    }
}
