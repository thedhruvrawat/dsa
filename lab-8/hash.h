#ifndef __HASH_H
#define __HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct LLNODE {
    int id, count;
    struct LLNODE *next;
};  

typedef struct {
    int elCount, insertCost, queryCost;
    struct LLNODE** head;
} HASHTABLE;

HASHTABLE *createHASHTABLE(int tblSize);
HASHTABLE *insertInHASHTABLE(HASHTABLE *ht, char **strings, int pos);
int insertAll(HASHTABLE *ht, char **book);
struct LLNODE *lookup(HASHTABLE *ht, char *string, char **book);
int lookupAll(HASHTABLE *ht, char **book, char **strings, double m);

#endif