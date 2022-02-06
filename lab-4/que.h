#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum Boolean{FALSE=0, TRUE}Boolean;
typedef int Element;

typedef struct queueNode* QNODE;
typedef struct queue* QUEUE;

struct queueNode {
    int element;
    QNODE next;
};

struct queue {
    QNODE head;
    QNODE tail;
    int size;
};

QUEUE newQ();
Boolean isEmptyQ(QUEUE q);
QUEUE delQ(QUEUE q);
Element front(QUEUE q);
QUEUE addQ(QUEUE q, Element e);
int lengthQ(QUEUE q);

#endif