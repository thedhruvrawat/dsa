#ifndef __ELEMENT_H
#define __ELEMENT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[10];
    float cgpa;
} Element;

typedef Element* ELIST;

#endif