// Hare and Tortoise Algorithm
#include "cycle.h"

LIST reverseList(LIST Ls) {
    NODE prev = Ls->first;
    NODE curr = prev->next;
    NODE nxt = curr->next;
    prev->next = NULL;
    while (nxt != NULL) {
        curr->next = prev;
        prev = curr;
        curr = nxt;
        nxt = nxt->next;
        Ls->first = prev;
    }
    curr->next = prev;
    Ls->first = curr;
    return Ls;
}

int testCyclic(LIST Ls){
    int flag  = 0;
	if(Ls->count < 2) return 0;	
	else if(Ls->count == 2){
		NODE first = Ls->first;
		NODE second = first->next;
		if(second->next != first) return 0;
        else return 1;
	} else {
        NODE temp = Ls->first;
        Ls = reverseList(Ls);
        if(temp == Ls->first) flag = 1;
        Ls = reverseList(Ls);
    }
    if(flag == 1) return 1;
	return 0;
}


