#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int heapSpace = 0;

void* myalloc(int space) {
    int *p = (int *)malloc(sizeof(int) + space);
    if(p!=NULL) {
        p[0] = space;
        heapSpace += space;
        p++;
        return (void*)p;
    }
    return (void*)p;
}

void myfree(void *p) {
    int *temp = (int *)p;
    temp--;
    heapSpace -= *temp;
    free(temp);
}

int main() {
    srand(time(0));
    int M=(rand() % 15001) + 10000;
    int *A = (int*)myalloc(M);
    heapSpace -= M;
    while (A != NULL)
    {
        M = (rand() % 15001) + 10000;
        A = (int*)myalloc(M);
        printf("&A[0]: %u\t&A[M-1]: %u\n", &A[0], &A[M-1]);
        myfree(A);
    }
    myfree(A);
}