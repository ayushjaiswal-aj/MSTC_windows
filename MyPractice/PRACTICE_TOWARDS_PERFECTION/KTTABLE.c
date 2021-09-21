#include <stdio.h>
#include <stdlib.h>

int main(void) {
	// your code goes here
    int T, N;
    int *timeAllocated = NULL;
    int *timeRequired = NULL;
    int *resultArray = NULL;
    int i, j;
    int complitionCount;
    int momentsAvailable;
    
    scanf("%d", &T);
    resultArray = (int*)malloc(sizeof(int) * T);    
    
    for(i=0; i<T; i++){
        complitionCount = 0;
        momentsAvailable = 0;
        scanf("%d", &N);
        timeAllocated = (int*)malloc(sizeof(int) * N);
        timeRequired = (int*)malloc(sizeof(int) * N);

        for(j=0; j<N; j++){
            scanf("%d", (timeRequired+j));
        }

        for(j=0; j<N; j++){
            scanf("%d", (timeAllocated+j));
        }
        
        for(j=0; j<N; j++){
            if(j == 0){
                momentsAvailable = timeRequired[j];
            }
            else {
                momentsAvailable = timeRequired[j] - timeRequired[j-1];
            }
            if(momentsAvailable >= timeAllocated[j]){
                complitionCount++;
            }
        }
        
        *(resultArray + i) = complitionCount;
        free(timeAllocated);
        free(timeRequired);
        timeRequired = NULL;
        timeAllocated = NULL;
    }
    for(i=0; i<T; i++){
        printf("%d\n", resultArray[i]);
    }
	return 0;
}