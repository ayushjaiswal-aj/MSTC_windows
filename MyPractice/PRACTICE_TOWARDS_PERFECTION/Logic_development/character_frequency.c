/*
 * Find frequency of characters in string.
 */

#include <stdio.h>
#include <string.h>

char str[100];

void get_string();
void print_frequency();
void set_frequency();

int main(void){
    get_string();
    print_frequency();
    return (0);
}

void get_string(){
    scanf("%[^\n]%*c", str);
    printf("%s\n", str);
}

void print_frequency(){
    int freq[26] = {0};
    int i = 0;
    while(str[i] != '\0'){
        freq[str[i] - 'a'] ++;
        i++;
    }
    for(i=0; i<26; i++){
        if(freq[i] != 0){
            printf("%c: %d\n", i+'a', freq[i]);
        }
    }
}