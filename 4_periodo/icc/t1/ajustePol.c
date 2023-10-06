#include <stdio.h>
#include <stdlib.h>
#include "libSistemaIntervalar.h"


double *criarVetorDouble(uint n) {

        double *vetorDouble = malloc(sizeof(double) * n);

        if (!vetorDouble)
                return NULL;

        return vetorDouble;
}

void lerEntrada(double *vetorX, double *vetorY, uint nPontos) {
         
        for (uint i = 0; i < nPontos; i++) {
                scanf("%lf %lf", &vetorX[i], &vetorY[i]);
        }
}

void calcularResiduo(NumIntervalar *vetorR, NumIntervalar *vetorIntervalarCoef, NumIntervalar *vetorX, NumIntervalar *vetorY, uint grau, uint nPontos) {

        for (uint i = 0; i < nPontos; i++) {
                NumIntervalar tmp;
                tmp.menor = 0;
                tmp.maior = 0;
                for (uint j = 0; j < grau; j++) {
                       tmp = somaIntervalar(tmp, multiplicacaoIntervalar(vetorIntervalarCoef[j], expIntervalar(vetorX[i], j)));  
                }
                vetorR[i] = subtracaoIntervalar(vetorY[i], tmp); 
        } 
}

void gerarSistemaIntervalar(NumIntervalar **matriz, NumIntervalar *vetorX, NumIntervalar *vetorY, NumIntervalar *vetorB, uint grau, uint nPontos) {

        for (uint i = 0; i < grau; i++) {
                NumIntervalar tmp;
                for (uint j = 0; j < grau; j++) {
                        tmp.menor = 0;
                        tmp.maior = 0;
                        for (uint l = 0; l < nPontos; l++) {
                                //if (matriz[i - 1][j + 1] != NULL)
                                        //tmp = matriz[i - 1][j + 1];
                                        //break;
                                tmp = somaIntervalar(tmp, expIntervalar(vetorX[l], i + j));
                        }
                        matriz[i][j] = tmp;
                }

                NumIntervalar tmpX;
                tmp.menor = 0;
                tmp.maior = 0;
                for (uint m = 0; m < nPontos; m++) {
                        tmpX = expIntervalar(vetorX[m], i);
                        tmp = somaIntervalar(tmp, multiplicacaoIntervalar(vetorY[m], tmpX)); 
                }
                vetorB[i] = tmp;
        }
}

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

        //imprimirVetorIntervalar(vetorIntervalarY, n);

        gerarSistemaIntervalar(matrizIntervalar, vetorIntervalarX, vetorIntervalarY, vetorIntervalarB, grau, nPontos);
        eliminacaoGauss(matrizIntervalar, vetorIntervalarB, grau);
        retrossubsIntervalar(matrizIntervalar, vetorIntervalarB, vetorIntervalarCoef, grau);
        //imprimirSistemaIntervalar(matrizIntervalar, vetorIntervalarB, grau);
        //printf("\n");
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
