#include "recursiveMerge.h"

extern int STACK_TOP;

void recursiveMS(Element Ls[], int sz) {
    int mid = sz / 2;
    if(sz>1) {
        recursiveMS(Ls, mid);
        recursiveMS(&Ls[mid], mid + sz % 2);
    }
    ELIST sorted = (ELIST)malloc(sizeof(Element) * sz);
    merge(Ls, mid, &Ls[mid], mid + sz % 2, sorted);
    //copy sorted array back into Ls
    for (int i = 0; i<sz; i++) {
        Ls[i] = sorted[i];
    }
    if(sz==1) {
        int i;
        STACK_TOP = &i;
    }
    free(sorted);
}