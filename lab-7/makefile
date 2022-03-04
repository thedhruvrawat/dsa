CC=gcc
#CC=gcc -pg
#CC=gcc -pg
LFLAGS = -lm
FILENAME:=  $(patsubst %.c,%.o,$(wildcard *.c))
all: $(FILENAME) main
%.o: %.c
	$(CC) -c -g $< -o $@ $(LFLAGS)
main: main.o 	
	$(CC) -g *.o -o $@ $(LFLAGS)
clean:
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.out