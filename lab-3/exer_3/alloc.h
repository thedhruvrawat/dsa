#ifndef __ALLOC_H
#define __ALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef size_t INT;

extern unsigned long long heapSpace;

void *myalloc(INT space);
void myfree(void *p, INT M);
void printHeapSize();

#endif