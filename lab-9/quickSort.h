#ifndef __QUICKSORT_H
#define __QUICKSORT_H

#include "record.h"
#include "stack.h"

#define MIN(a, b) (((a)<(b))?(a):(b))

void swap(record *a, record *b);
int partition(RECORD arr, int l, int h);
void quickSort(RECORD arr, int s, int sublSize);
void insertionSort(RECORD arr, int sz);

#endif