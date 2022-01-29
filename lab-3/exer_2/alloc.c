#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int heapSpace = 0;

int* myalloc(int space) {
    heapSpace += space;
    return (int*)malloc(space);
}

void myfree(int *p, int M) {
    heapSpace -= sizeof(p);
    free(p);
}

int main() {
    srand(time(0));
    int M=(rand() % 15001) + 10000;
    // for (int i = 0; i<20; i++)
    // printf("%d\n", M);
    int *A;

    while(A = myalloc(M)) {
        M = (rand() % 15001) + 10000;
        printf("M is: %d, HEAP SIZE is %d, Address of A[0]: %u and A[M-1]: %u\n", M, heapSpace, &A[0], &A[M-1]);
        myfree(A,M);
    }
}