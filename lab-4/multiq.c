#include "multiq.h"

MultiQ createMQ(int num) {
    MultiQ list = (MultiQ)malloc(sizeof(QUEUE) * (num+1));
    return list;
}

MultiQ addMQ(MultiQ mq, TASK t) {
    int id = t->task_id;
    PRIORITY p = t->p;
    QNODE temp = (QNODE)malloc(sizeof(struct queueNode));
    temp->element = id;
    temp->next = NULL;
    if(isEmptyQ((QUEUE)mq[p])) {
		QUEUE q = newQ();
		mq[p] = (QUEUE)q;
	}
    QUEUE q = addQ(mq[p], id);
	mq[p] = (QUEUE)q;
    return mq;
}

TASK nextMQ(MultiQ mq) {
    QNODE temp;
    TASK t;
    for (int i = 0; i < MAX_PRIORITY; i++) {
        if(!isEmptyQ(mq[i])){
			temp = ((QUEUE)&mq[i])->head;
			t->task_id = temp->element;
			t->p = i;
			return t;
		}
    }
    return t;
}

MultiQ delNextMQ(MultiQ mq) {
    for(int i = 0 ; i < MAX_PRIORITY ; i++){
		if(!isEmptyQ(mq[i])){
			mq[i] = delQ(mq[i]);
            return mq;
		}
	}
	return mq;
}

Boolean isEmptyMQ(MultiQ mq) {
    for (int i = 0; i < MAX_PRIORITY; i++) {
        if(!isEmptyQ(mq[i]))
            return FALSE;
    }
    return TRUE;
}

int sizeMQ(MultiQ mq) {
    int size = 0;
    for (int i = 0; i < MAX_PRIORITY; i++) {
        size += lengthQ(mq[i]);
    }
    return size;
}

int sizeMQbyPriority(MultiQ mq, PRIORITY p) {
    return lengthQ(mq[p]);
}

QUEUE getQueueFromMQ(MultiQ mq, PRIORITY p) {
    return mq[p];
}