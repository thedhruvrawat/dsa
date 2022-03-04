#include "quickSort.h"

void swap(employee* a, employee* b) {
    employee temp = *a;
    *a = *b;
    *b = temp;
}

int partition(EMP_LIST arr, int l, int h) {
    employee pivot = arr[l];
    int left = l;
    int right = h;
    while(left<right) {
        while(arr[left].empID <= pivot.empID)
            left++;
        while(arr[right].empID > pivot.empID)
            right--;
        if(left<right)
            swap(&arr[left], &arr[right]);
    }
    swap(&arr[l], &arr[right]);
    return right;
}

void quickSort(EMP_LIST arr, int s, int threshold) {
    STACK *st = createStack();
    PAIR temp;
    temp.low = 0;
    temp.high = s-1;
    st = push(st, temp);
    while(!isEmpty(st)) {
        temp = top(st);
        pop(st);
        int high = temp.high;
        int low = temp.low;
        if(high-low+1<threshold)
            continue;
        int p = partition(arr, low, high);
        if(p-1>low) {
            temp.low = low;
            temp.high = p - 1;
            st = push(st, temp);
        }
        if(p+1<high) {
            temp.low = p + 1;
            temp.high = high;
            st = push(st, temp);
        }
    }
}

void insertionSort(EMP_LIST arr, int size) {
    int i = 0, j;
    for (int i = 1; i < size; i++) {
        j = i - 1;
        employee key = arr[i];
        while(j>=0 && arr[j].empID > key.empID) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}