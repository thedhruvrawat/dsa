#ifndef __HEAP_H
#define __HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "record.h"

typedef struct {
    RECORD arr;
    int size;
    int maxCapacity;
} HEAP;

HEAP *initializeHeap(int size);
void exchange(record *A, record *B);
int parent(HEAP *h, int i);
int leftChild(HEAP *h, int i);
int rightChild(HEAP *h, int i);
int getHeapMaximum(HEAP *h);
int extractHeapMaximum(HEAP *h);
void HEAPIFY(HEAP *h, int i);
void buildMAXHEAP(HEAP *h, RECORD arr, int n);
HEAP *HEAPSORT(RECORD arr, int n);
void heapInsert(HEAP *h, int key);
HEAP *resize(HEAP *h);
void printHeapToFile(HEAP *h);

#endif