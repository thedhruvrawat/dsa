#include "alloc.h"

unsigned long long heapSpace = 0;

void* myalloc(INT space) {
    INT *p = (INT *)malloc(sizeof(INT));
    if(p!=NULL) {
        p[0] = space;
        heapSpace += space;
        p++;
        return (void*)p;
    }
    return (void*)p;
}

void myfree(void *p, INT M) {
    INT *temp = (INT *)p;
    temp--;
    heapSpace -= (*temp)*(M+1);
    free(temp);
}

void printHeapSize() {
    printf("%lld\n", heapSpace);
}