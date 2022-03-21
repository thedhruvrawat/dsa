#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

typedef struct {
    char name[11];
    long int empID;
} employee;

typedef employee* EMP_LIST;

typedef struct {
    int lo;
    int hi;
} PAIR;

typedef struct {
	PAIR* array;
	int stack_top;
	int stack_size;
} STACK;

typedef enum Boolean{FALSE=0, TRUE}Boolean;

#define MIN(a, b) (((a)<(b))?(a):(b))

#define MAX_SZ 50000 //Set maximum number of records to be read here (for inputs 10^5, 10^6, 10^7)


STACK* createEmptyStack() {
    STACK *st = (STACK *)malloc(sizeof(STACK));
    st->stack_size = 10;
    st->array = malloc(sizeof(PAIR) * st->stack_size);
    st->stack_top = -1;
    return st;
}

Boolean isStackEmpty(STACK* st) {
    return (st->stack_top == -1);
}

Boolean isStackFull(STACK* st) {
    return (st->stack_size - 1 == st->stack_top);
}

void popFromStack(STACK* st) {
    if(!isStackEmpty(st))
        st->stack_top--;
    else
        printf("STACK UNDERFLOW!\n");
}

PAIR stackTop(STACK* st) {
    PAIR temp;    
    if(isStackEmpty(st)) {
        temp.lo = -1, temp.hi = -1;
        return temp;
    }
    return st->array[st->stack_top];
}

STACK* resizeStack(STACK* st) {
    st->stack_size *= 2;
    st->array = (PAIR *)(realloc((st->array), sizeof(PAIR) * st->stack_size * 2));
    return st;
}


STACK* pushToStack(STACK* st, PAIR p) {
    if(isStackFull(st))
        resizeStack(st);
    st->array[++st->stack_top] = p;
    return st;
}

void swap(employee* a, employee* b) {
    employee temp = *a;
    *a = *b;
    *b = temp;
}

int partition(EMP_LIST arr, int l, int h) {
    int lf = l;
    int rt = h;
    employee pivotEl = arr[lf];
    while(lf<rt) {
        while(arr[rt].empID > pivotEl.empID)
            rt--;        
        while(arr[lf].empID <= pivotEl.empID)
            lf++;
        if(lf<rt)
            swap(&arr[lf], &arr[rt]);
    }
    swap(&arr[l], &arr[rt]);
    return rt;
}

void quickSort(EMP_LIST arr, int s, int sublSize) {
    // printf("QUICK SORT\n");
    PAIR temp;
    temp.lo = 0, temp.hi = s-1;
    STACK *st = createEmptyStack();
    st = pushToStack(st, temp);
    while(!isStackEmpty(st)) {
        temp = stackTop(st);
        int h = temp.hi, l = temp.lo;
        if(h-l+1<sublSize)
            continue;
        int p = partition(arr, l, h);
        popFromStack(st);
        if(p+1<h) {
            temp.lo = p + 1, temp.hi = h;
            st = pushToStack(st, temp);
        }
        if(p-1>l) {
            temp.lo = l, temp.hi = p - 1;
            st = pushToStack(st, temp);
        }
    }
}

void insertionSort(EMP_LIST arr, int sz) {
    // printf("INSERTION SORT\n");
    int m, n;
    employee k;
    for (m = 1; m < sz; m++) {
        k = arr[m];
        n = m - 1;
        while(n>=0 && arr[n].empID > k.empID) {
            arr[n + 1] = arr[n];
            n--;
        }
        arr[n + 1] = k;
    }
}

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