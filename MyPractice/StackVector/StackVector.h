#ifndef _STACK_VECTOR_H
#define _STACK_VECTOR_H

#define SUCCESS 1
#define FAILURE 0

struct Employee{
    int iId;
    char *pName;
    float fSalary;
};

struct Stack{
    struct Employee *pEmployee;
    struct Stack *pNextNode;
};



#endif