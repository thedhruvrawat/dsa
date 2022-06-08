#include "dns.h"

NODE initializeDNSTree() {
	NODE root = malloc(sizeof(struct node));
	root->child = NULL;
	root->sibling = NULL;
	root->value = NULL;
	return root;
}

NODE insertNode(char** terms, char* ip, int k, NODE root) {
	NODE current = root->child;
	NODE prev = root->child;
	NODE levelcurrent,levelprev,temp;
    int level = 1;
    if (current == NULL) {
        for(int i=0;i<k;i++) {
            NODE newnode = (NODE)(malloc(sizeof(struct node)));
            newnode->value = terms[i];
            newnode->child = NULL;
            newnode->sibling = NULL;
            if(prev==NULL) {
                root->child = newnode;
                prev = root->child;
            }
            else prev->child = newnode;
            current = newnode;
            prev = current;
            current = current->child;		
        }
        NODE newnode = malloc(sizeof(struct node));
        newnode->value = (char*)(malloc(sizeof(char)*(1+strlen(ip))));
        newnode->value = ip;
        newnode->child = NULL;
        newnode->sibling = NULL;
        prev->child = newnode;
    }
    else {
        levelcurrent = current;
        levelprev = current;
	    while(k>=level) {
            while(levelcurrent!=NULL) {
                if (strcmp(levelcurrent->value, terms[level-1])!=0) {
                    levelprev = levelcurrent;
                    levelcurrent = levelcurrent->sibling;
                } else if (strcmp(levelcurrent->value, terms[level-1])==0) {
                    levelprev = levelcurrent;
                    prev = levelprev;
                    temp = levelcurrent->child;
                    levelcurrent = levelcurrent->child;
                    level++;
                    continue;
                }
            }
            if(levelcurrent==NULL) {
                NODE newnode =(NODE)(malloc(sizeof(struct node)));
                newnode->value = (char*)(malloc(sizeof(char)*(strlen(terms[level-1]+1))));
                newnode->child= NULL;
                newnode->sibling = NULL;
                strcpy(newnode->value,terms[level-1]);
                levelprev->sibling = newnode;
                levelcurrent = newnode;
                temp = levelcurrent;
                prev = temp;
                temp = temp->child;
                level++;
                while (temp == NULL && level <= k)
                {
                    NODE newnode = malloc(sizeof(struct node));
                    prev->child = newnode;
                    temp = newnode->child;
                    newnode->value = (char*)(malloc(sizeof(char)*(strlen(terms[level-1]+1))));
                    strcpy(newnode->value,terms[level-1]);
                    newnode->child =NULL;
                    newnode->sibling = NULL;
                    prev= newnode;
                    current = newnode->child;
                    level++;
                }
            }
	    }
        NODE newnode = malloc(sizeof(struct node));
        newnode->value = (char*)(malloc(sizeof(char)*(1+strlen(ip))));
        newnode->value =ip;
        newnode->child = NULL;
        newnode->sibling = NULL;
        prev->child = newnode;
    }
    return root;	
}

void findDNSAddress(char* name,NODE root) {
	int j=0;
	char** x;
	x = (char**)(malloc(sizeof(char*)*strlen(name)+1));
	for(int i=0;i<strlen(name);i++)	{
		x[i] = (char*)(malloc(sizeof(char)*100));
	}
	int n = strlen(name);
	int i = n-1;
	int k=0;
	while(i>=0)	{
		while(name[i]!= '.' && i>=0) {
            x[k][j] = name[i];
            i--;
            j++;
		}		
		if(name[i] == '.' || i==-1) {
			char tname[j];
			for(int l=0;l<j;l++) {
				tname[l] = x[k][l];
			}	
			for(int l=0;l<j;l++) {
				x[k][l]=tname[j-l-1];
			}			
			i--;
			k++;
			j=0;
		}
	}
	int level=1;
	NODE current = root->child;
	NODE levelcurrent;
	int flag = 0;
    char *temp;
    while (k >= level)
    {
        levelcurrent = current;
		while(levelcurrent)	{
			if(strcmp(levelcurrent->value, x[level-1])!=0 )	{
				levelcurrent = levelcurrent->sibling;
                current = levelcurrent;
            }
            else {
				current = current->child;
				levelcurrent = current;
                temp = current->value;
                level++;
            }
		}
        if(level>k) {
            printf("Found, IP = %s\n", temp);
            return;
        } else if(levelcurrent==NULL && k<=level) {
		    printf("Not Found\n");
            return;
        }
    }
}

NODE splitDNSAddress(char* name, char* ip, NODE root) {
	int j=0;
	char** terms;
	terms = (char**)(malloc(sizeof(char*)*strlen(name)+1));
	for(int i=0;i<strlen(name);i++)	{
		terms[i] = (char*)(malloc(sizeof(char)*100));
	}
	int n = strlen(name);
	int i = n-1;
	int k=0;
	while(i>=0)	{
		while(name[i]!= '.' && i>=0) {
            terms[k][j] = name[i];
            i--;
            j++;
		}		
		if(name[i] == '.' || i==-1) {
			char tname[j];
			for(int l=0;l<j;l++) {
				tname[l] = terms[k][l];
			}	
			for(int l=0;l<j;l++) {
				terms[k][l]=tname[j-l-1];
			}			
			i--;
			k++;
			j=0;
		}
	}
	root = insertNode(terms,ip,k,root);
	return root;
}

NODE readData(FILE* fptr,NODE root) {
	int n;
	fscanf(fptr,"%d\n",&n);
	char name[n][1000];
	char ip[n][1000];
	for(int i=0;i<n;i++) {
		fscanf(fptr,"%s %s\n",name[i],ip[i]);
		root = splitDNSAddress(name[i],ip[i],root);
	}
	return root;
}

void lookup(FILE* fp, NODE root) {
	char name[1000];
	fscanf(fp,"%s\n",name);
	printf("%s, ",name);
	findDNSAddress(name, root);
}

int main() {
	int x;
	FILE* fptr = fopen("input.txt","r");
	NODE root;
	while(!feof(fptr)) {
	    fscanf(fptr,"%d",&x);
	    if(x==1) { 
            root = initializeDNSTree();
            root = readData(fptr,root);
            NODE temp = root->child;
            while(temp) {
                temp = temp->sibling;
            }
	    } else if(x==2) {
    		lookup(fptr,root);
	    } else if(x==-1) return 0;
	}
}
