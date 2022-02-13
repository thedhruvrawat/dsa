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
    struct timeval t1, t2;
    double elapsedTime;
    MultiQ mqq = createMQ(MAX_PRIORITY);
    FILE *fileptr;
    if(argc == 2){
        gettimeofday(&t1, NULL);
        fileptr = fopen(argv[1], "r");
        mqq = loadData(fileptr);
        for (int i = 1; i<=MAX_PRIORITY; i++) {
            int len = sizeMQbyPriority(mqq, i);
            printf("Pri %d: %d\n", i, len);
        }
        // QUEUE test = getQueueFromMQ(mqq, 10);
        // printf("front is %d\n", front(test));
        int pp = sizeMQ(mqq);
        printf("Size is: %d\n", pp);

        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        printf("Total addition time is %f ms.\n", elapsedTime);

        int delNum = 10;

        gettimeofday(&t1, NULL);
        mqq = testDel(mqq, delNum);
        gettimeofday(&t2, NULL);

        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        printf("Average deletion time is %f ms.\n", elapsedTime/delNum);
    
    }

    return 0;
}