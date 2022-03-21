#include "quickSort.h"
#include <math.h>
#include <sys/time.h>

#define MAX_SZ 10000 //Set max number of records to be read here (for inputs 10^5, 10^6, 10^7)

void copyEMP_LIST(EMP_LIST Ls, EMP_LIST copy, int sz) {
    for(int i=0; i<sz; i++)
        copy[i] = Ls[i];
}

void testRun(EMP_LIST Ls, int sz, double tval[]) {
    struct timeval t1, t2;
    double elapsedTime, time0, time1;
    employee Ls1[sz], Ls2[sz];
    copyEMP_LIST(Ls, Ls1, sz);
    copyEMP_LIST(Ls, Ls2, sz);
    if(sz)
    {
        gettimeofday(&t1,NULL);
        quickSort(Ls1, sz, 0);
        gettimeofday(&t2,NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec)*1000.0;
	    elapsedTime += (t2.tv_usec-t1.tv_usec)/1000.0;
        time0 = elapsedTime;
        gettimeofday(&t1,NULL);
        insertionSort(Ls2, sz);
        gettimeofday(&t2,NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec)*1000.0;
	    elapsedTime += (t2.tv_usec-t1.tv_usec)/1000.0;
        time1 = elapsedTime;
        tval[1] = elapsedTime;
    }
    tval[0] = time0;
    tval[1] = time1;
}

int estimateCutoff(EMP_LIST Ls, int sz) {    
    int minimum = 0, maximum = sz, cutoff;
    int mid = minimum + (maximum - minimum) / 2;
    double tval[2];
    while(minimum<maximum) {
        mid = minimum + (maximum - minimum) / 2;
        testRun(Ls, mid, tval);
        if(tval[1]-tval[0]>0.0)
            minimum = mid + 1;
        else if(tval[1]-tval[0]<0.0)
            maximum = mid + 1;
        else
            return mid;    
    }
}

void printSortedList(EMP_LIST Ls, int size, FILE *f) {
    if(f==NULL)
        printf("ERR!\n");
    printf("------------------------------------------------------------------------------------\nSorting %d records\n", size);
    for (int i = 0; i<size; i++) {
        fprintf(f, "%s %ld\n", (Ls + i)->name, (Ls + i)->empID);
    }
}

int main(int argc, char *argv[]) {
    struct timeval t1, t2;
    gettimeofday(&t1,NULL);
    FILE* fread = fopen(argv[1],"r");
    FILE *fwrite = fopen(argv[2], "w");
    int sz = atoi(argv[3]);
    int n = MIN(MAX_SZ, sz);
    employee Ls[n];
    int i = 0;
    while(fscanf(fread,"%s %ld", Ls[i].name, &Ls[i].empID) != -1 && i<n) {
		i++;
	}
    n = i;
    int cutoff = estimateCutoff(Ls, n);
    gettimeofday(&t2, NULL);
    quickSort(Ls, n, 0);
    printSortedList(Ls, n, fwrite);
    double elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec-t1.tv_usec)/1000.0;
    printf("For %d records, elapsed time = %f, estimated cutoff = %d\n", n, elapsedTime, cutoff);
    fclose(fread);
}