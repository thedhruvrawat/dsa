#ifndef __RECORD_H
#define __RECORD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned long long CardNum;
    char BankCode[6];
    char FirstName[50];
    char LastName[50];
    char ExpiryDate[8];
} record;

typedef record* RECORD;

RECORD insertRec(RECORD rec, char *fileName, int *final_size);
void printList(RECORD head, int size);

#endif