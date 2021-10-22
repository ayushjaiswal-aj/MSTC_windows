/*
 * calculate x raised to y
 */

#include <stdio.h>

int get_number();
int get_power();
int x_raised_y(int x, int y);

int main(void){
    int x, y;
    x = get_number();
    y = get_power();
    printf("%d raised to %d: %d\n", x, y, x_raised_y(x, y));
    return (0);
}

int get_number(){
    int x;
    printf("Enter number: ");
    scanf("%d", &x);
    return x;
}

int get_power(){
    int y;
    printf("Enter power: ");
    scanf("%d", &y);
    return y;
}

int x_raised_y(int x, int y){
    int i = 0;
    int sum = 1;
    while(i < y){
        sum = sum * x;
        i++;
    }
    return sum;
}