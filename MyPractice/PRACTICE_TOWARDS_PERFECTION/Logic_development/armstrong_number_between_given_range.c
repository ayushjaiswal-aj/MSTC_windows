/*
 * armstrong number within given range.
 */

#include <stdio.h>
#include <math.h>

int get_cube_sum(int n);
void print_armstrong_numbers(int start, int end);

int main(void){
    int start, end;
    printf("enter range: ");
    scanf("%d", &start);
    scanf("%d", &end);

    print_armstrong_numbers(start, end);

    return 0;
}

int get_cube_sum(int n){
    int i, num;
    int cube_sum = 0;
    while(n != 0){
        num = n % 10;
        cube_sum = cube_sum + (num * num * num);
        n = n / 10;
    }
    return cube_sum;
}

void print_armstrong_numbers(int start, int end){
    int i, cube_sum;
    printf("armstrong numbers between range %d and %d\n", start, end);
    for(i = start; i<= end; i++){
        cube_sum = get_cube_sum(i);
        if(cube_sum == i){
            printf("%d\n", i);
        }
    }
}