/*
 * Sort string.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort_string(char *str);

int main(void){
    char str[128];
    printf("Enter string: ");
    gets(str);
    printf("original string: %s\n", str);
    sort_string(str);
    printf("sorted string: %s\n", str);
    return 0;
}

void sort_string(char str[]){
    char temp;
    int str_len = strlen(str);
    int i, j;
    int c_min;
    for(i = 0; i < str_len - 1; i++){
        c_min = i;
        for(j = i; j < str_len; j++){
            if(str[i] > str[j]){
                c_min = j;
            }
        }
        temp = str[i];
        str[i] = str[c_min];
        str[c_min] = temp;
    }
}