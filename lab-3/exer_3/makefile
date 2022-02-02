CC=gcc
#CC=gcc -pg
#CC=gcc -pg
LFLAGS = -lm
FILENAME:=  $(patsubst %.c,%.o,$(wildcard *.c))
all: $(FILENAME) cycle1.exe
%.o: %.c
	$(CC) -c -g -Wall $< -o $@ $(LFLAGS)
cycle1.exe: cycle1.o 	
	$(CC) -g -Wall *.o -o $@ $(LFLAGS)
clean:
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.txt