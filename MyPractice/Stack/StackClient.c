#include <stdio.h>
#include "Stack.h"

int main(void){
    struct Stack *pStack = NULL;
    unsigned int uiLimit = 10;
    pStack = CreateStack(uiLimit);

    if(Push(pStack, 10) == SUCCESS){
        printf("%d is pushed successfully\n", 10);
    }
    else{
        printf("Push Failure, Stack full\n");
    }
    
    if(Push(pStack, 20) == SUCCESS){
        printf("%d is pushed successfully\n", 20);
    }
    else{
        printf("Push Failure, Stack full\n");
    }
    
    if(Push(pStack, 30) == SUCCESS){
        printf("%d is pushed successfully\n", 30);
    }
    else{
        printf("Push Failure, Stack full\n");
    }
    
    if(Push(pStack, 40) == SUCCESS){
        printf("%d is pushed successfully\n", 40);
    }
    else{
        printf("Push Failure, Stack full\n");
    }
    
    printf("peek: %d\n", Peek(pStack));
    
    ShowStack(pStack);
    
    if(Pop(pStack) == FAILURE){
        printf("Pop Failure. Stack Empty\n");
    }
    else{
        printf("Pop success\n");
    }
    
    printf("peek: %d\n", Peek(pStack));
    
    if(Pop(pStack) == FAILURE){
        printf("Pop Failure. Stack Empty\n");
    }
    else{
        printf("Pop Success\n");
    }
}