/* File: test2.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	char *ptr = argv[1];
	long num;
	num = strtol(ptr, &ptr, 10);
	if (*ptr == '\0')
		printf("The input argument is a number: %ld\n", num);
	else
		printf("Not an number\n");
	return 0;
}
