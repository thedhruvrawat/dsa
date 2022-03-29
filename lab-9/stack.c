#include "stack.h"

STACK* createEmptyStack() {
    STACK *st = (STACK *)malloc(sizeof(STACK));
    st->stack_size = 10;
    st->array = malloc(sizeof(PAIR) * st->stack_size);
    st->stack_top = -1;
    return st;
}

Boolean isStackEmpty(STACK* st) {
    return (st->stack_top == -1);
}

Boolean isStackFull(STACK* st) {
    return (st->stack_size - 1 == st->stack_top);
}

void popFromStack(STACK* st) {
    if(!isStackEmpty(st))
        st->stack_top--;
    else
        printf("STACK UNDERFLOW!\n");
}

PAIR stackTop(STACK* st) {
    PAIR temp;    
    if(isStackEmpty(st)) {
        temp.lo = -1, temp.hi = -1;
        return temp;
    }
    return st->array[st->stack_top];
}

STACK* resizeStack(STACK* st) {
    st->stack_size *= 2;
    st->array = (PAIR *)(realloc((st->array), sizeof(PAIR) * st->stack_size * 2));
    return st;
}


STACK* pushToStack(STACK* st, PAIR p) {
    if(isStackFull(st))
        resizeStack(st);
    st->array[++st->stack_top] = p;
    return st;
}