#ifndef __STACK_H
#define __STACK_H

#include "record.h"

typedef struct {
    int lo;
    int hi;
} PAIR;

typedef struct {
	PAIR* array;
	int stack_top;
	int stack_size;
} STACK;

typedef enum Boolean{FALSE=0, TRUE}Boolean;

STACK* createEmptyStack();
Boolean isStackEmpty(STACK *st);
Boolean isStackFull(STACK *st);
STACK* pushToStack(STACK *st, PAIR p);
void popFromStack(STACK *st);
PAIR stackTop(STACK *st);
STACK *resizeStack(STACK *st);

#endif