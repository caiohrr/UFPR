#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "likwid.h"
#include "utils.h"

typedef struct Ponto {
        double x, y;
} Ponto;

Ponto *criarVetorPontos(uint n) {

        Ponto *vetor = malloc(sizeof(Ponto) * n);
        if (!vetor)
                return NULL;

        return vetor;
}

void destruirVetorPontos(Ponto *vetor) {

        free(vetor);
}

void imprimirVetorPontos(Ponto *vetor, uint n) {

        for (uint i = 0; i < n; i++) {
                printf("(%lf, %lf)\n", vetor[i].x, vetor[i].y);
        }
}

double interpolacaoLagrange(Ponto *vetor, uint n, uint x) {

        double num = x - vetor[0].x;

        for (uint i = 1; i < n; i++) {
                num *= (x - vetor[i].x);
        }

        double den;

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                }
        }

}

int main() {

        uint n;
        scanf("%u", &n);

        Ponto *entrada = criarVetorPontos(n);
        for(uint i = 0; i < n; i++) {
                scanf("%lf %lf", &entrada[i].x, &entrada[i].y);
        }

        imprimirVetorPontos(entrada, n);

        destruirVetorPontos(entrada);

        return 0;
}
