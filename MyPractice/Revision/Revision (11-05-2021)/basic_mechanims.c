#include <stdio.h>
#include <stdlib.h>

int test_1(int n);
void test_2(int , int *);
void test_3(int *);

int main(void){
    int n = 100;
    int ret;

    ret = test_1(n);
    ret = -1;
    test_2(n, &ret);
    test_3(&n);

    return 0;
}

int test_1(int n){
    int result = n * 10;
    return (result);
}

void test_2(int n, int *p_result){
    int result = n * 10;
    *p_result = result;
}

void test_3(int *p_inout_int){
    *p_inout_int = *p_inout_int * 10;
}
