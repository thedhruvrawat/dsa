CC=gcc
#CC=gcc -pg
#CC=gcc -pg
LFLAGS = -lm
FILENAME:=  $(patsubst %.c,%.o,$(wildcard *.c))
all: $(FILENAME) cycle.exe
%.o: %.c
	$(CC) -c -g -Wall $< -o $@ $(LFLAGS)
cycle.exe: cycle.o 	
	$(CC) -pg -g -Wall cycle1.o cycle.o alloc.o linkedlist.o -o $@ $(LFLAGS)
clean:
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.txt
	rm -rf observations.xlsx
	rm -rf *.out
	rm -rf prof_output