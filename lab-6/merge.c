#include "merge.h"

void merge(Element Ls1[], int sz1, Element Ls2[], int sz2, Element Ls[]) {
    int iter1 = 0, iter2 = 0, iter3 = 0;
    while(iter1<sz1 && iter2<sz2) {
        if(Ls1[iter1].cgpa <= Ls2[iter2].cgpa) {
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