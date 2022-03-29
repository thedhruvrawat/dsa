#ifndef __RECMSORT_H
#define __RECMSORT_H

#include "record.h"

void merge(record Ls1[], int sz1, record Ls2[], int sz2, record Ls[]);
void recursiveMS(record Ls[], int sz);

#endif