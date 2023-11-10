//Caio Henrique Ramos Rufino (GRR20224386)
//Frank Wolff Hannemann (GRR20224758)

#include <stdio.h>
#include <stdlib.h>
#include "libSistemaIntervalar.h"

double *criarVetorDouble(long long n) {

        double *vetorDouble = malloc(sizeof(double) * n);

        if (!vetorDouble)
                return NULL;

        return vetorDouble;
}

void lerEntrada(double *vetorX, double *vetorY, long long nPontos) {
         
        for (long long i = 0; i < nPontos; i++) {
                scanf("%lf %lf", &vetorX[i], &vetorY[i]);
        }
}

void calcularResiduo(NumIntervalar *vetorR, NumIntervalar *vetorIntervalarCoef, NumIntervalar *vetorX, NumIntervalar *vetorY, long long grau, long long nPontos) {

        // Gerar um vetor dos expoentes calculando seus valores apenas uma vez, ao inves de recalcular durante o loop
        NumIntervalar vetorExp[grau];
        for (long long j = 0; j < grau; j++) {
                vetorExp[j] = expIntervalar(vetorX[j], j);
        }

        for (long long i = 0; i < nPontos; i++) {
                NumIntervalar tmp;
                tmp.menor = 0;
                tmp.maior = 0;
                for (long long j = 0; j < grau; j++) {
                       tmp = somaIntervalar(tmp, multiplicacaoIntervalar(vetorIntervalarCoef[j], vetorExp[j]));  
                }
                vetorR[i] = subtracaoIntervalar(vetorY[i], tmp); 
        } 
}


//void gerarSistemaIntervalar(NumIntervalar *matriz, NumIntervalar *vetorX, NumIntervalar *vetorY, NumIntervalar *vetorB, long long grau, long long nPontos) {
//
//        for (long long i = 0; i < grau; i++) {
//                NumIntervalar tmp;
//                for (long long j = 0; j < grau; j++) {
//                        tmp.menor = 0;
//                        tmp.maior = 0;
//                        for (long long l = 0; l < nPontos; l++) {
//                                tmp = somaIntervalar(tmp, expIntervalar(vetorX[l], i + j));
//                        }
//                        matriz[i][j] = tmp;
//                }
//
//                NumIntervalar tmpX;
//                tmp.menor = 0;
//                tmp.maior = 0;
//                for (long long m = 0; m < nPontos; m++) {
//                        tmpX = expIntervalar(vetorX[m], i);
//                        tmp = somaIntervalar(tmp, multiplicacaoIntervalar(vetorY[m], tmpX)); 
//                }
//                vetorB[i] = tmp;
//        }
//}

void gerarVetorCoef(NumIntervalar *matriz, NumIntervalar *vetorX, long long grau, long long nPontos, NumIntervalar *vetorCoef) {

        for(long long i = 0; i < grau * 2 - 1; i++) {
                NumIntervalar tmp;
                tmp.menor = 0;
                tmp.maior = 0;
                for (long long j = 0; j < nPontos; j++) {
                        tmp = somaIntervalar(tmp, expIntervalar(vetorX[j], i));
                }
                vetorCoef[i] = tmp;
        }
        
}

void gerarSistemaIntervalar(NumIntervalar *matriz, NumIntervalar *vetorX, NumIntervalar *vetorY, NumIntervalar *vetorB, long long grau, long long nPontos) {
        NumIntervalar vetorCoef[grau * 2 - 1];

        gerarVetorCoef(matriz, vetorX, grau, nPontos, vetorCoef);
        for (long long i = 0; i < grau; i++) {
                for (long long j = 0; j < grau; j++) {
                        matriz[i * grau + j].menor = vetorCoef[i + j].menor;
                        matriz[i * grau + j].maior = vetorCoef[i + j].maior;
                }
        }

        for (long long i = 0; i < grau; i++) {

                NumIntervalar tmp, tmpX;
                tmp.menor = 0;
                tmp.maior = 0;
                for (long long m = 0; m < nPontos; m++) {
                        tmpX = expIntervalar(vetorX[m], i);
                        tmp = somaIntervalar(tmp, multiplicacaoIntervalar(vetorY[m], tmpX)); 
                }
                vetorB[i] = tmp;
        }
}
