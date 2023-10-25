#include <stdio.h>
#include <stdlib.h>    /* exit, malloc, calloc, etc. */
#include <string.h>
#include <getopt.h>    /* getopt */
#include <time.h>

#include "matriz.h"
#include "utils.h"

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname) {
        fprintf(stderr, "Forma de uso: %s [ <ordem> ] \n", progname);
        exit(1);
}

/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main (int argc, char *argv[]) {

        int n = DEF_SIZE;

        MatRow mRow_1, mRow_2, resMat;
        Vetor vet, res;

        /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

        if (argc < 2)
                usage(argv[0]);

        n = atoi(argv[1]);

        /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */

        srandom(20232);

        res = geraVetor(n, 0); // (real_t *) malloc (n*sizeof(real_t));
        resMat = geraMatRow(n, n, 1);

        mRow_1 = geraMatRow(n, n, 0);
        mRow_2 = geraMatRow(n, n, 0);

        vet = geraVetor(n, 0);

        if (!res || !resMat || !mRow_1 || !mRow_2 || !vet) {
                fprintf(stderr, "Falha em alocação de memória !!\n");
                liberaVetor((void*) mRow_1);
                liberaVetor((void*) mRow_2);
                liberaVetor((void*) resMat);
                liberaVetor((void*) vet);
                liberaVetor((void*) res);
                exit(2);
        }

#ifdef _DEBUG_
        prnMat(mRow_1, n, n);
        prnMat(mRow_2, n, n);
        prnVetor(vet, n);
        printf("=================================\n\n");
#endif /* _DEBUG_ */

        
        rtime_t tempoMatVet = timestamp();
        multMatVet(mRow_1, vet, n, n, res);
        tempoMatVet = timestamp() - tempoMatVet;

        rtime_t tempoMatVetV2 = timestamp();
        multMatVetV2(mRow_1, vet, n, n, res);
        tempoMatVetV2 = timestamp() - tempoMatVetV2;

        rtime_t tempoMatMat = timestamp();
        multMatMat(mRow_1, mRow_2, n, resMat);
        tempoMatMat = timestamp() - tempoMatMat;

        rtime_t tempoMatMatV2 = timestamp();
        multMatMatV2(mRow_1, mRow_2, n, resMat);
        tempoMatMatV2 = timestamp() - tempoMatMatV2;

#ifdef _DEBUG_
        prnVetor(res, n);
        prnMat(resMat, n, n);
#endif /* _DEBUG_ */

        printf("Tempo matriz vetor: %lf\nTempo matriz matriz: %lf\n", tempoMatVet, tempoMatMat);
        printf("Tempo matriz vetor(V2): %lf\n", tempoMatVetV2);
        printf("Tempo matriz matriz(V2): %lf\n", tempoMatMatV2);
        liberaVetor((void*) mRow_1);
        liberaVetor((void*) mRow_2);
        liberaVetor((void*) resMat);
        liberaVetor((void*) vet);
        liberaVetor((void*) res);

        return 0;
}

