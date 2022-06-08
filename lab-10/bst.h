#ifndef __BST_H
#define __BST_H

#include<stdio.h>
#include<stdlib.h>

typedef struct bstNode* BSTNODE;

typedef struct bstNode {
    int val;
    BSTNODE leftSubtree;
    BSTNODE rightSubtree;
    int height;
    BSTNODE parent;
};

typedef struct root {
    BSTNODE bstRoot;
} root, *bstRootPtr;

#endif