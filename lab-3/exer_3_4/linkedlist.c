/* linkedlist.c */
#include "linkedlist.h"

LIST createEmptyList() {
    LIST list;    
    list = (LIST)myalloc(sizeof(*list));
    list->count=0;
	list->first = NULL;
	return list;
}

void insertFirst(LIST head, int ele) {
    NODE link;
    link = (NODE)myalloc(sizeof(*link));
    link->element = ele;
    link->next = head->first;
    head->first = link;
    head->count++;
}

NODE deleteFirst(LIST head){
    NODE temp = head->first;
    head->first = temp->next;
    head->count--;
    return temp;
}

void printList(LIST head) {
    NODE ptr = head->first;
    printf("\n[ ");
    while(ptr != NULL){
        printf(" %d ", ptr->element);
        if(ptr->next != NULL)
            printf("->");
        ptr = ptr->next;
    }
    printf("]");
}

