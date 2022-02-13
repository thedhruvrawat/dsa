#ifndef __MULTIQUEUE_H
#define __MULTIQUEUE_H

#include "que.h"

extern int MAX_PRIORITY;

typedef struct task* TASK;
typedef int PRIORITY;
typedef QUEUE* MultiQ;

struct task {
    int task_id;
    PRIORITY p;
};

MultiQ createMQ(int num);                       // creates a list of num Queues, each of which is empty.
MultiQ addMQ(MultiQ mq, TASK t);                // adds t to the Queue corresponding to priority p in mq. Task includes a TaskID tid and a priority p.
TASK nextMQ(MultiQ mq);                         // returns the front of the non-empty Queue in mq with the highest priority.
MultiQ delNextMQ(MultiQ mq);                    // deletes the front of the non-empty Queue in mq with the highest priority; returns the modified MultiQ
Boolean isEmptyMQ(MultiQ mq);                      // tests whether all the Queues in mq are empty
int sizeMQ(MultiQ mq);                          // returns the total number of items in the MultiQ
int sizeMQbyPriority(MultiQ mq, PRIORITY p);    // returns the number of items in mq with the priority p.
QUEUE getQueueFromMQ(MultiQ, PRIORITY p);       // returns the Queue with priority p.

#endif