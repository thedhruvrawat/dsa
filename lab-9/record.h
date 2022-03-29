#ifndef __RECORD_H
#define __RECORD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[11];
    int id;
} record;

typedef record* RECORD;

RECORD insertRec(RECORD rec, char *fileName, int size);
void printList(RECORD head, int size);

#endif