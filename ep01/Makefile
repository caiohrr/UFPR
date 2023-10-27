CC = gcc
CFLAGS = -Wall -Wextra -g -lm -std=c99
objects = ep01.o

all: $(objects)
	$(CC) $(CFLAGS) $(objects) -o ep01

ep01.o: ep01.c
	$(CC) $(CFLAGS) -c ep01.c

clean:
	-rm -f *.o

purge: clean
	-rm -f ep01
