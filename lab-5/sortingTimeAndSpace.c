#include <sys/time.h>
#include "record.h"
#include "insertionSort.h"
#include <stdio.h>
#include <string.h>

long long int STACK_TOP;

int main() {
    char *readRec = "read.txt";
    char *sortSpace = "space.txt";
    char *sortTime = "time.txt";
    char input[18];
    const char check_str[11][9] = { "10", "100", "1000", "2500", "5000", "7500", "10000", "25000", "50000", "75000", "100000"};


   for (int i = 0; i < 11; i++) {
        strcpy(input, "generated/");
        strcat(input, check_str[i]);

        printf("Performing time and space measurements on input file %s...\n", input);
        FILE *fspace = fopen(sortSpace, "a");
        FILE *ftime = fopen(sortTime, "a");
        FILE *f = fopen(readRec, "a");
        int size;
        RECORD rec_array;

        struct timeval t1, t2;
        double elapsedTime;
        gettimeofday(&t1, NULL);
        rec_array = insertRec(rec_array, input, &size);
        gettimeofday(&t2, NULL);

        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
        
        fprintf(f, "Read %d records in %f ms.\n", size, elapsedTime);
        fclose(f);
        // printf("Initially\n");
        // RECORD a = rec_array;
        // printList(rec_array, size);
        long long int STACK_BOTTOM;
     //    RECORD a = rec_array;
        gettimeofday(&t1, NULL);
        rec_array = insertionSort(rec_array, size);
        gettimeofday(&t2, NULL);
        printf("Stack size is %d\n", (long long int)&STACK_BOTTOM - STACK_TOP);

        

        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

        printf("Total time taken is %f ms.\n", elapsedTime);

        fprintf(ftime, "Sorted %d records in %f ms.\n", size, elapsedTime);
        fprintf(fspace, "Sorted %d records taking %d space\n", size, (long long int)&STACK_BOTTOM - STACK_TOP);
        fclose(ftime);
        fclose(fspace);
        printf("--------------------------------------------------------------------------------\n");
        // printList(a, size);
   }
}