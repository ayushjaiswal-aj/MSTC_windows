#include "StudentVector.h"

int main(void){
    int iStudent1, iStudent2;

    InitStudentLib();

    iStudent1 = CreateStudent(133, 'A');
    iStudent2 = CreateStudent(44, 'B');

    ShowStudent(iStudent1);
    ShowStudent(iStudent2);

    SetRoll (iStudent1, 33);
    SetSection(iStudent1, 'a');

    ShowStudent(iStudent1);

    printf("Student2=> roll: %d\tsection: %c\n", GetRoll(iStudent2), GetSection(iStudent2));

    ReleaseStudentLib();

    return 0;
}