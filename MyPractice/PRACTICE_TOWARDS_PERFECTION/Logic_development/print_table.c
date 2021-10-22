/*
 * write a program to print the multiplication tale of the number entered by the user.
 */

#include <stdio.h>

#define EXIT_SUCCESS 0
#define SUCCESS 1

typedef int status_t;

status_t print_table(int n);
int get_number();

int main(void){
    int n;
    n = get_number();
    print_table(n);

    return (EXIT_SUCCESS);
}

int get_number(){
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    return n;
}

status_t print_table(int n){
    int i;
    for(i=1; i<=10; i++){
        printf("%d * %d = %d\n", n, i, i*n);
    }
    printf("\n");
    return SUCCESS;
}