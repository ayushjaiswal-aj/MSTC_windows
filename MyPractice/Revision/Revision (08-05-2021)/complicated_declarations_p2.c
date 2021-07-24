// Declare a pointer to array 5 of integer

int (*pA)[5];
int a[5] = {1, 2, 3, 4, 5};

int main(void){
    int i;
    int m;

    pA = &a;
    
    printf("sizeof(pA[0]) = %d\n", sizeof(pA[0]));
    printf("sizeof((*pA)[0]) = %d\n", sizeof((*pA)[0]));
    printf("sizeof(pA) = %d\n", sizeof(pA));

    printf("pA = %p\n", pA);
    printf("pA[0] = %p\n", pA[0]);

    for(i=0; i<5; i++){
        printf("&(a[%d]) = %p\n", i, &(a[i]));
    }

    printf("Printing array a:\n");

    for (i=0; i<5; i++){
        m = (*pA)[i];
        printf("m = %d\n", m);
    }

    return 0;
}

