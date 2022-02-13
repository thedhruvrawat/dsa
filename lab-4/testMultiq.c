#include "multiq.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

int MAX_PRIORITY = 10;

// MultiQ mq;

MultiQ loadData(FILE *f) {
    MultiQ mq = createMQ(MAX_PRIORITY);
    if(mq==NULL){
        printf("Error");
    }
	while(!feof(f)) {
        int task_id=0,p=0;
        fscanf(f, "%d,%d", &task_id, &p);
        TASK t;
        t->task_id = task_id;
        t->p = p;        
        mq = addMQ(mq,t);
	}
    return mq;
}

MultiQ testDel(MultiQ mq, int num) {
    while(num--) {
        mq = delNextMQ(mq);
    }
    return mq;
}

int main(int argc, char *argv[]){
    printf("--------------------------------------------------------\n");
    struct timeval t1, t2;
    double elapsedTime;
    MultiQ myMQ = createMQ(MAX_PRIORITY);
    FILE *fileptr;
    if(argc == 2){
        printf("Input file: %s\n", argv[1]);
        gettimeofday(&t1, NULL);
        fileptr = fopen(argv[1], "r");
        myMQ = loadData(fileptr);
        // for (int i = 1; i<=MAX_PRIORITY; i++) {
        //     int len = sizeMQbyPriority(myMQ, i);
        //     printf("Pri %d: %d\n", i, len);
        // }
        // QUEUE test = getQueueFromMQ(myMQ, 10);
        // printf("front is %d\n", front(test));
        // int pp = sizeMQ(myMQ);
        // printf("Size is: %d\n", pp);

        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        printf("Total addition time is %f ms.\n", elapsedTime);

        int delNum = 6;

        gettimeofday(&t1, NULL);
        myMQ = testDel(myMQ, delNum);
        gettimeofday(&t2, NULL);
        // for (int i = 1; i<=MAX_PRIORITY; i++) {
        //     int len = sizeMQbyPriority(myMQ, i);
        //     printf("Pri %d: %d\n", i, len);
        // }
        // pp = sizeMQ(myMQ);
        // printf("Size is: %d\n", pp);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        printf("Average deletion time is %f ms.\n", elapsedTime/delNum);
        
    
    }

    return 0;
}