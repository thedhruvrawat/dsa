#include<stdio.h>
#include<stdlib.h>

typedef struct bstNode* BSTNODE;

struct bstNode {
    int value;
    BSTNODE leftChild;
    BSTNODE rightChild;
    int balanceFactor;
};

int height(BSTNODE root) {
    if(root==NULL)
         return 0;
    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);
    if(leftHeight>rightHeight)
        return leftHeight+1;
    else
        return rightHeight+1;    
}

BSTNODE inorderSuccessor(BSTNODE root) {  
    BSTNODE temp = root->rightChild;
    while(temp->leftChild!=NULL)
        temp = temp->leftChild;
    return temp;
}

BSTNODE rotate(BSTNODE x, BSTNODE y, BSTNODE z) {
    BSTNODE a = x;
    BSTNODE b = y;
    BSTNODE c = z;
    BSTNODE t0 = a->leftChild;
    BSTNODE t1;
    BSTNODE t2;
    BSTNODE t3;
    if(a->rightChild!=b && a->rightChild!=c) t1 = a->rightChild;
    else t1 = b->leftChild;
    if(b->rightChild!=c && b->rightChild!=a) t2 = b->rightChild;
    else t2 = c->leftChild;
    t3 = c->rightChild;
    b->leftChild = a;
    b->rightChild = c;
    a->leftChild = t0;
    a->rightChild = t1;
    c->leftChild = t2;
    c->rightChild = t3;
    a->balanceFactor = height(a->rightChild) - height(a->leftChild);
    b->balanceFactor = height(b->rightChild) - height(b->leftChild);
    c->balanceFactor = height(c->rightChild) - height(c->leftChild);
    return b;
}

BSTNODE add(BSTNODE root, int value) {
    if(root== NULL) {
        BSTNODE n = (BSTNODE)malloc(sizeof(struct bstNode));
        n->value = value;
        n->leftChild = NULL;
        n->rightChild = NULL;
        n->balanceFactor = 0;
        return n;
    }
    if (value<root->value) root->leftChild = add(root->leftChild,value);
    else if(value>root->value) root->rightChild = add(root->rightChild,value);
    else return root;                                                              
    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);
    root->balanceFactor = rightHeight-leftHeight;
	if(root->balanceFactor < -1  && value < root->leftChild->value) return rotate(root->leftChild->leftChild, root->leftChild, root);
	else if(root->balanceFactor > 1 && value > root->rightChild->value) return rotate(root, root->rightChild, root->rightChild->rightChild);
	else if(root->balanceFactor < -1 && value > root->leftChild->value) return rotate(root->leftChild,root->leftChild->rightChild,root);
	else if(root->balanceFactor >1 && value < root->rightChild->value) return rotate(root,root->rightChild->leftChild,root->rightChild);
    return root;
 }



BSTNODE find(BSTNODE root, int value) {
    if(root==NULL||value==root->value) return root;
    if(value<root->value) return find(root->leftChild,value);
    else return find(root->rightChild,value);
}

BSTNODE delete(BSTNODE root, int value){
    if(root==NULL) return root;
    if(value<root->value) root->leftChild = delete(root->leftChild,value);
    else if(value>root->value) root->rightChild = delete(root->rightChild,value);
    else {
        if(root->leftChild==NULL && root->rightChild == NULL) {
            BSTNODE temp = root;
            root = NULL;
            free(temp);
        } else if(root->leftChild==NULL) {
            BSTNODE temp = root->rightChild;
            *root = *temp;
            free(temp);
        } else if(root->rightChild == NULL) {
            BSTNODE temp = root->leftChild;
            *root = *temp;
            free(temp);
        } else {    
            BSTNODE temp = inorderSuccessor(root);                              
            root->value = temp->value;
            root->rightChild = delete(root->rightChild,temp->value);
        }
    }
    if(root ==NULL) return root;
    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);
    root->balanceFactor = rightHeight - leftHeight;    
    if(root->balanceFactor <-1  && value < root->leftChild->value)
        return rotate(root->leftChild->leftChild, root->leftChild, root);
	else if(root->balanceFactor > 1 && value > root->rightChild->value)
        return rotate(root, root->rightChild, root->rightChild->rightChild);
	else if(root->balanceFactor < -1 && value > root->leftChild->value) 
		return rotate(root->leftChild,root->leftChild->rightChild,root);
	else if(root->balanceFactor >1 && value < root->rightChild->value)
		return rotate(root,root->rightChild->leftChild,root->rightChild);
    return root;
}

void printInorder(BSTNODE root)
{
    if(root!=NULL) // checking if the root is not null
    {
        printInorder(root->leftChild); // visiting left child
        printf("%d ", root->value); // printing value at root
        printInorder(root->rightChild);// visiting right child
        
    }
}

int main() {
    BSTNODE root = NULL;
	root = add(root, 12);
	root = add(root, 52);
	root = add(root, 18);
	root = add(root, 64);
    root = add(root, 83);
    root = add(root, 71);
	root = add(root, 48);
    root = add(root, 6);
    root = add(root, 27);
    root = add(root, 33);
	root = add(root, 95);
    root = add(root, 65);
    printf("After addition: ");
    printInorder(root);
    printf("\n");
    root = delete(root,64);
    root = delete(root,6);
    printf("After deletion: ");
    printInorder(root);
    printf("\n");
    return 0;
}