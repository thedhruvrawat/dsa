#ifndef __STACK_H
#define __STACK_H

#include "graph.h"
#include "extras.h"

typedef struct {
	node* array;
	int stack_top;
	int stack_size;
} STACK;

typedef enum Boolean{FALSE=0, TRUE}Boolean;

STACK* createEmptyStack();
Boolean isStackEmpty(STACK *st);
Boolean isStackFull(STACK *st);
STACK* pushToStack(STACK *st, node p);
void popFromStack(STACK *st);
node stackTop(STACK *st);
STACK *resizeStack(STACK *st);

#endif