#include "heap.h"
#include "mergeSort.h"
// #include "insertionSort.h"
#include "quickSort.h"
#include <math.h>
#include <sys/time.h>

void compare_sort_algos(char *filename, int size) {
    struct timeval t1, t2;
    double elapsedTime, time0, time1;
    FILE *f = fopen(filename, "r");
    if(f==NULL) {
        printf("No file received!!");
        exit(0);
    }
    //Create an array of records and insert records in it
    RECORD rec_array, isort, msort, qsort;
    rec_array = insertRec(rec_array, filename, size);
    msort = insertRec(msort, filename, size);
    isort = insertRec(isort, filename, size);
    qsort = insertRec(qsort, filename, size);

    gettimeofday(&t1,NULL);
    //HEAP SORT
    HEAP *h = HEAPSORT(rec_array, size);
    gettimeofday(&t2,NULL);
    printHeapToFile(h);

    elapsedTime = (t2.tv_sec - t1.tv_sec)*1000.0;
	elapsedTime += (t2.tv_usec-t1.tv_usec)/1000.0;
    printf("Heap Sort took %f sec.\n", elapsedTime);

    //QUICK SORT
    gettimeofday(&t1,NULL);
    quickSort(qsort, size, 0);
    gettimeofday(&t2,NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec)*1000.0;
	elapsedTime += (t2.tv_usec-t1.tv_usec)/1000.0;
    printf("Quick Sort took %f sec.\n", elapsedTime);
    
    //MERGE SORT
    gettimeofday(&t1,NULL);
    recursiveMS(msort, size);
    gettimeofday(&t2,NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec)*1000.0;
	elapsedTime += (t2.tv_usec-t1.tv_usec)/1000.0;
    printf("Merge Sort took %f sec.\n", elapsedTime);

    //INSERTION SORT
    gettimeofday(&t1,NULL);
    insertionSort(isort, size);
    gettimeofday(&t2,NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec)*1000.0;
	elapsedTime += (t2.tv_usec-t1.tv_usec)/1000.0;
    printf("Insertion Sort took %f sec.\n", elapsedTime);
}

int main() {
    char *readRec = "input/data1000000";
    FILE *f = fopen(readRec, "r");
    int size = 1000000;
    compare_sort_algos(readRec, size);
    // RECORD rec_array;
    // rec_array = insertRec(rec_array, readRec, size);
    // gettimeofday(&t2, NULL);
    // printList(rec_array, size);

    // HEAP *h = HEAPSORT(rec_array, size);
    // for(int i=0; i<100; i++) {
    //     printf("%d ", h->arr[i].id);
    // }
    // printHeap(h);
    // printf("Heap size: %d\n", h->size);
    // fprintf(f, "Read %d records.\n", size);
    fclose(f);
}