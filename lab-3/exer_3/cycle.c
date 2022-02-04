#include "cycle.h"
#include <sys/time.h>

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
        // printf("Cycle created!\n");
        return Ls;
    }
}

void printHeapSpace(char* fileName) {
    FILE *f = fopen(fileName, "a");
    fprintf(f,"%lld\n",heapSpace);
    fclose(f);
}

void printData(int N, double eta) {
    FILE *f = fopen("observations.xlsx", "a");
    fprintf(f,"%d,%f,%lld\n",N,eta,heapSpace);
    fclose(f);
}

int main() {
    srand(time(0));
    FILE *f = fopen("observations.xlsx", "a");
    fprintf(f,"N,Time Taken (in ms),Heap Space Used\n");
    fclose(f);
    struct timeval t1, t2;
    double elapsedTime;
    int testcases = 100;
    int n = 1;
    while(testcases--) {
        n = (rand() % 500000) + 1000000;
        LIST myList = createList(n);
        myList = createCycle(myList);
        gettimeofday(&t1, NULL);
        int flag = testCyclic(myList);
        gettimeofday(&t2, NULL);
        if(flag==1) printf("Cycle detected\n");
        else printf("Cycle not detected\n");
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        printf("N: %d, elapsed time: %f ms. & heap space: %lld\n", n, elapsedTime, heapSpace);
        printData(n, elapsedTime);
        printf("**********************************************************************\n");
        myfree(myList, myList->count);
    }
    return 0;
}