/* linkedlist.c */
#include "linkedlist.h"
#include <stdlib.h>

void insertFirst(struct linkedList *head, int ele) {
    //create a node
    struct node *link = (struct node*)malloc(sizeof(struct node)); /* by this
    you are creating a node whose address is being stored in the link pointer. */
    link->element = ele;
    //point it to old first node
    link->next = head->first;
    //point first to new first node
    head->first = link;
    head->count++;
}

//delete first item
struct node* deleteFirst(struct linkedList * head){
    // exercise to implement this operation.
    struct node *temp = head->first;
    head->first = temp->next;
    head->count--;
    return temp;
}

//display the list
void printList(struct linkedList *head) {
    struct node *ptr = head->first;
    printf("\n[ ");
    //start from the beginning
    while(ptr != NULL){
        printf(" %d ", ptr->element);
        if(ptr->next != NULL)
            printf("->");
        ptr = ptr->next;
    }
    printf("]");
}

//search element
int search (struct linkedList * head, int ele) {
    struct node *temp = head->first;
    while(temp!=NULL) {
        if(temp->element == ele)
            return 1;
        temp = temp->next;
    }
    return 0;
}

struct node *delete (struct linkedList * head, int ele) {
    if(search(head, ele)) {
        struct node *temp = head->first;
        struct node *prev = head->first;
        while(temp!=NULL) {
            temp = temp->next;
            if(temp->element == ele) {
                prev->next = temp->next;
                return temp;
            }
            prev = prev->next;
        }
        head->count--;
    } else {
        printf("\nElement not found\n");
    }
}