#include "quickSort.h"
#include <math.h>
#include <sys/time.h>

#define MAX_SZ 50000 //Set max number of records to be read here (for inputs 10^5, 10^6, 10^7)

void testRun(EMP_LIST Ls, int n, double tval[]) {
    struct timeval t1, t2, t3;
    double elapsedTime;
    employee Ls1[n], Ls2[n];
    for(int i=0; i<n; i++) {
        Ls1[i] = Ls[i];
        Ls2[i] = Ls[i];
    }
    if(n>0) {
        // printf("\t %d", n);
        gettimeofday(&t1,NULL);
        quickSort(Ls1, n, 0);
        gettimeofday(&t2,NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec)*1000.0;
	    elapsedTime += (t2.tv_usec-t1.tv_usec)/1000.0;
        tval[0] = elapsedTime;
        gettimeofday(&t2,NULL);
        insertionSort(Ls2, n);
        gettimeofday(&t3,NULL);
        elapsedTime = (t3.tv_sec - t2.tv_sec)*1000.0;
	    elapsedTime += (t3.tv_usec-t2.tv_usec)/1000.0;
        tval[1] = elapsedTime;
    }
}

int estimateCutoff(EMP_LIST Ls, int n) {
    double tval[2], time;
    employee temp[n];
    int min = 0, max = n, cutoff;
    int mid = min + (max - min) / 2;
    while(min<max) {
        mid = min + (max - min) / 2;
        testRun(Ls, mid, tval);
        if(tval[1]-tval[0]>0.0)
            min = mid + 1;
        else if(tval[1]-tval[0]<0.0)
            max = mid - 1;
        else
            return mid;    
    }
}

void printSortedList(EMP_LIST Ls, int size, FILE *f) {
    // printf("%s\n", output);
    // FILE *f = fopen(output, "w");
    if(f==NULL)
        printf("ERR!\n");
    printf("Sorting %d records\n", size);
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
    // printf("n is %d\n", n);
    employee Ls[n];
    int i = 0;
    while(fscanf(fread,"%s %ld", Ls[i].name, &Ls[i].empID) != -1 && i<n) {
		// printf("%s %ld\n", Ls[i].name, Ls[i].empID);
		i++;
	}
    n = i;
    // printf("now n is %d\n", n);
    int cutoff = estimateCutoff(Ls, n);
    gettimeofday(&t2, NULL);
    quickSort(Ls, n, 0);
    printSortedList(Ls, n, fwrite);
    double elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec-t1.tv_usec)/1000.0;
    printf("For %d records, elapsed Time = %f, estimated cutoff = %d\n", n, elapsedTime, cutoff);
	// printf("cutoff = %d\n", cutoff);
    fclose(fread);
}