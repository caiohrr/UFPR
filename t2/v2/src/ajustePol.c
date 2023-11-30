//Caio Henrique Ramos Rufino (GRR20224386) Frank Wolff Hannemann (GRR20224758)

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "likwid.h"
#include "libAjustePolinomialIntervalar.h"

int main() {

        LIKWID_MARKER_INIT;
        long long grau, nPontos;
        double *vetorX, *vetorY, tempoGerarSistema, tempoResolverSistema, tempoCalcularResiduo;

        scanf("%lld %lld", &grau, &nPontos);
        grau++;

        vetorX = criarVetorDouble(nPontos);
        vetorY = criarVetorDouble(nPontos);

        lerEntrada(vetorX, vetorY, nPontos);

        NumIntervalar *vetorIntervalarX = criarVetorIntervalar(nPontos);
        NumIntervalar *vetorIntervalarY = criarVetorIntervalar(nPontos);
        NumIntervalar *vetorIntervalarB = criarVetorIntervalar(nPontos);
        NumIntervalar *vetorIntervalarR = criarVetorIntervalar(nPontos);
        NumIntervalar *vetorIntervalarCoef = criarVetorIntervalar(grau);
        NumIntervalar *matrizIntervalar = criarMatrizIntervalar(grau);

        for (long long i = 0; i < nPontos; i++) {
                vetorIntervalarX[i] = doubleToNumIntervalar(vetorX[i]);
                vetorIntervalarY[i] = doubleToNumIntervalar(vetorY[i]);
        }


        tempoGerarSistema = timestamp();
        LIKWID_MARKER_START("GerarSistema");
        gerarSistemaIntervalar(matrizIntervalar, vetorIntervalarX, vetorIntervalarY, vetorIntervalarB, grau, nPontos);
        LIKWID_MARKER_STOP("GerarSistema");
        tempoGerarSistema = timestamp() - tempoGerarSistema;

        tempoResolverSistema = timestamp();
        LIKWID_MARKER_START("ResolverSistema");
        eliminacaoGauss(matrizIntervalar, vetorIntervalarB, grau);
        retrossubsIntervalar(matrizIntervalar, vetorIntervalarB, vetorIntervalarCoef, grau);
        LIKWID_MARKER_STOP("ResolverSistema");
        tempoResolverSistema = timestamp() - tempoResolverSistema;

        //Comentado para rodar os testes
        //imprimirVetorIntervalar(vetorIntervalarCoef, grau);
        
        LIKWID_MARKER_START("CalcularResiduo");
        tempoCalcularResiduo = timestamp();
        calcularResiduo(vetorIntervalarR, vetorIntervalarCoef, vetorIntervalarX, vetorIntervalarY, grau, nPontos);
        LIKWID_MARKER_STOP("CalcularResiduo");
        tempoCalcularResiduo = timestamp() - tempoCalcularResiduo;


        //Comentado para rodar os testes
        //printf("\n");
        //imprimirVetorIntervalar(vetorIntervalarR, nPontos);
        //printf("\n");
        
        printf("TempoGerarSistema: %lf\nTempoResolverSistema: %lf\nTempoCalularResiduo: %lf\n", tempoGerarSistema, tempoResolverSistema, tempoCalcularResiduo);

        free(vetorX);
        free(vetorY);
        free(vetorIntervalarX);
        free(vetorIntervalarY);
        free(vetorIntervalarB);
        free(vetorIntervalarR);
        free(vetorIntervalarCoef);
        destruirMatrizIntervalar(matrizIntervalar);

        LIKWID_MARKER_CLOSE;

        return 0;
}
