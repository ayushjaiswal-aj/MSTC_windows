/*
 *Maximum of three numbers
 */

#include <stdio.h>

int get_max_of_three(int a, int b, int c);

int main(void){
    int a, b, c;
    printf("Enter three numbers: ");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    printf("%d is maximum among three\n", get_max_of_three(a, b, c));
    return 0;
}

int get_max_of_three(int a, int b, int c){
    int max;
    if(a > b){
        max  = a;
    }
    else {
        max = b;
    }
    if(max < c){
        max = c;
    }
    return max;
}