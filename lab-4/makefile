CC=gcc
#CC=gcc -pg
#CC=gcc -pg
LFLAGS = -lm
FILENAME:=  $(patsubst %.c,%.o,$(wildcard *.c))
all: $(FILENAME) que.exe
%.o: %.c
	$(CC) -c -g -Wall $< -o $@ $(LFLAGS)
que.exe: que.o 	
	$(CC) -g -Wall *.o -o $@ $(LFLAGS)
clean:
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.out