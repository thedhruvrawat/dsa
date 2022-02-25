runRecMS : recursive.c compRecMS
	gcc -o runRecMS recursive.c recursiveMerge.o merge.o

runIterMS : iterativen.c compRecMS
	gcc -o runIterMS iterative.c iterativeMerge.o merge.o

compRecMS : recursiveMerge.c merge.o recursiveMerge.h
	gcc -c recursiveMerge.c 

compIterMS : iterativeMerge.c merge.o iterativeMerge.h
	gcc -c iterativeMerge.c 

merge.o : merge.h merge.c element.h
	gcc -c merge.c

compare : compare.c compIterMS merge.o compRecMS
	gcc -o compare compare.c iterativeMerge.o merge.o recursiveMerge.o

clean:
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.out
	rm -rf *.txt