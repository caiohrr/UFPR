LIKWID_HOME=/home/soft/likwid

CC = gcc
CFLAGS = -I${LIKWID_HOME}/include -DLIKWID_PERFMON -Wall -Wextra -g -lm -std=gnu99 -O3 -mavx -march=native 

LFLAGS = -L${LIKWID_HOME}/lib -llikwid

objects = interpola.o utils.o

all: $(objects)
	$(CC) $(CFLAGS) $(objects) -o interpola $(LFLAGS) 
interpola.o: interpola.c
	$(CC) $(CFLAGS) -c interpola.c

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	-rm -f *.o

purge: clean
	-rm -f interpola FLOPS_DP.log
