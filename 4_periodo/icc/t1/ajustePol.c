#include <stdio.h>
#include <stdlib.h>
#include "libSistemaIntervalar.h"


double *criarVetorDouble(uint n) {

        double *vetorDouble = malloc(sizeof(double) * n);

        if (!vetorDouble)
                return NULL;

        return vetorDouble;
}

void lerEntrada(double *vetorX, double *vetorY, uint n) {
         
        for (uint i = 0; i < n; i++) {
                scanf("%lf %lf", &vetorX[i], &vetorY[i]);
        }
}

void gerarSistemaIntervalar(NumIntervalar **matriz, NumIntervalar *vetorX, NumIntervalar *vetorY, NumIntervalar *vetorB, uint n, uint k) {

        for (uint i = 0; i < k; i++) {
                NumIntervalar tmp;
                for (uint j = 0; j < k; j++) {
                        tmp.menor = 0;
                        tmp.maior = 0;
                        for (uint l = 0; l < n; l++) {
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
                for (uint m = 0; m < n; m++) {
                        tmpX = expIntervalar(vetorX[m], i);
                        tmp = somaIntervalar(tmp, multiplicacaoIntervalar(vetorY[m], tmpX)); 
                }
                vetorB[i] = tmp;
        }
}

int main() {

        uint n, k;
        double *vetorX, *vetorY;

        scanf("%u %u", &n, &k);

        vetorX = criarVetorDouble(n);
        vetorY = criarVetorDouble(n);

        lerEntrada(vetorX, vetorY, n);

        NumIntervalar *vetorIntervalarX = criarVetorIntervalar(n);
        NumIntervalar *vetorIntervalarY = criarVetorIntervalar(n);
        NumIntervalar *vetorIntervalarB = criarVetorIntervalar(n);
        NumIntervalar **matrizIntervalar = criarMatrizIntervalar(k);

        for (uint i = 0; i < n; i++) {
                vetorIntervalarX[i] = doubleToNumIntervalar(vetorX[i]);
                vetorIntervalarY[i] = doubleToNumIntervalar(vetorY[i]);
        }

        //imprimirVetorIntervalar(vetorIntervalarY, n);

        gerarSistemaIntervalar(matrizIntervalar, vetorIntervalarX, vetorIntervalarY, vetorIntervalarB, n, k);
        imprimirSistemaIntervalar(matrizIntervalar, vetorIntervalarB, k);
        
        printf("\n");

        free(vetorX);
        free(vetorY);
        free(vetorIntervalarX);
        free(vetorIntervalarY);
        free(vetorIntervalarB);
        destruirMatrizIntervalar(matrizIntervalar, k);

        return 0;
}
