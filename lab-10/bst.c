#include "bst.h"

BSTNODE bstFind(BSTNODE x, int k) {
    if(x==NULL || x->val==k) {
        return x;
    }
    if(k<x->val) {
        return bstFind(x->leftSubtree, k);
    } else
        return bstFind(x->rightSubtree, k);
}

BSTNODE bstAdd(BSTNODE root, int x) {
    if(root==NULL) {
        root->val = x;
    } else {
        if(x<=root->val)
            root->leftSubtree = bstAdd(root->leftSubtree, x);
        else
            root->rightSubtree = bstAdd(root->rightSubtree, x);
    }
    return root;
}

BSTNODE bstMin(BSTNODE root) {
    if(root==NULL)
        return root;
    while (root->leftSubtree != NULL)
        root = root->leftSubtree;
    return root;
}

BSTNODE bstMax(BSTNODE root) {
    if(root==NULL)
        return root;
    while(root->rightSubtree!=NULL)
        root = root->rightSubtree;
    return root;
}

BSTNODE bstSuccessor(BSTNODE x) {
    if(x==NULL)
        return x;
    if(x->rightSubtree!=NULL)
        return bstMin(x->rightSubtree);
    BSTNODE y = x->parent;
    while(y!=NULL && x==y->rightSubtree) {
        x = y;
        y = y->parent;
    }
    return y;
}

BSTNODE bstPredecessor(BSTNODE x) {
    if(x==NULL)
        return x;
    if(x->leftSubtree!=NULL)
        return bstMax(x->leftSubtree);
    BSTNODE y = x->parent;
    while(y!=NULL && x==y->leftSubtree) {
        x = y;
        y = y->parent;
    }
    return y;
}

void bstInsert(bstRootPtr root, int key) {
    BSTNODE z = (BSTNODE)malloc(sizeof(struct bstNode));
    z->val = key;
    z->leftSubtree = NULL;
    z->rightSubtree = NULL;
    if(root==NULL) {
        root = z;
        return root;
    }
    BSTNODE y = NULL;
    BSTNODE x = root->bstRoot;
    while(x!=NULL) {
        y = x;
        if(z->val<x->val)
            x = x->leftSubtree;
        else
            x = x->rightSubtree;
    }
    z->parent = NULL;
    if(y==NULL) {
        root->bstRoot = z;
    } else if(z->val<y->val) {
        y->leftSubtree = z;
    } else {
        y->rightSubtree = z;
    }
}


