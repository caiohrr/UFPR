//Caio Henrique Ramos Rufino (GRR20224386)
//Frank Wolff Hannemann (GRR20224758)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "libSistemaIntervalar.h"

NumIntervalar *criarVetorIntervalar(long long n) {
        NumIntervalar *vetor = malloc(sizeof(NumIntervalar) * n);
        if (vetor == NULL)
                return NULL;
        return vetor;
}

NumIntervalar *criarMatrizIntervalar(long long n) {
        NumIntervalar *matriz = criarVetorIntervalar(n * n);
        if (matriz == NULL)
                return NULL;
        return matriz;
}

void destruirVetorIntervalar(NumIntervalar *vetor) {
        free(vetor);
}

void imprimirVetorIntervalar(NumIntervalar *vetor, long long n) {

        for (long long i = 0; i < n; i++) 
                printf("[%1.8e, %1.8e] ", vetor[i].menor, vetor[i].maior);
}

void copiarVetorIntervalar(NumIntervalar *original, NumIntervalar *novo, long long n) {

        for (long long i = 0; i < n; i++) {
                novo[i].menor = original[i].menor;
                novo[i].maior = original[i].maior;
        }
}

void destruirMatrizIntervalar(NumIntervalar *matriz) {

        free(matriz);
}

void lerMatrizIntervalar(NumIntervalar *matriz, long long n) {

        for (long long i = 0; i < n; i++) {
                for (long long j = 0; j < n; j++) {
                        scanf("%lf %lf", &matriz[i * n + j].menor, &matriz[i * n + j].maior);
                }
        }
}

void imprimirMatrizIntervalar(NumIntervalar *matriz, long long n) {

        for (long long i = 0; i < n; i++) {
                long long j;
                for (j = 0; j < n - 1; j++) {
                        printf("[%1.8e %1.8e], ", matriz[i * n + j].menor, matriz[i * n + j].maior);
                }
                printf("[%1.8e %1.8e]\n", matriz[i * n + j].menor, matriz[i * n + j].maior);
        }
}

void copiarMatriz(NumIntervalar *original, NumIntervalar *nova, long long n) {

        copiarVetorIntervalar(original, nova, n * n);

}

void imprimirSistemaIntervalar(NumIntervalar *matriz, NumIntervalar *vetor, long long n) {

        for (long long i = 0; i < n; i++) {
                long long j;
                for (j = 0; j < n - 1; j++) {
                        printf("[%1.8e %1.8e], ", matriz[i * n + j].menor, matriz[i * n + j].maior);
                }
                printf("[%1.8e %1.8e]  ", matriz[i * n + j].menor, matriz[i * n + j].maior);

                printf("[%1.8e %1.8e]\n", vetor[i].menor, vetor[i].maior);
        }
}

long long encontraMaxIntervalar(NumIntervalar *matriz, long long n, long long i) {

        double max = matriz[i * n + i].menor;
        long long linha = i; 

        for (long long j = i + 1; j < n; j++) {
                if (max < matriz[j * n + i].menor) {
                        max = matriz[j * n + i].menor;
                        linha = j;
                }
        }

        return linha;
}

void retrossubsIntervalar(NumIntervalar *matriz, NumIntervalar *b, NumIntervalar *x, long long n) {
        for (int i = n - 1; i >= 0; --i) {
                x[i].menor = b[i].menor;
                x[i].maior = b[i].maior;
                for (long long j = i + 1; j < n; ++j)
                        x[i] = subtracaoIntervalar(x[i], multiplicacaoIntervalar(matriz[i * n + j], x[j])); 
                x[i] = divisaoIntervalar(x[i], matriz[i * n + i]);
        }
}

void trocaLinhaIntervalar(NumIntervalar *matriz, long long n, NumIntervalar *b, int i, long long pivo) {

        NumIntervalar tmp, tmp2;

        tmp2.menor = b[i].menor;
        tmp2.maior = b[i].maior;
        b[i].menor = b[pivo].menor;
        b[i].maior = b[pivo].maior;
        b[pivo].menor = tmp2.menor;
        b[pivo].maior = tmp2.maior;

        for (long long j = 0; j < n; j++) {
                tmp.menor = matriz[i * n + j].menor;
                tmp.maior = matriz[i * n + j].maior;
                matriz[i * n + j].menor = matriz[pivo * n + j].menor;
                matriz[i * n + j].maior = matriz[pivo * n + j].maior;
                matriz[pivo * n + j].menor = tmp.menor;
                matriz[pivo * n + j].maior = tmp.maior;
        }
}

void eliminacaoGauss(NumIntervalar *matriz, NumIntervalar *b, long long n) {

        // para cada linha a partir da primeira
        for (long long i = 0; i < n - 1; ++i) {
                long long pivo = encontraMaxIntervalar(matriz, n, i);
                if (i != pivo)
                        trocaLinhaIntervalar(matriz, n, b, i, pivo);

                for(long long k = i + 1; k < n; ++k) {
                        NumIntervalar m = divisaoIntervalar(matriz[k * n + i], matriz[i * n + i]);

                        matriz[k * n + i].menor = 0.0;
                        matriz[k * n + i].maior = 0.0;

                        for (long long j = i + 1; j < n; ++j)
                                matriz[k * n + j] = subtracaoIntervalar(matriz[k * n + j], multiplicacaoIntervalar(matriz[i * n + j], m));
                        b[k] = subtracaoIntervalar(b[k], multiplicacaoIntervalar(b[i], m));
                }
        }
}
