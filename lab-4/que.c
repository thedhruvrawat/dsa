#include "que.h"

QUEUE newQ() {
    QUEUE q = (QUEUE)malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

Boolean isEmptyQ(QUEUE q) {
    return q == NULL || q->head == NULL;
}

QUEUE delQ(QUEUE q) {
    QNODE temp;
	temp = q->head;
	q->head = temp->next;
	q->size--;
    return q;
}

Element front(QUEUE q) {
    return q->head->element;
}

QUEUE addQ(QUEUE q, Element e) {
    QNODE temp = (QNODE)malloc(sizeof(struct queueNode));
    temp->element = e;
    temp->next = NULL;
    if(isEmptyQ(q)) {
		q->head = temp;
		q->tail = temp;	
	} else {	
		QNODE last = q->tail;
		last->next = temp;		
		q->tail = temp;
	}
	q->size++;
	return q;
}

int lengthQ(QUEUE q) {
    return q?q->size:0;
}

// int main() {
//     QUEUE test = newQ();
//     test = addQ(test, 7);
//     test = addQ(test, 13);
//     test = addQ(test, 15);
//     test = addQ(test, 3);
//     test = addQ(test, 89);
//     printf("front is %d\n", lengthQ(test));
//     test = delQ(test);
//     printf("front is %d\n", lengthQ(test));
//     return 0;
// }