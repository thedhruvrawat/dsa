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
    int low;
    int high;
} PAIR;

typedef struct {
	PAIR* array;
	int top;
	int size;
} STACK;

typedef enum Boolean{FALSE=0, TRUE}Boolean;

#define MIN(a, b) (((a)<(b))?(a):(b))

#define MAX_SZ 50000 //Set max number of records to be read here (for inputs 10^5, 10^6, 10^7)


STACK* createStack() {
    STACK *st = (STACK *)malloc(sizeof(STACK));
    st->size = 10;
    st->array = malloc(sizeof(PAIR) * st->size);
    st->top = -1;
    return st;
}

Boolean isEmpty(STACK* st) {
    return (st->top == -1);
}

Boolean isFull(STACK* st) {
    return (st->size - 1 == st->top);
}

void pop(STACK* st) {
    if(!isEmpty(st))
        st->top--;
    else
        printf("STACK UNDERFLOW!\n");
}

PAIR top(STACK* st) {
    PAIR temp;
    temp.low = -1;
    temp.high = -1;
    if(isEmpty(st))
        return temp;
    return st->array[st->top];
}

STACK* resize(STACK* st) {
    st->array = (PAIR *)(realloc((st->array), sizeof(PAIR) * st->size * 2));
    st->size *= 2;
    return st;
}


STACK* push(STACK* st, PAIR p) {
    if(isFull(st))
        resize(st);
    st->array[++st->top] = p;
    return st;
}

void swap(employee* a, employee* b) {
    employee temp = *a;
    *a = *b;
    *b = temp;
}

int partition(EMP_LIST arr, int l, int h) {
    employee pivot = arr[l];
    int left = l;
    int right = h;
    while(left<right) {
        while(arr[left].empID <= pivot.empID)
            left++;
        while(arr[right].empID > pivot.empID)
            right--;
        if(left<right)
            swap(&arr[left], &arr[right]);
    }
    swap(&arr[l], &arr[right]);
    return right;
}

void quickSort(EMP_LIST arr, int s, int threshold) {
    STACK *st = createStack();
    PAIR temp;
    temp.low = 0;
    temp.high = s-1;
    st = push(st, temp);
    while(!isEmpty(st)) {
        temp = top(st);
        pop(st);
        int high = temp.high;
        int low = temp.low;
        if(high-low+1<threshold)
            continue;
        int p = partition(arr, low, high);
        if(p-1>low) {
            temp.low = low;
            temp.high = p - 1;
            st = push(st, temp);
        }
        if(p+1<high) {
            temp.low = p + 1;
            temp.high = high;
            st = push(st, temp);
        }
    }
}

void insertionSort(EMP_LIST arr, int size) {
    int i = 0, j;
    for (int i = 1; i < size; i++) {
        j = i - 1;
        employee key = arr[i];
        while(j>=0 && arr[j].empID > key.empID) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void testRun(EMP_LIST Ls, int n, double tval[]) {
    struct timeval t1, t2, t3;
    double elapsedTime;
    employee Ls1[n], Ls2[n];
    for(int i=0; i<n; i++) {
        Ls1[i] = Ls[i];
        Ls2[i] = Ls[i];
    }
    if(n>0) {
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
            max = mid + 1;
        else
            return mid;    
    }
}

void printSortedList(EMP_LIST Ls, int size, FILE *f) {
    if(f==NULL)
        printf("ERR!\n");
    printf("-------------------------------------------\nSorting %d records\n", size);
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