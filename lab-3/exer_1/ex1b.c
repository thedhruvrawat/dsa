#include <stdio.h>

int p(int n)
{
    printf("Address of n: %u\n", &n);
    if(n<10)
        return p(n + 1);
    return 0;
}

int main() {
    p(0);
}