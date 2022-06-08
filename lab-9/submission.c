/*
Note: Recursive Merge Sort was used
OUTPUTS
For n = 10000,
        HEAP SORT       = 4.942 sec
        QUICK SORT      = 1.726 sec
        MERGE SORT      = 2.421 sec
        INSERTION SORT  = 77.901 sec
For n = 100000,
        HEAP SORT       = 37.145 sec
        QUICK SORT      = 16.076 sec
        MERGE SORT      = 22.89 sec
        INSERTION SORT  = 7929.471 sec
For n = 1000000,
        HEAP SORT       = 542.374 sec
        QUICK SORT      = 219.248 sec
        MERGE SORT      = 279.902 sec
        INSERTION SORT  = didn't complete
For n = 10000000,
        HEAP SORT       = 13005.444 sec
        QUICK SORT      = 5166.102 sec
        MERGE SORT      = 5370.120 sec
        INSERTION SORT  = didn't complete
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/time.h>

#define MIN(a, b) (((a)<(b))?(a):(b))

typedef struct {
    char name[11];
    int id;
} record;

typedef record* RECORD;

typedef struct {
    int lo;
    int hi;
} PAIR;

typedef struct {
	PAIR* array;
	int stack_top;
	int stack_size;
} STACK;

typedef struct {
    RECORD arr;
    int size;
    int maxCapacity;
} HEAP;

typedef enum Boolean{FALSE=0, TRUE}Boolean;


HEAP *initializeHeap(int size);
void exchange(record *A, record *B);
int parent(HEAP *h, int i);
int leftChild(HEAP *h, int i);
int rightChild(HEAP *h, int i);
int getHeapMaximum(HEAP *h);
int extractHeapMaximum(HEAP *h);
void HEAPIFY(HEAP *h, int i);
void buildMAXHEAP(HEAP *h, RECORD arr, int n);
HEAP *HEAPSORT(RECORD arr, int n);
void heapInsert(HEAP *h, int key);
HEAP *resize(HEAP *h);
void printHeapToFile(HEAP *h);
STACK* createEmptyStack();
Boolean isStackEmpty(STACK *st);
Boolean isStackFull(STACK *st);
STACK* pushToStack(STACK *st, PAIR p);
void popFromStack(STACK *st);
PAIR stackTop(STACK *st);
STACK *resizeStack(STACK *st);

RECORD insertRec(RECORD rec, char *fileName, int size);
void printList(RECORD head, int size);

int partition(RECORD arr, int l, int h);
void quickSort(RECORD arr, int s, int sublSize);
void insertionSort(RECORD arr, int sz);

void merge(record Ls1[], int sz1, record Ls2[], int sz2, record Ls[]);
void recursiveMS(record Ls[], int sz);


RECORD insertRec(RECORD rec, char* fileName, int size) {
    rec = (RECORD)malloc(sizeof(record)*size);

    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        printf("File not opening!\n");
        exit(0);
    }

    int i = 0;
    record temp;

    while(!feof(f)) {
        fscanf(f, "%11s %d\n", temp.name, &temp.id);
        rec[i++] = temp;
    }
    fclose(f);
    return rec;
}

void printList(RECORD head, int size) {
    while(size--) {
        printf("%11s %d\n", head->name, head->id);
        head++;
    }
}

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

int partition(RECORD arr, int l, int h) {
    int lf = l;
    int rt = h;
    record pivotEl = arr[lf];
    while(lf<rt) {
        while(arr[rt].id > pivotEl.id)
            rt--;        
        while(arr[lf].id <= pivotEl.id)
            lf++;
        if(lf<rt)
            exchange(&arr[lf], &arr[rt]);
    }
    exchange(&arr[l], &arr[rt]);
    return rt;
}

void quickSort(RECORD arr, int s, int sublSize) {
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

void insertionSort(RECORD arr, int sz) {
    int m, n;
    record k;
    for (m = 1; m < sz; m++) {
        k = arr[m];
        n = m - 1;
        while(n>=0 && arr[n].id > k.id) {
            arr[n + 1] = arr[n];
            n--;
        }
        arr[n + 1] = k;
    }
}

void merge(record Ls1[], int sz1, record Ls2[], int sz2, record Ls[]) {
    int iter1 = 0, iter2 = 0, iter3 = 0;
    while(iter1<sz1 && iter2<sz2) {
        if(Ls1[iter1].id <= Ls2[iter2].id) {
            Ls[iter3++] = Ls1[iter1++];
        } else {
            Ls[iter3++] = Ls2[iter2++];
        }
    }
    //transfer remaining elements from Ls1 to Ls
    while(iter1<sz1) {
        Ls[iter3++] = Ls1[iter1++];
    }
    //transfer remaining elements from Ls2 to Ls
    while(iter2<sz2) {
        Ls[iter3++] = Ls2[iter2++];
    }
}

void recursiveMS(record Ls[], int sz) {
    int mid = sz / 2;
    if(sz>1) {
        recursiveMS(Ls, mid);
        recursiveMS(&Ls[mid], mid + sz % 2);
    }
    RECORD sorted = (RECORD)malloc(sizeof(record) * sz);
    merge(Ls, mid, &Ls[mid], mid + sz % 2, sorted);
    //copy sorted array back into Ls
    for (int i = 0; i<sz; i++) {
        Ls[i] = sorted[i];
    }
    free(sorted);
}

HEAP* initializeHeap(int capacity) {
    HEAP *h = (HEAP *)malloc(sizeof(HEAP));
    h->size = 0;
    h->maxCapacity = capacity;
    h->arr = (RECORD)malloc(sizeof(record) * capacity);
    return h;
}

void exchange(record *A, record *B){
    record temp = *A;
    *A = *B;
    *B = temp;
}

int parent(HEAP* h, int i) {
    if(i>=h->maxCapacity || i<=0)
        return -1;
    return (i - 1) / 2;
}

int leftChild(HEAP* h, int i) {
    int lChild = 2 * i + 1;
    if(lChild>=h->size)
        return -1;
    return lChild;
}

int rightChild(HEAP* h, int i) {
    int rChild = 2 * i+2;
    if(rChild>=h->size)
        return -1;
    return rChild;
}

int getHeapMaximum(HEAP *h) {
    if(h->size==0)
        return -1;
    return h->arr[0].id;
}

int extractHeapMaximum(HEAP *h) {
    if(h->size<1)
        return -1;
    int max = h->arr[0].id;
    h->arr[0].id = h->arr[h->size - 1].id;
    strcpy(h->arr[0].name, h->arr[h->size - 1].name);
    h->size--;
    HEAPIFY(h, 0);
    return max;
}

void HEAPIFY(HEAP *h, int i) {
    int l = leftChild(h, i);
    int r = rightChild(h, i);
    int largest;
    if ((l != -1) && (h->arr[l].id > h->arr[i].id))
        largest = l;
    else
        largest = i;
    if ((r != -1) && (h->arr[r].id > h->arr[largest].id))
        largest = r;
    if(largest!=i) {
        exchange(&h->arr[i], &h->arr[largest]);
        HEAPIFY(h, largest);
    }
}

void buildMAXHEAP(HEAP *h, RECORD arr, int n) {
    if(h==NULL)
        return;
    while(n>h->maxCapacity) {
        resize(h);
    }
    for (int i = 0; i < n; i++) {
        h->arr[i].id = arr[i].id;
        strcpy(h->arr[i].name, arr[i].name);
    }
    h->size = n;
    for (int i = (n - 1) / 2; i >= 0; i--)
    {
        HEAPIFY(h, i);
    }
}

HEAP *HEAPSORT(RECORD arr, int n) {
    HEAP *h = initializeHeap(n);
    buildMAXHEAP(h, arr, n);
    for (int i = n - 1; i >= 0; i--) {
        exchange(&h->arr[0], &h->arr[h->size - 1]);
        h->size--;
        HEAPIFY(h, 0);
    }
    return h;
}

void heapInsert(HEAP *h, int key) {
    if(h->size == h->maxCapacity) {
        printf("Full!");
    }
    h->size++;
    int i = h->size-1;
    while(i>=0 && h->arr[(i-1)/2].id<key) {
        h->arr[i].id = h->arr[(i - 1) / 2].id;
        strcpy(h->arr[i].name, h->arr[(i - 1) / 2].name);
        i = (i - 1) / 2;
    }
    h->arr[i].id = key;
}

void freeHeap(HEAP *h){
  if(h==NULL)
    return;
  free(h->arr);
  free(h);
  h=NULL;
}

void printHeapToFile(HEAP *h) {
    char *output = "data_sorted_heap.txt";
    FILE *f = fopen(output, "w");
    for (int i = 0; i < h->maxCapacity; i++)
    {
        fprintf(f,"%s %d\n",  h->arr[i].name, h->arr[i].id);
    }
    printf("Heap sort printed to file\n");
    fclose(f);
}

HEAP *resize(HEAP *h) {
    RECORD temp = h->arr;
    h->maxCapacity *= 2;
    h->arr = (RECORD)malloc(sizeof(record) * h->maxCapacity);
    for (int i = 0; i < h->size; i++) {
        h->arr[i].id = temp[i].id;
        strcpy(h->arr[i].name, temp[i].name);
    }
    free(temp);
    return h;
}

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
    char *readRec = "input/data10000000";
    FILE *f = fopen(readRec, "r");
    int size = 10000000;
    compare_sort_algos(readRec, size);
    fclose(f);
}