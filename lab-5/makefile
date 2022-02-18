CC=gcc
#CC=gcc -pg
#CC=gcc -pg
LFLAGS = -lm
FILENAME:=  $(patsubst %.c,%.o,$(wildcard *.c))
all: $(FILENAME) rec.exe
%.o: %.c
	$(CC) -pg -w -c -g $< -o $@ $(LFLAGS)
rec.exe: sortingTimeAndSpace.o 	
	$(CC) -pg -w -g *.o -o $@ $(LFLAGS)
clean:
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.out
	rm -rf *.txt