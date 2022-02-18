#include "record.h"

RECORD insertRec(RECORD rec, char* fileName, int* final_size) {
    int size = 10;
    rec = (RECORD)calloc(size, sizeof(record));

    // FILE *f = fopen(filename, "r");
    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        printf("File not opening!\n");
        exit(0);
    }

    int i = 0;
    record temp;

    while(!feof(f)) {
        fscanf(f, "\"%lld, %5s, %7s, %5s, %5s\"\n", &temp.CardNum, temp.BankCode, temp.ExpiryDate, temp.FirstName, temp.LastName);
        rec[i++] = temp;
        // printf("%lld, %s, %s, %s, %s\n", temp.CardNum, temp.BankCode, temp.ExpiryDate, temp.FirstName, temp.LastName);
        if (i == size) {
            // printf("Expanding size from %d to ", size);
            size *= 5;
            // printf("%d.\n", size);
            rec = realloc(rec, sizeof(record) * size);
        }
        // i++;
    }
    fclose(f);
    *final_size = i;
    return rec;
}

void printList(RECORD head, int size) {
    while(size--) {
        printf("%lld, %s, %s, %s, %s\n", head->CardNum, head->BankCode, head->ExpiryDate, head->FirstName, head->LastName);
        head++;
    }
}