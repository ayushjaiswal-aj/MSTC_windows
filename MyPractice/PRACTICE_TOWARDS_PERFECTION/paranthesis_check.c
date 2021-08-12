#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int bool;

bool areParanthesisOk(const char *str);

int main(void){
    char *p_paranthesis_string = "(()({))}";
    
    if(areParanthesisOk(p_paranthesis_string)){
        printf("paranthesis are ok");
    }
    else {
        printf("paranthesis are not ok");
    }

    exit(EXIT_SUCCESS);
}

bool areParanthesisOk(const char *str){
    int i = 0;
    int count_round = 0, count_curly = 0, count_square = 0;

    while(str[i] != '\0'){
        switch(str[i]){
            case '(':
                count_round ++;
                break;
            
            case ')':
                count_round --;
                if(count_round < 0){
                    return FALSE;
                }
                break;
            
            case '{':
                count_curly ++;
                break;
            
            case '}':
                count_curly --;
                if(count_curly < 0){
                    return FALSE;
                }
                break;
            
            case '[':
                count_square ++;
                break;
            
            case ']':
                count_square --;
                if(count_square < 0){
                    return FALSE;
                }
                break;

            default:
                ;
        }
        i++;
    }
    if(count_round == 0 && count_curly == 0 && count_square == 0){
            return TRUE;
    }
    return FALSE;
}