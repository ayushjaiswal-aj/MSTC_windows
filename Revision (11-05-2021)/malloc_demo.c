#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(void){
    int *p = NULL;
    p = (int *) malloc(sizeof(int));
    assert(p != NULL);
    memset(p, 0, sizeof(int));

    printf("Enter an integer: ");
    scanf("%d", p);
    printf("Entered number: %d\n", *p);

    free (p);
    p = NULL;

    return 0;
}