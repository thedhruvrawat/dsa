#include <sys/time.h>
#include "record.h"
#include <stdio.h>

int main() {
    char* input = "input/10";

    int size;
    RECORD rec_array;

    struct timeval t1, t2;
	double elapsedTime;
	gettimeofday(&t1, NULL);
	rec_array = insertRec(rec_array, input, &size);
	gettimeofday(&t2, NULL);

	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

    printf("Read %d records in %f ms.\n", size, elapsedTime);
}