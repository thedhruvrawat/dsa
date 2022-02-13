CC=gcc
#CC=gcc -pg
#CC=gcc -pg
LFLAGS = -lm
FILENAME:=  $(patsubst %.c,%.o,$(wildcard *.c))
all: $(FILENAME) test.exe
%.o: %.c
	$(CC) -pg -c -g $< -o $@ $(LFLAGS)
test.exe: testMultiq.o 	
	$(CC) -pg -g *.o -o $@ $(LFLAGS)
clean:
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.out
	rm -rf prof_output10
	rm -rf prof_output100
	rm -rf prof_output10000