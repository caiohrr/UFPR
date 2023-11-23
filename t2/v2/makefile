LIKWID_HOME=/home/soft/likwid

CC = gcc
CFLAGS = -I${LIKWID_HOME}/include -Iinclude -DLIKWID_PERFMON -Wall -Wextra -lm -std=gnu11 -O3 -mavx -march=native 
LFLAGS = -L${LIKWID_HOME}/lib -llikwid -lm

OBJ = ajustePol.o libIntervalar.o libSistemaIntervalar.o libAjustePolinomialIntervalar.o utils.o

SRC_DIR = src
INC_DIR = include

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o ajustePol $(LFLAGS)

ajustePol.o: src/ajustePol.c
	$(CC) $(CFLAGS) -c src/ajustePol.c $(LFLAGS)

libIntervalar.o: src/libIntervalar.c
	$(CC) $(CFLAGS) -c src/libIntervalar.c

libSistemaIntervalar.o: src/libIntervalar.c src/libSistemaIntervalar.c
	$(CC) $(CFLAGS) -c src/libSistemaIntervalar.c

libAjustePolinomialIntervalar.o: src/libIntervalar.c src/libSistemaIntervalar.c src/libAjustePolinomialIntervalar.c
	$(CC) $(CFLAGS) -c src/libAjustePolinomialIntervalar.c

utils.o: src/utils.c
	$(CC) $(CFLAGS) -c src/utils.c

clean:
	-rm -f *.o

purge: clean
	-rm -f ajustePol FLOPS_DP.log ENERGY.log
