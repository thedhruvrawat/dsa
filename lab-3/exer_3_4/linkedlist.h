#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "alloc.h"

typedef struct linkedList* LIST;
typedef struct node* NODE;

struct node {
    int element;
    NODE next;
};

struct linkedList {
    int count;
    NODE first;
};

LIST createEmptyList();
void insertFirst(LIST head, int ele);
NODE deleteFirst(LIST head);
void printList(LIST head);

#endif