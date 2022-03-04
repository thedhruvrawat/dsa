#ifndef __STACK_H
#define __STACK_H

#include "record.h"

typedef struct {
    int low;
    int high;
} PAIR;

typedef struct {
	PAIR* array;
	int top;
	int size;
} STACK;

typedef enum Boolean{FALSE=0, TRUE}Boolean;

STACK *createStack();
Boolean isEmpty(STACK *st);
Boolean isFull(STACK *st);
STACK *push(STACK *st, PAIR p);
void pop(STACK *st);
PAIR top(STACK *st);
STACK *resize(STACK *st);

#endif