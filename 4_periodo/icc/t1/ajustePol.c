#include <stdio.h>
#include <stdlib.h>
#include "likwid.h"
#include "libAjustePolinomialIntervalar.h"

int main() {


        uint grau, nPontos;
        double *vetorX, *vetorY;

        scanf("%u %u", &grau, &nPontos);

        vetorX = criarVetorDouble(nPontos);
        vetorY = criarVetorDouble(nPontos);

        lerEntrada(vetorX, vetorY, nPontos);

        NumIntervalar *vetorIntervalarX = criarVetorIntervalar(nPontos);
        NumIntervalar *vetorIntervalarY = criarVetorIntervalar(nPontos);
        NumIntervalar *vetorIntervalarB = criarVetorIntervalar(nPontos);
        NumIntervalar *vetorIntervalarR = criarVetorIntervalar(nPontos);
        NumIntervalar *vetorIntervalarCoef = criarVetorIntervalar(grau);
        NumIntervalar **matrizIntervalar = criarMatrizIntervalar(grau);

        for (uint i = 0; i < nPontos; i++) {
                vetorIntervalarX[i] = doubleToNumIntervalar(vetorX[i]);
                vetorIntervalarY[i] = doubleToNumIntervalar(vetorY[i]);
        }


        LIKWID_MARKER_INIT;
        LIKWID_MARKER_START("GerarSistema");
        gerarSistemaIntervalar(matrizIntervalar, vetorIntervalarX, vetorIntervalarY, vetorIntervalarB, grau, nPontos);
        LIKWID_MARKER_STOP("GerarSistema");

        LIKWID_MARKER_START("ResolverSistema");
        eliminacaoGauss(matrizIntervalar, vetorIntervalarB, grau);
        retrossubsIntervalar(matrizIntervalar, vetorIntervalarB, vetorIntervalarCoef, grau);
        LIKWID_MARKER_STOP("ResolverSistema");
        LIKWID_MARKER_CLOSE;

        imprimirVetorIntervalar(vetorIntervalarCoef, grau);

        calcularResiduo(vetorIntervalarR, vetorIntervalarCoef, vetorIntervalarX, vetorIntervalarY, grau, nPontos);



        printf("\n");
        imprimirVetorIntervalar(vetorIntervalarR, nPontos);
        
        printf("\n");

        free(vetorX);
        free(vetorY);
        free(vetorIntervalarX);
        free(vetorIntervalarY);
        free(vetorIntervalarB);
        free(vetorIntervalarR);
        free(vetorIntervalarCoef);
        destruirMatrizIntervalar(matrizIntervalar, grau);


        return 0;
}
