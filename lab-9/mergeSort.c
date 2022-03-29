#include "mergeSort.h"

void merge(record Ls1[], int sz1, record Ls2[], int sz2, record Ls[]) {
    int iter1 = 0, iter2 = 0, iter3 = 0;
    while(iter1<sz1 && iter2<sz2) {
        if(Ls1[iter1].id <= Ls2[iter2].id) {
            Ls[iter3++] = Ls1[iter1++];
        } else {
            Ls[iter3++] = Ls2[iter2++];
        }
    }
    //transfer remaining elements from Ls1 to Ls
    while(iter1<sz1) {
        Ls[iter3++] = Ls1[iter1++];
    }
    //transfer remaining elements from Ls2 to Ls
    while(iter2<sz2) {
        Ls[iter3++] = Ls2[iter2++];
    }
}

void recursiveMS(record Ls[], int sz) {
    int mid = sz / 2;
    if(sz>1) {
        recursiveMS(Ls, mid);
        recursiveMS(&Ls[mid], mid + sz % 2);
    }
    RECORD sorted = (RECORD)malloc(sizeof(record) * sz);
    merge(Ls, mid, &Ls[mid], mid + sz % 2, sorted);
    //copy sorted array back into Ls
    for (int i = 0; i<sz; i++) {
        Ls[i] = sorted[i];
    }
    // if(sz==1) {
    //     int i;
    //     STACK_TOP = &i;
    // }
    free(sorted);
}