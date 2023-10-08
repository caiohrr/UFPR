//Caio Henrique Ramos Rufino (GRR20224386)
//Frank Wolff Hannemann (GRR20224758)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "libSistemaIntervalar.h"

NumIntervalar *criarVetorIntervalar(uint n) {
        NumIntervalar *vetor = malloc(sizeof(NumIntervalar) * n);
        if (vetor == NULL)
                return NULL;
        return vetor;
}

NumIntervalar **criarMatrizIntervalar(uint n) {

        NumIntervalar **matriz = malloc(sizeof(NumIntervalar*) * n);
        if (matriz == NULL)
                return NULL;
        for (uint i = 0; i < n; i++) {
                matriz[i] = criarVetorIntervalar(n);
        }

        return matriz;
}

void destruirVetorIntervalar(NumIntervalar *vetor) {
        free(vetor);
}

void imprimirVetorIntervalar(NumIntervalar *vetor, uint n) {

        for (uint i = 0; i < n; i++) 
                printf("[%1.8e, %1.8e] ", vetor[i].menor, vetor[i].maior);
}

void copiarVetorIntervalar(NumIntervalar *original, NumIntervalar *novo, uint n) {

        for (uint i = 0; i < n; i++) {
                novo[i].menor = original[i].menor;
                novo[i].maior = original[i].maior;
        }
}

void destruirMatrizIntervalar(NumIntervalar **matriz, uint n) {

        for (uint i = 0; i < n; i++) {
                free(matriz[i]);
        }

        free(matriz);
}

void lerMatrizIntervalar(NumIntervalar **matriz, uint n) {

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                        scanf("%lf %lf", &matriz[i][j].menor, &matriz[i][j].maior);
                }
        }
}

void imprimirMatrizIntervalar(NumIntervalar **matriz, uint n) {

        for (uint i = 0; i < n; i++) {
                uint j;
                for (j = 0; j < n - 1; j++) {
                        printf("[%1.8e %1.8e], ", matriz[i][j].menor, matriz[i][j].maior);
                }
                printf("[%1.8e %1.8e]\n", matriz[i][j].menor, matriz[i][j].maior);
        }
}

void copiarMatriz(NumIntervalar **original, NumIntervalar **nova, uint n) {

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                        nova[i][j].menor = original[i][j].menor;
                        nova[i][j].maior = original[i][j].maior;
                }
        }
}

void imprimirSistemaIntervalar(NumIntervalar **matriz, NumIntervalar *vetor, uint n) {

        for (uint i = 0; i < n; i++) {
                uint j;
                for (j = 0; j < n - 1; j++) {
                        printf("[%1.8e %1.8e], ", matriz[i][j].menor, matriz[i][j].maior);
                }
                printf("[%1.8e %1.8e]  ", matriz[i][j].menor, matriz[i][j].maior);

                printf("[%1.8e %1.8e]\n", vetor[i].menor, vetor[i].maior);
        }
}

uint encontraMaxIntervalar(NumIntervalar **matriz, uint n, uint i) {

        double max = matriz[i][i].menor;
        uint linha = i; 

        for (uint j = i + 1; j < n; j++) {
                if (max < matriz[j][i].menor) {
                        max = matriz[j][i].menor;
                        linha = j;
                }
        }

        return linha;
}

void retrossubsIntervalar(NumIntervalar **matriz, NumIntervalar *b, NumIntervalar *x, uint n) {
        for (int i = n - 1; i >= 0; --i) {
                x[i].menor = b[i].menor;
                x[i].maior = b[i].maior;
                for (uint j = i + 1; j < n; ++j)
                        x[i] = subtracaoIntervalar(x[i], multiplicacaoIntervalar(matriz[i][j], x[j])); 
                x[i] = divisaoIntervalar(x[i], matriz[i][i]);
        }
}

void trocaLinhaIntervalar(NumIntervalar **matriz, uint n, NumIntervalar *b, int i, uint pivo) {

        NumIntervalar tmp, tmp2;

        tmp2.menor = b[i].menor;
        tmp2.maior = b[i].maior;
        b[i].menor = b[pivo].menor;
        b[i].maior = b[pivo].maior;
        b[pivo].menor = tmp2.menor;
        b[pivo].maior = tmp2.maior;

        for (uint j = 0; j < n; j++) {
                tmp.menor = matriz[i][j].menor;
                tmp.maior = matriz[i][j].maior;
                matriz[i][j].menor = matriz[pivo][j].menor;
                matriz[i][j].maior = matriz[pivo][j].maior;
                matriz[pivo][j].menor = tmp.menor;
                matriz[pivo][j].maior = tmp.maior;
        }
}

void eliminacaoGauss(NumIntervalar **matriz, NumIntervalar *b, uint n) {

        // para cada linha a partir da primeira
        for (uint i = 0; i < n - 1; ++i) {
                uint pivo = encontraMaxIntervalar(matriz, n, i);
                if (i != pivo)
                        trocaLinhaIntervalar(matriz, n, b, i, pivo);

                for(uint k = i + 1; k < n; ++k) {
                        NumIntervalar m = divisaoIntervalar(matriz[k][i], matriz[i][i]);

                        matriz[k][i].menor = 0.0;
                        matriz[k][i].maior = 0.0;

                        for (uint j = i + 1; j < n; ++j)
                                matriz[k][j] = subtracaoIntervalar(matriz[k][j], multiplicacaoIntervalar(matriz[i][j], m));
                        b[k] = subtracaoIntervalar(b[k], multiplicacaoIntervalar(b[i], m));
                }
        }
}
