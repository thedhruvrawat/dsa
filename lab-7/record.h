#ifndef __RECORD_H
#define __RECORD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[11];
    long int empID;
} employee;

typedef employee* EMP_LIST;

#endif