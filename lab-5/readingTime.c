#include <sys/time.h>
#include "record.h"
#include "insertionSort.h"
#include <stdio.h>
#include <string.h>

int read() {
    char *read = "time.txt";
    char input[18];
    const char check_str[11][9] = { "10", "100", "1000", "10000", "25000", "50000", "75000", "100000", "1000000", "2500000", "5000000"};


   for (int i = 0; i < 11; i++) {
        strcpy(input, "generated/");
        strcat(input, check_str[i]);

        printf("Performing time and space measurements on input file %s...\n", input);
        FILE *f = fopen(read, "a");
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
   }
}