runRecMS : recursive.c compRecMS
	gcc -w -o runRecMS recursive.c recursiveMerge.o merge.o

runIterMS : iterative.c compIterMS
	gcc -w -o runIterMS iterative.c iterativeMerge.o merge.o

compRecMS : recursiveMerge.c merge.o recursiveMerge.h
	gcc -w -c recursiveMerge.c 

compIterMS : iterativeMerge.c merge.o iterativeMerge.h
	gcc -w -c iterativeMerge.c 

merge.o : merge.h merge.c element.h
	gcc -w -c merge.c

compare : compare.c compIterMS merge.o compRecMS
	gcc -w -o compare compare.c iterativeMerge.o merge.o recursiveMerge.o

writeMS : writeMS.c compRecMS
	gcc -o writeMS writeMS.c recursiveMerge.o merge.o

clean:
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.out
	rm -rf *.txt
	rm -r output
	rm -rf runRecMS
	rm -rf compare
	rm -rf runIterMS
	rm -rf compRecMS
	rm -rf compIterMS
	rm -rf writeMS