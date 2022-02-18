#include "insertionSort.h"

extern long long int STACK_TOP;

RECORD insertInOrder(RECORD arr, int index){
    RECORD temp = &arr[index-1];
    while(arr != temp){
        RECORD prev = temp-1;
        if(prev->CardNum > temp->CardNum){
            record a = *prev;
            *prev = *temp;
            *temp = a;
        }
        temp--;
    }
    return arr;
}

RECORD insertionSort(RECORD arr, int size){
    if(size > 1){
        insertionSort(arr, size-1);
    }
    insertInOrder(arr, size);
    if(size == 1) {
        int a;
        STACK_TOP = (int)&a;
    }
    return arr;
}
