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

int tableSize = 5000;                   
int baseNumber = 5021;
int stringCnt=0;  


int hash(int baseNumber, int tableSize, char *strings) {
    int hashSum = 0;
    for(int i=0; i<strlen(strings); i++)
        hashSum += strings[i];
    return (hashSum % baseNumber) % tableSize;
}

int collision(int size, int baseNumber, int tableSize, char** strings) {
    int hashTable[tableSize];
    for (int i = 0; i < tableSize; i++) {
        hashTable[i] = 0;
    }    
    int base = baseNumber, tblSize = tableSize, strNum = size, collisionCount = 0;
    for(int i=0; i<strNum; i++) {
        int hashValue = hash(base, tblSize, strings[i]);
        hashTable[hashValue]++;
    }
    for(int i=0; i<tableSize; i++) {
        if (hashTable[i] > 1)
            collisionCount+=hashTable[i]-1;
    }
    // printf("\nCollisions are %d\n", collisionCount);
    return collisionCount;
}

char** fileParser() {
    FILE *fptr = fopen("aliceinwonderland.txt", "r");
    int MAX = 50000, success=0;
    char **book = (char **)malloc(sizeof(char*) * MAX);
    for(int i=0; i<MAX; i++) {
        book[i] = (char *)malloc(sizeof(char) * 50);
    }
    char *validString = (char *)malloc(50*sizeof(char));
    if (fptr == NULL)
    {
        printf("File not opened\n");
        return book;
    }
    while(!(feof(fptr))) {
        fscanf(fptr," %s ",validString);
        int failed = 0;
        for(int i = 0; i<strlen(validString); i++) {
            if(!((validString[i] <= 'z' && validString[i] >= 'a') || (validString[i]>='A' && validString[i]<='Z'))) {
                failed++;
                break;
            }
        }
        if(!failed) {
            book[success] = (char*)malloc(sizeof(char)*(strlen(validString)+1));
            strcpy(book[success],validString);
            success++;
        }
    }
    stringCnt = success;
    printf("Count: %d\n", success);
    free(validString);
    fclose(fptr);
    return book;
}


HASHTABLE* createHASHTABLE(int tblSize) {
    HASHTABLE *ht = (HASHTABLE *)malloc(sizeof(HASHTABLE));
    ht->elCount = 0;
    ht->head = (struct LLNODE **)malloc(sizeof(struct LLNODE *) * tblSize);
    ht->insertCost = 0;
    ht->queryCost = 0;
    for(int i=0; i<tblSize; i++) {
        ht->head[i] = NULL;
    }
    return ht;
}


struct LLNODE* lookup(HASHTABLE* ht, char *string, char **book) {
    int id = hash(baseNumber, tableSize, string);
    struct LLNODE* front = ht->head[id];
    int cost = 0;
    while(front!=NULL) {
        if(strcmp(book[front->id],string)==0) {
            cost++;                                                     
            ht->queryCost+=cost;
            return front;
        }
        cost++;                                                        
        front = front->next;
    }
    ht->queryCost+=cost;
    return front;
}

int insertAll(HASHTABLE *ht, char **book) {
    for (int i = 0; i<stringCnt; i++) {
        ht = insertInHASHTABLE(ht, book, i);
    }
    return ht->insertCost;
}

HASHTABLE* insertInHASHTABLE(HASHTABLE* ht, char** strings, int pos) {
    int id = hash(baseNumber, tableSize, strings[pos]);
    struct LLNODE *temp = (struct LLNODE*)malloc(sizeof(struct LLNODE));
    struct LLNODE *front = ht->head[id];
    int cost = 0;
    while(front!=NULL) {
        if(strcmp(strings[pos], strings[front->id])==0) {
            ht->insertCost += cost;
            front->count++;
            return ht;
        }
        cost++;
        if(front->next==NULL)
            break;
        front = front->next;
    }
    temp->id = pos;
    temp->count = 1;
    temp->next = NULL;
    ht->elCount++;
    if(ht->head[id]==NULL) {
        ht->head[id] = temp;
    } else {
        front->next = temp;
    }
    ht->insertCost+=cost;
    return ht;
}

int lookupAll(HASHTABLE *ht, char **book, char **strings, double m) {
    int sz = (int)(m * stringCnt);
    ht->queryCost = 0;
    if(m>1) {
        int nsz = stringCnt;
        sz -= stringCnt;
        for (int i = 0; i < nsz; i++) {
            lookup(ht, strings[i], book);
        }
        m -= 1;
    }
    for (int i = 0; i < sz; i++) {
        lookup(ht, strings[i], book);
    }
    return ht->queryCost;
}

void bookProfiler(char** book)
{
    int tIndex=0, bIndex=0;
    int bNum[3][6] = {
        {5021, 6619, 8317, 5169347, 5011129, 5007137},
        {50993,81773,76777,56117293,67845619,56393651},
        {511909,661009,858311,579818819,503896961,672016379}
    };

    int tblSz[3] = {5000, 50000, 500000};
    int colVal  = collision(stringCnt, tblSz[tIndex], bNum[tIndex][bIndex], book);
    for (int i = 0; i < 3; i++) {
        for(int j=0;j<6;j++) {
            int tcol = collision(stringCnt,bNum[i][j],tblSz[i],book);
            printf("Collision count for base number %d and tableSize %d is %d\n", bNum[i][j], tblSz[i], tcol);
            if(tcol<colVal) {
                colVal = tcol;
                tIndex = i;
                bIndex = j;
            }
        }
    }
    printf("Optimum table size index = %d, Optimum base number index = %d\n", tIndex, bIndex);
}

int main() {
    char **book = fileParser();
    bookProfiler(book);
    HASHTABLE *ht = createHASHTABLE(tableSize);
    printf("Insertion cost is %d\n",insertAll(ht,book));
    printf("Element count is %d\n",ht->elCount);
    for (double i = 0.1; i <= 2.1; i+=0.1) {
        printf("Querying cost for %d%% lookup is %d\n", (int)(i*100), lookupAll(ht, book, book, i));
    }
}
