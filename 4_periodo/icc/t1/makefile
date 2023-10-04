LIKWID_HOME=/home/soft/likwid

CC = gcc
CFLAGS = -I${LIKWID_HOME}/include -DLIKWID_PERFMON -Wall -Wextra -g -lm -std=gnu99 -O3 -mavx -march=native 

LFLAGS = -L${LIKWID_HOME}/lib -llikwid -lm -g

objects = ajustePol.o libIntervalar.o

all: $(objects)
	$(CC) $(CFLAGS) $(objects) -o ajustePol $(LFLAGS) 

ajustePol.o: ajustePol.c
	$(CC) $(CFLAGS) -c ajustePol.c

libIntervalar.o: libIntervalar.c
	$(CC) $(CFLAGS) -c libIntervalar.c

clean:
	-rm -f *.o

purge: clean
	-rm -f ajustePol FLOPS_DP.log resultado.out
