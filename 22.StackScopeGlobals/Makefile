CFLAGS=-Wall -g -std=c99 -DNDEBUG
CC=gcc
LD=gcc

all: clean target

target: ex22.o ex22_main.o
	$(LD) ex22.o ex22_main.o -o ex22

ex22.o: ex22.c
	$(CC) $(CFLAGS) -o ex22.o -c ex22.c

ex22_main.o: ex22_main.c
	$(CC) $(CFLAGS) -o ex22_main.o -c ex22_main.c

clean:
	rm -f *.o ex22
