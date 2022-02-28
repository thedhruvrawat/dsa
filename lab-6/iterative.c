#include "element.h"
#include "iterativeMerge.h"

int STACK_TOP;

int main() {
    FILE *f = fopen("input/1024.txt", "r");

    if(f == NULL){
        printf("Couldn't open file");
        exit(1);
    }

    ELIST Ls = (ELIST)malloc(sizeof(Element)*1024);

    ELIST temp = Ls;

    int cnt = 0;

    while(fscanf(f, "%[^,], %f", temp->name, &temp->cgpa) > 1){
        //printf("%s, %0.2lf", temp->name, temp->cgpa);
        cnt++;
        temp++;
    }

    iterativeMS(Ls, cnt);
    temp = Ls;

    int i = 0;
    while (i < cnt) {
        printf("%s, %0.2lf", temp->name, temp->cgpa);
        temp++;
        i++;
    }
    return 0;
}