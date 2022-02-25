#include "element.h"
#include "recursiveMerge.h"

int STACK_TOP;

int main() {
    FILE *f = fopen("input/1024.txt", "r");

    if(f == NULL){
        printf("Couldn't open file");
        exit(1);
    }

    ELIST Ls = (ELIST)malloc(sizeof(Element)*1024);

    ELIST temp = Ls;

    int id_count = 0;

    while(fscanf(f, "%[^,], %lf", temp->name, &temp->cgpa) > 1){
        //printf("%s, %0.2lf", temp->name, temp->cgpa);
        id_count++;
        temp++;
    }

    recursiveMS(Ls, id_count);
    temp = Ls;

    int i = 0;
    while (i < id_count) {
        printf("%s, %0.2lf\n", temp->name, temp->cgpa);
        temp++;
        i++;
    }
    return 0;
}