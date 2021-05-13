#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Student.h"
#include "StudentVector.h"

struct StudentVector *pHandleTable = NULL;
struct StudentVector* CreateStudentVector(void){
    struct StudentVector *pStudentVector = NULL;
    pStudentVector = (struct StudentVector *)malloc(sizeof(struct StudentVector));
    assert(pStudentVector);

    pStudentVector->pStudentTable = NULL;
    pStudentVector->iSize = 0;

    return (pStudentVector);
}

int PushBack(struct StudentVector *pStudentVector, struct Student *pStudent){
    pStudentVector->iSize += 1;
    pStudentVector->pStudentTable = (struct Student**)realloc(  pStudentVector->pStudentTable,
                                                                (pStudentVector->iSize) * sizeof(struct Student*)
                                                            );

    assert(pStudentVector->pStudentTable);

    pStudentVector->pStudentTable[pStudentVector->iSize - 1] = pStudent;
    return SUCCESS;
}

int DestroyStudentVector(struct StudentVector *pStudentVector){
    int i;
    for(i=0; i<pStudentVector->iSize; i++){
        if(pStudentVector->pStudentTable[i]){
            free(pStudentVector->pStudentTable[i]);
        }
    }

    free(pStudentVector->pStudentTable);
    free(pStudentVector);
    pStudentVector = NULL;

    return (SUCCESS);
}

void InitStudentLib(void){
    pHandleTable = CreateStudentVector();
}

int CreateStudent(int iInitRoll, char cInitSection){
    struct Student *pNewStudent = NULL;
    int i;
    BOOL bFreeHandle = FALSE;
    int iNewHandle;
    
    pNewStudent = (struct Student*)malloc(sizeof(struct Student));
    assert(pNewStudent);

    pNewStudent->iRoll = iInitRoll;
    pNewStudent->cSection = cInitSection;

    for(i=0; i<pHandleTable->iSize; i++){
        if(pHandleTable->pStudentTable[i] == NULL){
            bFreeHandle = TRUE;
            break;
        }

        bFreeHandle = FALSE;
    }
    if(bFreeHandle == FALSE){
        PushBack(pHandleTable, pNewStudent);
        iNewHandle = pHandleTable->iSize - 1;
    }
    else{
        pHandleTable->pStudentTable[i] = pNewStudent;
        iNewHandle = i;
    }

    return (iNewHandle);
}

int GetRoll(int iStudentId){
    if(iStudentId < 0 || iStudentId >= pHandleTable->iSize){
        return (E_INVALID_HANDLE);
    }
    return pHandleTable->pStudentTable[iStudentId]->iRoll;
}
char GetSection(int iStudentId){
    if(iStudentId < 0 || iStudentId >= pHandleTable->iSize){
        return (E_INVALID_HANDLE);
    }
    return (pHandleTable->pStudentTable[iStudentId]->cSection);
}

int SetRoll(int iStudentId, int iNewRoll){
    if(iStudentId < 0 || iStudentId >= pHandleTable->iSize){
        return (E_INVALID_HANDLE);
    }
    pHandleTable->pStudentTable[iStudentId]->iRoll = iNewRoll; 
    return (SUCCESS);   
}
int SetSection(int iStudentId, char cNewSection){
    if(iStudentId < 0 || iStudentId >= pHandleTable->iSize){
        return (E_INVALID_HANDLE);
    }
    pHandleTable->pStudentTable[iStudentId]->cSection = cNewSection;
    return (SUCCESS);
}

int ShowStudent(int iStudentId){
    if(iStudentId < 0 || iStudentId >= pHandleTable->iSize){
        return (E_INVALID_HANDLE);
    }
    printf("%d-%c\n", pHandleTable->pStudentTable[iStudentId]->iRoll,
                        pHandleTable->pStudentTable[iStudentId]->cSection);
    
    return SUCCESS;
}

void ReleaseStudentLib(void){
    DestroyStudentVector(pHandleTable);
}