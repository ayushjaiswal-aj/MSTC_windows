#include <stdio.h>

int main(void){
    int i, j;
    int m = 8, n = 7, k = 3;

    puts("Block 1:");
    for(i=0; i<m; i++){
        for(j=i; j<n; j++){
            printf("i = %d, j = %d\n", i, j);
        }
    }

    puts("Block 2:");
    for(i=0; i<m; i++){
        for(j=i+1; j<n; j++){
            printf("i = %d, j = %d\n", i, j);
        }
    }

    puts("Block 3:");
    for(i = m; i > 0; i--){
        for(j = i; j > 0; j--){
            printf("i = %d, j = %d\n", i, j);
        }
    }

    puts("Block 4:");
    for(i = m; i > 0; i--){
        for(j = i; j > 0; j--){
            printf("i = %d, j = %d\n", i, j);
        }
    }

    puts("Block 5:");
    for(i = m; i > 0; i--){
        for(j = i - 1; j > 0; j--){
            printf("i = %d, j = %d\n", i, j);
        }
    }

    puts("Block 6: ");
    for(i = m; i >= 0; i = i - 3){
        for(j = i - 1; j >= 0; j = j - 3){
            printf("i = %d, j = %d\n", i, j);
        }
    }

    return (0);
}