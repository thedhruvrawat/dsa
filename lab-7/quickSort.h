#ifndef __QUICKSORT_H
#define __QUICKSORT_H

#include "stack.h"

#define MIN(a, b) (((a)<(b))?(a):(b))

void swap(employee *a, employee *b);
int partition(EMP_LIST arr, int l, int h);
void quickSort(EMP_LIST arr, int s, int threshold);
void insertionSort(EMP_LIST arr, int size);

#endif