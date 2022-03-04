#include "stack.h"

STACK* createStack() {
    STACK *st = (STACK *)malloc(sizeof(STACK));
    st->size = 10;
    st->array = malloc(sizeof(PAIR) * st->size);
    st->top = -1;
    return st;
}

Boolean isEmpty(STACK* st) {
    return (st->top == -1);
}

Boolean isFull(STACK* st) {
    return (st->size - 1 == st->top);
}

STACK* push(STACK* st, PAIR p) {
    if(isFull(st))
        resize(st);
    st->array[++st->top] = p;
    return st;
}

void pop(STACK* st) {
    if(!isEmpty(st))
        st->top--;
    else
        printf("STACK UNDERFLOW!\n");
}

PAIR top(STACK* st) {
    PAIR temp;
    temp.low = -1;
    temp.high = -1;
    if(isEmpty(st))
        return temp;
    return st->array[st->top];
}

STACK* resize(STACK* st) {
    st->array = (PAIR *)(realloc((st->array), sizeof(PAIR) * st->size * 2));
    st->size *= 2;
    return st;
}