#include "iterativeMerge.h"

extern int STACK_TOP;

void iterativeMS(Element Ls[], int sz) {
    int i;
    for (i = 2; i<sz; i*=2) {
        for(int j=0; j<sz; j+=i) {
            int mid = j + (i / 2);
            int left = MIN(i / 2, sz - j);
            int right = MIN(i / 2, sz - j - i / 2);
            if(left<i/2)
                right = 0;
            ELIST sorted = (ELIST)malloc(sizeof(Element) * (left + right));
            merge(&Ls[j], left, &Ls[mid], right, sorted);
            int temp = 0;
            for (int k = j; temp < MIN(i, left+right); k++){
                Ls[k] = sorted[temp++];
            }
            free(sorted);
        }
    }
    int x = i/2;
    ELIST sorted = (ELIST)malloc(sizeof(Element)*sz);
    merge(Ls, x, &Ls[x], sz - x, sorted);
    for(int k = 0 ; k < sz; k++){
        Ls[k] = sorted[k];
    }
    STACK_TOP = &x;
    free(sorted);
}