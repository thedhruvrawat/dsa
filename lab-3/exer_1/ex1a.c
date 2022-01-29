#include <stdio.h>
int bits;

void p()
{
    int pilani;
    printf("Address of variable pilani: %u\n", &pilani);
}

void g() {
    int goa;
    printf("Address of variable goa: %u\n", &goa);
    p();
}

void h() {
    int hyd;
    printf("Address of variable hyd: %u\n", &hyd);
    g();
}

void d() {
    int dub;
    printf("Address of variable dub: %u\n", &dub);
    h();
}

int main() {
    // p();
    // g();
    // h();
    d();
}