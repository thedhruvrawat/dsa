#include "record.h"

RECORD insertRec(RECORD rec, char* fileName, int size) {
    // int size = 10;
    rec = (RECORD)malloc(sizeof(record)*size);

    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        printf("File not opening!\n");
        exit(0);
    }

    int i = 0;
    record temp;

    while(!feof(f)) {
        fscanf(f, "%11s %d\n", temp.name, &temp.id);
        rec[i++] = temp;
        // if (i == size) {
        //     size *= 5;
        //     rec = realloc(rec, sizeof(record) * size);
        // }
    }
    fclose(f);
    // *final_size = i;
    return rec;
}

void printList(RECORD head, int size) {
    while(size--) {
        printf("%11s %d\n", head->name, head->id);
        head++;
    }
}