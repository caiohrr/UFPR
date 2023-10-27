//Caio Henrique Ramos Rufino (GRR20224386)
//Frank Wolff Hannemann (GRR20224758)

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "likwid.h"
#include "libAjustePolinomialIntervalar.h"

int main() {

        uint grau, nPontos;
        double *vetorX, *vetorY, tempoGerarSistema, tempoResolverSistema;

        scanf("%u %u", &grau, &nPontos);
        grau++;

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

        tempoGerarSistema = timestamp();
        LIKWID_MARKER_INIT;
        LIKWID_MARKER_START("GerarSistema");
        gerarSistemaIntervalar(matrizIntervalar, vetorIntervalarX, vetorIntervalarY, vetorIntervalarB, grau, nPontos);
        LIKWID_MARKER_STOP("GerarSistema");
        tempoGerarSistema = timestamp() - tempoGerarSistema;

        tempoResolverSistema = timestamp();
        LIKWID_MARKER_START("ResolverSistema");
        eliminacaoGauss(matrizIntervalar, vetorIntervalarB, grau);
        retrossubsIntervalar(matrizIntervalar, vetorIntervalarB, vetorIntervalarCoef, grau);
        LIKWID_MARKER_STOP("ResolverSistema");
        LIKWID_MARKER_CLOSE;
        tempoResolverSistema = timestamp() - tempoResolverSistema;

        imprimirVetorIntervalar(vetorIntervalarCoef, grau);

        calcularResiduo(vetorIntervalarR, vetorIntervalarCoef, vetorIntervalarX, vetorIntervalarY, grau, nPontos);
        printf("\n");
        imprimirVetorIntervalar(vetorIntervalarR, nPontos);
        printf("\n");
        printf("%1.8e\n%1.8e\n", tempoGerarSistema, tempoResolverSistema);

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
