#include "quickSort.h"

void swap(employee* a, employee* b) {
    employee temp = *a;
    *a = *b;
    *b = temp;
}

int partition(EMP_LIST arr, int l, int h) {
    int lf = l;
    int rt = h;
    employee pivotEl = arr[lf];
    while(lf<rt) {
        while(arr[rt].empID > pivotEl.empID)
            rt--;        
        while(arr[lf].empID <= pivotEl.empID)
            lf++;
        if(lf<rt)
            swap(&arr[lf], &arr[rt]);
    }
    swap(&arr[l], &arr[rt]);
    return rt;
}

void quickSort(EMP_LIST arr, int s, int sublSize) {
    // printf("QUICK SORT\n");
    PAIR temp;
    temp.lo = 0, temp.hi = s-1;
    STACK *st = createEmptyStack();
    st = pushToStack(st, temp);
    while(!isStackEmpty(st)) {
        temp = stackTop(st);
        int h = temp.hi, l = temp.lo;
        if(h-l+1<sublSize)
            continue;
        int p = partition(arr, l, h);
        popFromStack(st);
        if(p+1<h) {
            temp.lo = p + 1, temp.hi = h;
            st = pushToStack(st, temp);
        }
        if(p-1>l) {
            temp.lo = l, temp.hi = p - 1;
            st = pushToStack(st, temp);
        }
    }
}

void insertionSort(EMP_LIST arr, int sz) {
    // printf("INSERTION SORT\n");
    int m, n;
    employee k;
    for (m = 1; m < sz; m++) {
        k = arr[m];
        n = m - 1;
        while(n>=0 && arr[n].empID > k.empID) {
            arr[n + 1] = arr[n];
            n--;
        }
        arr[n + 1] = k;
    }
}