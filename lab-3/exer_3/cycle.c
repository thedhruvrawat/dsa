#include "cycle.h"

LIST createList(int N) {
    LIST Ls = createEmptyList();
    for (int i = 0; i<N; i++) {
        int rand_num = (rand() % 100) + 1;
        insertFirst(Ls, rand_num);
    }
    printHeapSpace("heap.txt");
    return Ls;
}

LIST createCycle(LIST Ls) {
    int toss = (rand() % 2);
    if(toss==0)
        return Ls;                              //linear
    else {
        int r = (rand() % Ls->count) + 1;       //cyclic
        NODE temp = Ls->first;
        int i = 1;
        while (temp != NULL && ++i<r) {
            // printf("%d: %d\n", i, temp->element);
            temp = temp->next;
        }
        NODE end = Ls->first;
        while(end->next!=NULL) {
            end = end->next;
        }
        end->next = temp;
        printf("Cycle created!\n");
        return Ls;
    }
}

void printHeapSpace(char* fileName) {
    FILE *f = fopen(fileName, "a");
    fprintf(f,"%lld\n",heapSpace);
    fclose(f);
}

// int main() {
//     srand(time(0));
//     printHeapSize();

//     LIST myList = createList(100);
//     int r = (rand() % myList->count) + 1;
//     printf("r is %d\n", r);
//     NODE temp = myList->first;
//     int i = 1;
//     while (temp != NULL && ++i<r) {
//         printf("%d: %d\n", i, temp->element);
//         temp = temp->next;
//     }
//     printf("current element is: %d %d", i, temp->element);
//     NODE end = myList->first;
//     while(end->next!=NULL) {
//         end = end->next;
//     }
//     printf("last element is: %d", end->element);
// }