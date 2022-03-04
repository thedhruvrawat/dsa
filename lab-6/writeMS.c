#include "element.h"
#include "recursiveMerge.h"

int STACK_TOP;

void copyFile(char *sourcename, char* targetname) {
   char ch;
   FILE *source = fopen(sourcename, "r");
   FILE *target = fopen(targetname, "w");

   if( source == NULL ) {
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
  
   if( target == NULL )
   {
      fclose(source);
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 
   while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
 
   fclose(source);
   fclose(target);
}

void printSort(char* input, int k, int size) {
  FILE* infile = fopen(input, "r");
  char *filename = malloc(sizeof(char)*100);
  ELIST arr = (ELIST)malloc(sizeof(Element) * size);
	int d=0, j=0;

	while(++j<=(size/k)){
    sprintf(filename, "output/%d/%d/%d.txt", k, size, j);
    for (int i = 0; i < k; i++)
    {
      if(feof(infile)){
				d=i;
				break;
			}
			fscanf(infile,"%[^,], %f\n",arr[i].name,&arr[i].cgpa);
    }

    if(d){
			k=d;
		}
    FILE* outfile = fopen(filename, "w");
		recursiveMS(arr,k);
		for(int i=0;i<k;i++){
			fprintf(outfile,"%10s, %0.2f\n",arr[i].name,arr[i].cgpa);
		}
    fclose(outfile);
		if(d)break;
  }
  fclose(infile);
	
}

void mergeFiles(char* input1, char* input2, char* output){
	FILE* infile1 = fopen(input1,"r");
	FILE* infile2 = fopen(input2,"r");
	FILE* outfile = fopen(output,"w");

	Element a;
	Element b;

	fscanf(infile1,"\n%[^,], %f", a.name, &a.cgpa);
	fscanf(infile2,"\n%[^,], %f", b.name, &b.cgpa);

	while(!feof(infile1) && !feof(infile2)) {
		if(a.cgpa<=b.cgpa){
			fprintf(outfile,"\n%10s, %0.2f", a.name, a.cgpa);
			fscanf(infile1,"\n%[^,], %f", a.name, &a.cgpa);
		} else {
			fprintf(outfile,"\n%10s, %0.2f", b.name, b.cgpa);
			fscanf(infile2,"\n%[^,], %f", b.name, &b.cgpa);
		}
	} 
  if(a.cgpa<=b.cgpa) fprintf(outfile,"\n%10s, %0.2f", a.name, a.cgpa);
  else fprintf(outfile,"\n%10s, %0.2f", b.name, b.cgpa);

	if(feof(infile1)){
		while (!feof(infile2)) {
			fprintf(outfile,"\n%10s, %0.2f", b.name, b.cgpa);
			fscanf(infile2,"\n%[^,], %f", b.name, &b.cgpa);
    } 
  }

  if(feof(infile2)){
		while (!feof(infile1)) {
			fprintf(outfile,"\n%10s, %0.2f", a.name, a.cgpa);
			fscanf(infile1,"\n%[^,], %f", a.name, &a.cgpa);
    } 
  }

  fclose(infile1);
	fclose(infile2);
	fclose(outfile);
}

void createRecords() {
  int fname = 1024;
  for(int j=0; j<2; j++) {
    char *temp1 = malloc(sizeof(char)*100);
    sprintf(temp1, "input/%d.txt",fname);
    printSort(temp1, 64, fname);
    printSort(temp1, 256, fname);
    printSort(temp1, 512, fname);
    printSort(temp1, 1024, fname);
    fname*=10;
  }
}

int main() {
  createRecords();
  int fname = 1024;
  for(int j=0; j<1; j++) {
    char *filename1 = "output/64/1024/1.txt";
    char *outername = malloc(sizeof(char) * 100);
    int p = 2, k=64, i=1;
    while (p <= (fname / k)) {
      char *filename2 = malloc(sizeof(char)*100);
      char* tempFile = malloc(sizeof(char)*100);
      sprintf(filename2, "output/%d/%d/%d.txt", k, fname, p++);
      sprintf(tempFile, "output%d.txt", i++);
      mergeFiles(filename1, filename2, tempFile);
      filename1 = tempFile;
    }
    fname*=10;
  }
}
