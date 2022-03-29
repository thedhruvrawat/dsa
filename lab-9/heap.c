#include "heap.h"

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
    // printf("New iter\n");
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("%d ", h->arr[i]);
    // }
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
        // int t = h->arr[i].id;
        // h->arr[i].id = h->arr[largest].id;
        // h->arr[largest].id = t;
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

// int main() {
//     record arr[4] = {{"kmszbuzhuj",127681}, {"oxnwgsmbek",610324}, {"qynfjkfoxk", 746080}, {"rogdshojsi",310198}};
//     // for(int i=0; i<10; i++) {
//     //     printf("%d ", arr[i]);
//     // }
//     printf("\nAfter Heap sort: ");
//     HEAP *h = HEAPSORT(arr, 4);
//     for(int i=0; i<4; i++) {
//         printf("%d ", h->arr[i].id);
//     }
//     return 0;
// }

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