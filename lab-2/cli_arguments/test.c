/* File: test.c */
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
	char *progName = strtok(argv[0], "/");
	progName = strtok(NULL, "/");
	printf("%s ", progName);
	for (int i = 1; i < argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("\n");
	return 0;
}
