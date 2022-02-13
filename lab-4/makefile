CC=gcc
#CC=gcc -pg
#CC=gcc -pg
LFLAGS = -lm
FILENAME:=  $(patsubst %.c,%.o,$(wildcard *.c))
all: $(FILENAME) test.exe
%.o: %.c
	$(CC) -pg -c -g -Wall $< -o $@ $(LFLAGS)
test.exe: testMultiq.o 	
	$(CC) -pg -g -Wall *.o -o $@ $(LFLAGS)
clean:
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.out
	rm -rf prof_output