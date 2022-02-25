#ifndef __ITERMSORT_H
#define __ITERMSORT_H

#include "element.h"
#include "merge.h"

#define MIN(a, b) (((a)<(b))?(a):(b))

void iterativeMS(Element Ls[], int sz);

#endif