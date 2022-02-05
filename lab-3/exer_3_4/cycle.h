#ifndef __CYCLE_H
#define __CYCLE_H

#include "linkedlist.h"

LIST createList(int N);
LIST createCycle(LIST Ls);
void printHeapSpace(char *fileName);
LIST reverseList(LIST Ls);
int testCyclic(LIST Ls);
void printData(int N, double eta);

#endif
