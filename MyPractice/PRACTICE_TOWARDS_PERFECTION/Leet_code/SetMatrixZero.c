#include <stdio.h>
#include <stdlib.h>

struct Node{
    int i;
    int j;
    struct Node *next;
};

typedef struct Node IndexNode;

IndexNode* getIndexNode(int i, int j);
void setZeros(int **matrix, int matrixSize, int *matrixColSize);

int main(void){
    int nrCol = 4;
    int nrRow = 7;
    int **matrix = (int **)malloc(sizeof(int*) * nrRow);
    int i, j;

    for(i = 0; i < nrRow; i++){
        matrix[i] = (int *)malloc(sizeof(int) * nrCol);
    }

    printf("Matrix before:\n");
    for(i = 0; i < nrRow; i++){
        for(j = 0; j < nrCol; j++){
            matrix[i][j] = rand() % 10;
            printf("matrix[%d][%d]: %d\t", i, j, matrix[i][j]);
        }
        printf("\n");
    }

    setZeros(matrix, nrRow, &nrCol);

    printf("Matrix after setting zeros:\n");
    for(i = 0; i < nrRow; i++){
        for(j = 0; j < nrCol; j++){
            printf("matrix[%d][%d]: %d\t", i, j, matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

IndexNode* getIndexNode (int i, int j){
    IndexNode *indexNode = (IndexNode *)malloc(sizeof(IndexNode));
    indexNode->i = i;
    indexNode->j = j;
    indexNode->next = NULL;
    return indexNode;
}

void setZeros(int** matrix, int matrixSize, int *matrixColSize){
    int i, j;
    IndexNode *indexNodeList = NULL;
    IndexNode *indexNode = NULL;
    IndexNode *run = NULL;

    for(i = 0; i < matrixSize; i ++){
        for(j = 0; j < *matrixColSize; j++){
            if(matrix[i][j] == 0){
                indexNode = getIndexNode(i, j);
                indexNode->next = indexNodeList;
                indexNodeList = indexNode;
            }
        }
    }

    run = indexNodeList;
    while(run != NULL){
        for(i = 0; i < matrixSize; i++){
            matrix[i][run->j] = 0;
        }
        for(j = 0; j < *matrixColSize; j++){
            matrix[run->i][j] = 0;
        }
        run = run->next;
    }
}