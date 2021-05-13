#ifndef _STUDENT_H
#define _STUDENT_H

#define TRUE    1
#define FALSE   0

#define SUCCESS             1
#define E_INVALID_HANDLE    -1
#define E_INVALID_VALUE     -2

typedef int BOOL;

struct Student{
    int iRoll;
    char cSection;
};

void InitStudentLib(void);

int CreateStudent(int iInitRoll, char cInitSection);

int GetRoll(int iStudentId);
char GetSection(int iStudentId);

int SetRoll(int iStudentId, int iNewRoll);
int SetSection(int iStudentId, char iNewSection);

int ShowStudent(int iStudentId);
int ReleaseStudent(int iStudentId);

void ReleaseStudentLib(void);

#endif /*_STUDENT_H*/