#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (((a)>(b))?(a):(b))

typedef struct bstNode* BSTNODE;

struct bstNode {
    int value; //node will store an integer
    BSTNODE rightST; // right child
    BSTNODE leftST; // left child
    int height;
};

void updateHeight(BSTNODE root, BSTNODE temp);
BSTNODE find(BSTNODE root, int x);
BSTNODE findMinimum(BSTNODE root);
BSTNODE blankNode(int x);
BSTNODE add(BSTNODE root, int x);
BSTNODE delete (BSTNODE root, int x);
BSTNODE parent(BSTNODE tree, int nodeValue);
int getBalance(BSTNODE x);

void updateHeight(BSTNODE root, BSTNODE temp) {
    while(temp!=root) {
        temp->height = getBalance(temp);
        temp = parent(root, temp->value);
    }
    root->height = getBalance(root);
}

BSTNODE find(BSTNODE root, int x) {
    if(root==NULL || root->value==x) //if root->value is x then the element is found
        return root;
    else if(x>root->value) // x is greater, so we will search the right subtree
        return find(root->rightST, x);
    else //x is smaller than the value, so we will search the left subtree
        return find(root->leftST,x);
}

//function to find the minimum value in a node
BSTNODE findMinimum(BSTNODE root)
{
    if(root == NULL)
        return NULL;
    else if(root->leftST != NULL) // node with minimum value will have no left child
        return findMinimum(root->leftST); // left most element will be minimum
    return root;
}

//function to create a node
BSTNODE blankNode(int x) {
    BSTNODE p;
    p = malloc(sizeof(struct bstNode));
    p->value = x;
    p->leftST = NULL;
    p->rightST = NULL;

    return p;
}

BSTNODE add(BSTNODE root, int x) {
    //searching for the place to add
    if(root==NULL)
        return blankNode(x);
    else if(x>root->value) // x is greater. Should be added to right
        root->rightST = add(root->rightST, x);
    else // x is smaller should be added to left
        root->leftST = add(root->leftST,x);
    return root;
}

int height(BSTNODE x) {
	if(x==NULL)
		return 0;
	return x->height;
}

BSTNODE immediate_predecessor(BSTNODE x) {
	while(x->rightST!=NULL) {
		x = x->rightST;
	}
	return x;
}

// funnction to delete a node
BSTNODE delete(BSTNODE root, int x) {
    //searching for the item to be deleted
    if(root==NULL)
        return NULL;
    if (x>root->value)
        root->rightST = delete(root->rightST, x);
    else if(x<root->value)
        root->leftST = delete(root->leftST, x);
    else
    {
        //No Children
        if(root->leftST==NULL && root->rightST==NULL)
        {
            free(root);
            return NULL;
        }

        //One Child
        else if(root->leftST==NULL || root->rightST==NULL)
        {
            BSTNODE temp;
            if(root->leftST==NULL)
                temp = root->rightST;
            else
                temp = root->leftST;
            free(root);
            return temp;
        }

        //Two Children
        else
        {
            BSTNODE temp = findMinimum(root->rightST);
            root->value = temp->value;
            root->rightST = delete(root->rightST, temp->value);
        }
    }
    return root;
}

BSTNODE parent(BSTNODE tree, int nodeValue) {
	
//	printf("parent of node with value : %d is demanded\n",nodeValue);
	
	if((!find(tree,nodeValue)) || tree->value == nodeValue){	//if this node doesn't exist in
//		printf("shshshsh %d\n",tree->value);									//tree or is root, parent doesn't exists
		return NULL;
	}
	if((tree->leftST && tree->leftST->value == nodeValue) || (tree->rightST && tree->rightST->value == nodeValue))
		return tree;
	
	if(tree->value > nodeValue)
		return parent(tree->leftST,nodeValue);
	
	else
		return parent(tree->rightST,nodeValue);
	
}

void inorder(BSTNODE root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->leftST); // visiting left child
        printf(" %d ", root->value); // printing value at root
        inorder(root->rightST);// visiting right child
    }
}

BSTNODE rotateRight(BSTNODE y) {
  BSTNODE x = y->leftST;
  BSTNODE T2 = x->rightST;
  x->rightST = y;
  y->leftST = T2;
  y->height = MAX(height(y->leftST), height(y->rightST)) + 1;
  x->height = MAX(height(x->leftST), height(x->rightST)) + 1;
  return x;
}

BSTNODE rotateLeft(BSTNODE x) {
	BSTNODE y = x->rightST;
	// BSTNODE t1 = x->leftST;
	BSTNODE t2 = y->leftST;
	// BSTNODE t3 = y->rightST;
	// BSTNODE temp = t2;
	y->leftST = x;
	x->rightST = t2;
    y->height = MAX(height(y->leftST), height(y->rightST)) + 1;
    x->height = MAX(height(x->leftST), height(x->rightST)) + 1;
	return y;
}

int getBalance(BSTNODE x) {
	if(!x)
		return 0;	
	return (height(x->leftST))-(height(x->rightST));	
} 

BSTNODE addAVL(BSTNODE root, int x)
{
	if(root == NULL) {
        root = blankNode(x);
        root->height = 1;
        return root;
	} 
    
	if(x < root->value) {
            // root->height++;
            BSTNODE temp = addAVL(root->leftST, x);
            root->leftST = temp;
            // updateHeight(root, temp);
            // return root;
    } else if(x > root->value) {
            // root->height++;
            BSTNODE temp = addAVL(root->rightST, x);
            root->rightST = temp;
            // updateHeight(root, temp);
            // return root;
    } else
        return root;
    root->height = 1 + MAX(root->leftST->height, root->rightST->height);
    int balance = getBalance(root);
    if (balance > 1 && x < root->leftST->value)
        return rotateRight(root);

    if (balance < -1 && x > root->rightST->value)
        return rotateLeft(root);

    if (balance > 1 && x > root->leftST->value) {
        root->leftST = rotateLeft(root->leftST);
        return rotateRight(root);
    }

    if (balance < -1 && x < root->rightST->value) {
        root->rightST = rotateRight(root->rightST);
        return rotateLeft(root);
    }

    
}

// BSTNODE add(BSTNODE root, int x) {
//     //searching for the place to add
//     if(root==NULL)
//         return blankNode(x);
//     else if(x>root->value) // x is greater. Should be added to right
//         root->rightST = add(root->rightST, x);
//     else // x is smaller should be added to left
//         root->leftST = add(root->leftST,x);
//     return root;
// }

BSTNODE deleteAVL(BSTNODE x, int val) 
{
	if(x == NULL)
		return NULL;
    if(x && x->value == val){
		free(x);
		return NULL;
	}
	if(val< x->value) {
	    x->leftST= deleteAVL(x->leftST,val);
	} else if(val > x->value) {
	 	x->rightST = deleteAVL(x->rightST,val);
	} else {
        if(x->leftST==NULL && x->rightST == NULL) {
            BSTNODE temp = x;
            x = NULL;
            free(temp);
        } else if(x->rightST == NULL) {
            BSTNODE temp = x->leftST;
            *x = *temp;//copy contents
            free(temp);			
		} else if(x->leftST == NULL) {
            BSTNODE temp = x->rightST;
            *x = *temp;
            free(temp);
		} else { //node has two children
            BSTNODE temp = immediate_predecessor(x->leftST);
            x->value = temp->value;
            x->leftST = deleteAVL(x->rightST,temp->value);
		}
	}
	//height update
	x->height = MAX(height(x->leftST),height(x->rightST))+1;
	//Calculate balance factor
	int bal = getBalance(x);
	// Multiple cases 
	// Left left
	if(bal>1 && getBalance(x->leftST) >=0) {
		return rotateRight(x);
	}
	//left right case
	else if(bal>1 && getBalance(x->leftST)<0) {
		x->leftST = rotateLeft(x->leftST);
		return rotateRight(x);
	}
	//right left case
	else if(bal<-1 && getBalance(x->rightST)>0) {
		x->rightST = rotateRight(x->rightST);
		return rotateLeft(x);	
	}
	//right right
	else if(bal<-1 && getBalance(x->rightST)<=0) {
		return rotateLeft(x);
	}
}



int main()
{
    /*
                   20
                 /    \
                /      \
               5       30
             /   \     /\
            /     \   /  \
           1      15 25  40
                /          \
               /            \
              9             45
            /   \          /
           /     \        /
          7      12      42
    */
    BSTNODE root;
    root = blankNode(20);
    addAVL(root,5);
    addAVL(root,1);
    addAVL(root,15);
    addAVL(root,9);
    addAVL(root,7);
    addAVL(root,12);
    addAVL(root,30);
    addAVL(root,25);
    addAVL(root,40);
    addAVL(root, 45);
    addAVL(root, 42);
    // add(root,5);
    // add(root,1);
    // add(root,15);
    // add(root,9);
    // add(root,7);
    // add(root,12);
    // add(root,30);
    // add(root,25);
    // add(root,40);
    // add(root, 45);
    // add(root, 42);

    inorder(root);
    printf("\n");

    root = delete(root, 1);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25   40
                /           \
               /             \
              9              45
            /   \           /
           /     \         /
          7      12       42
    */

    root = deleteAVL(root, 40);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  45
                 /       / 
                /       /   
               9       42    
             /   \          
            /     \        
           7      12      
    */

    root = deleteAVL(root, 45);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  42
                 /          
                /            
               9            
             /   \          
            /     \        
           7      12      
    */
    root = deleteAVL(root, 9);
    inorder(root);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  42
                 /          
                /            
               12            
             /             
            /             
           7            
    */
    printf("\n");

    return 0;
}