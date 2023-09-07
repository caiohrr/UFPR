LIKWID_HOME=/home/soft/likwid

CC = gcc
CFLAGS = -I${LIKWID_HOME}/include -DLIKWID_PERFMON -Wall -Wextra -g -lm -std=gnu99 -O3 -mavx -march=native 

LFLAGS = -L${LIKWID_HOME}/lib -llikwid

objects = perfEG.o utils.o

all: $(objects)
	$(CC) $(CFLAGS) $(objects) -o perfEG $(LFLAGS) 
perfEG.o: perfEG.c
	$(CC) $(CFLAGS) -c perfEG.c

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	-rm -f *.o

purge: clean
	-rm -f perfEG
