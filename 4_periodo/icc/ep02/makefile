CC = gcc
CFLAGS = -Wall -Wextra -g -lm -std=gnu99 -O3 -mavx -march=native
objects = ep02.o

all: $(objects)
	$(CC) $(CFLAGS) $(objects) -o ep02

ep02.o: ep02.c
	$(CC) $(CFLAGS) -c ep02.c

clean:
	-rm -f *.o

purge: clean
	-rm -f ep02
