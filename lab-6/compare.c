#include "element.h"
#include "recursiveMerge.h"
#include "iterativeMerge.h"
#include <time.h>
#include <sys/time.h>

int STACK_TOP;

int main() {
    struct timeval t1, t2;
	double elapsedTime;
    int fname = 1024;
    FILE * fptr;

    //Measures running time and space for Iterative MS.
    for(int j = 0; j < 2 ; j++){

        char* temp1 = malloc(sizeof(char)*100);
        sprintf(temp1, "input/%d.txt", fname);
        fptr = fopen(temp1,"r");

        if(fptr == NULL){
            printf("Error opening file\n");
            exit(1);
        }

        ELIST ls = (ELIST)malloc(sizeof(Element) * fname);

        ELIST temp = ls;

        int cnt = 0;

        while(fscanf(fptr, "%[^,], %f", temp->name, &temp->cgpa) > 1){
            //printf("%s, %0.2lf", temp->name, temp->cgpa);

            cnt++;
            temp++;
        }

        int ITER_STACK_BOTTOM;

        gettimeofday(&t1, NULL);
        iterativeMS(ls, cnt);
        gettimeofday(&t2, NULL);
        printf("Stack size for sorting %d elements using Iterative MS is %d\n", fname, (int)&ITER_STACK_BOTTOM - STACK_TOP);

        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        printf("Total time taken for sorting %d elements using Iterative MS is %f ms.\n", fname, elapsedTime);

        temp = ls;

        // Uncomment to check sorted list contents
        // int i = 0;
        // while (i < cnt)
        // {
        //     printf("%s, %0.2lf", temp->name, temp->cgpa);
        //     temp++;
        //     i++;

        // }
        fname*=10;
    }

    fname = 1024;
    printf("\n");

    //Measures running time and space for Recursive MS.
    for(int j = 0; j < 2 ; j++){

        char * temp1 = malloc(sizeof(char)*100);
        sprintf(temp1, "input/%d.txt", fname);
        fptr = fopen(temp1,"r");

        if(fptr == NULL){
            printf("Error opening file\n");
            exit(1);
        }

        ELIST ls = (ELIST)malloc(sizeof(Element) * fname);

        ELIST temp = ls;

        int cnt = 0;

        while(fscanf(fptr, "%[^,], %f", temp->name, &temp->cgpa) > 1){
            //printf("%s, %0.2lf", temp->name, temp->cgpa);

            cnt++;
            temp++;
        }

        int REC_STACK_BOTTOM;

        //RECURSIVE MERGE SORT
        gettimeofday(&t1, NULL);
        recursiveMS(ls, cnt);
        gettimeofday(&t2, NULL);
        printf("Stack size for sorting %d elements using Recursive MS is %d\n", fname, (int)&REC_STACK_BOTTOM - STACK_TOP);

        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        printf("Total time taken for sorting %d elements using Recursive MS is %f ms.\n", fname, elapsedTime);

        temp = ls;

        // Uncomment to check sorted list contents
        // int i = 0;
        // while (i < cnt)
        // {
        //     printf("%s, %0.2lf", temp->name, temp->cgpa);
        //     temp++;
        //     i++;

        // }
        fname*=10;
    }

    return 0;
}
