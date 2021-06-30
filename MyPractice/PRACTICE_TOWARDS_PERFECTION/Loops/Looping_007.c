// nested loops: level 2

#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, j;
    int m = 8, n = 7;

    puts("block 1:");
    for(i=0; i<m; i++){
        for(j=0; j<m; j++){
            printf("i = %d, j = %d\n", i, j);
        }
    }
    puts("block 2:");
    for(i=0; i<m; i++){
        for(j = 0; j<n; j++){
            if(i < j){
                printf("i = %d, j = %d\n", i, j);
            }
        }
    }

    puts("Block 3:");
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            if(i <= j){
                printf("i = %d, j = %d\n", i, j);
            }
        }
    }

    puts("block 4:");
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            if(i>j){
                printf("i = %d, j = %d\n", i, j);
            }
        }
    }

    puts("Block 5: ");
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            if(i>j){
                printf("i = %d, j = %d\n", i, j);
            }
        }
    }
    puts("block 6:");
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            if(i==j){
                printf("i = %d, j = %d\n", i, j);
            }
        }
    }

    puts("block 7:");
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            if(i != j){
                printf("i = %d, j = %d\n", i, j);
            }
        }
    }

    return 0;
}