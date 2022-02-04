// Hare and Tortoise Algorithm
#include "cycle.h"

int isAhead(NODE a, NODE b) {
    if(b==a && b!=NULL && a!=NULL)
        return 1;       //If a is ahead of b, return 1
    return 0;
}

int testCyclic(LIST Ls) {
    if(Ls->count < 2) return 0;	
	else if(Ls->count == 2) {
		NODE first = Ls->first;
		NODE second = first->next;
		if(second->next != first) return 0;
	} else {
        NODE hare, tort;
        hare = Ls->first;
        tort = Ls->first;
        while(hare!=tort || hare!=NULL) {
            if(tort->next == NULL || (hare->next == NULL) || (hare -> next) -> next == NULL) return 0;	
            tort = tort -> next;
            hare = (hare -> next) -> next;
            if(hare == tort && hare!=NULL && tort!=NULL) return 1;
        }
    }   
    return 0;
}