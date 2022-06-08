#ifndef __DNS_H
#define __DNS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* NODE;

typedef struct node {
	char* value;
	NODE child, sibling;
};

NODE initializeDNSTree();
NODE insertNode(char **name, char* ip, int k, NODE root);
NODE splitDNSAddress(char *name, char *ip, NODE root);
void findDNSAddress(char *name, NODE root);
NODE readData(FILE *fptr, NODE root);
void search_tree(NODE root, char* name);
void lookup(FILE* fp,NODE root);

#endif