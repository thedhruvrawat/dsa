// Hare and Tortoise Algorithm
#include "cycle.h"
#include <sys/time.h>

int isAhead(NODE a, NODE b) {
    while(b->next!=NULL) {
        if(b==a)
            return 1;       //If a is ahead of b, return 1
        b = b->next;
    }
    return 0;
}

int main() {
    struct timeval t1, t2;
    double elapsedTime;

    gettimeofday(&t1, NULL);
    srand(time(0));
    LIST myList = createList(1000000);
    myList = createCycle(myList);
    NODE hare, tort;
    hare = myList->first;
    tort = myList->first;
    while(!isAhead(tort,hare)) {
        tort = tort->next;
        hare = hare->next->next;
    }
    gettimeofday(&t2, NULL);

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("Total time is: %f ms. and heap is %lld", elapsedTime, heapSpace);
    // int k = isAhead(tort, hare);
    // printf("%d %d", tort->element, hare->element);
    // printf("%d", k);
    return 0;
}