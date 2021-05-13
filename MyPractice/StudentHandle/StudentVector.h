#ifndef _STUDENT_VECTOR_H
#define _STUDENT_VECTOR_H

#include "Student.h"

struct StudentVector{
    struct Student** pStudentTable;
    int iSize;
};

struct StudentVector* CreateStrudentVector(void);
int PushBack(struct StudentVector *pStudentVector, struct Student *pStudent);
int DestroyStudentVector(struct StudentVector *pStudentVector);

#endif /*_STUDENT_VECTOR_H*/