CC=gcc
#CC=gcc -pg
#CC=gcc -pg
LFLAGS = -lm
FILENAME:=  $(patsubst %.c,%.o,$(wildcard *.c))
all: $(FILENAME) rec.exe
%.o: %.c
	$(CC) -pg -c -g $< -o $@ $(LFLAGS)
rec.exe: main.o 	
	$(CC) -pg -g *.o -o $@ $(LFLAGS)
clean:
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.out