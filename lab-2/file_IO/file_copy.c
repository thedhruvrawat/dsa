#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
    FILE *freader, *fwriter;
    char ch;
    freader = fopen(argv[1], "r");
    if(freader == NULL) {
        printf("File %s not available!\n", argv[1]);
        exit(1);
    }
    fwriter = fopen(argv[2],"w");
    if(freader == NULL) {
        printf("File %s not available!\n", argv[2]);
        exit(1);
    }
    printf("Copying following from %s to %s:\n", argv[1], argv[2]);
    printf("File 1 ---------------------------\n");
    ch = fgetc(freader);
    while (ch != EOF)
    {
        fprintf(fwriter,"%c", ch);
        printf("%c", ch);
        ch = fgetc(freader);
    }
    printf("\n----------------------------------\n");
    printf("Copying operation finished...\n");
    fclose(freader);
    fclose(fwriter);
    return 0;
}