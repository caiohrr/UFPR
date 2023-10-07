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
