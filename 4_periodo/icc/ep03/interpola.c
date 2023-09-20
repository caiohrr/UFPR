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

double interpolacaoLagrange(Ponto *vetor, uint n, double x) {
        double den = 1, xi, li, resultado;
        double num = x - vetor[0].x;

        for (uint i = 1; i < n; i++) {
                num *= (x - vetor[i].x);
        }
        //printf("num: %lf", num);

        resultado = 0;
        for (uint i = 0; i < n; i++) {
                den = 1;
                xi = vetor[i].x;
                for (uint j = 0; j < n; j++) {
                        if (i != j) {
                                den *= (xi - vetor[j].x);
                        }
                }
                den *= x - xi;
                //printf("den: %lf", den);
                li = num / den;
                resultado += li * vetor[i].y;
                //printf("%lf\n", resultado);
        }
        return resultado;
}

double calculaDiferencaDividida(Ponto *vetor, uint a, uint b) {

        if (a == b) {
                return vetor[a].y;
        }

        double mult = (calculaDiferencaDividida(vetor, a + 1, b) - calculaDiferencaDividida(vetor, a, b - 1)) / (vetor[b].x - vetor[a].x);

        return mult;
}

double interpolacaoNewton(Ponto *vetor, uint n, double x) {

        double resultado = 0;

        for (uint i = 0; i < n; i++) {
                double tmp = calculaDiferencaDividida(vetor, 0, i);
                for (uint j = 0; j < i; j++) {
                        tmp *= x - vetor[j].x;
                }
                resultado += tmp;
        }

        return resultado;
}

int main(int argc, char **argv) {
        LIKWID_MARKER_INIT;


        if (argc < 1)
                return 1;

        uint n;
        double x = atof(argv[1]);
        scanf("%u", &n);

        Ponto *entrada = criarVetorPontos(n);
        for(uint i = 0; i < n; i++) {
                scanf("%lf %lf", &entrada[i].x, &entrada[i].y);
        }
        
        double tempoL = timestamp();

         LIKWID_MARKER_START("interpolacaoLagrange");

        double respostaLagrange = interpolacaoLagrange(entrada, n, x);

        tempoL = timestamp() - tempoL;

        LIKWID_MARKER_STOP("interpolacaoLagrange");

        double tempoN = timestamp();

        LIKWID_MARKER_START("interpolacaoNewton");

        double respostaNewton = interpolacaoNewton(entrada, n, x);

        tempoN = timestamp() - tempoN;

        LIKWID_MARKER_STOP("interpolacaoNewton");

        printf("P%u(%lf) = %.8lf\n", n, x, respostaLagrange);
        printf("P%u(%lf) = %.8lf\n", n, x, respostaNewton);
        printf("Tempo Lagrange: %lf\n", tempoL);
        printf("Tempo Newton: %lf\n", tempoN);
        
        destruirVetorPontos(entrada);

        LIKWID_MARKER_CLOSE;
        return 0;
}
