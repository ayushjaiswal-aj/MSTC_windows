#include <cstdio>
#include <iostream>

/* pass by referance values */
void swap(int *pa, int *pb)
{
    int temp;
    temp = *pa;
    *pa = *pb; 
    *pb = temp;
}

/* pass by reference */
void swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int main(void)
{
    int a = 10;
    int b = 20;

    printf("Original values : a = %d, b = %d\n", a, b);
    
    swap(&a, &b);
    printf("After swap function using pass by refernce values : a = %d, b = %d\n", a, b);
    
    swap(a, b);
    printf("After swap fucntion using pass by refernce: a = %d, b = %d\n", a, b);

    return (0);
}