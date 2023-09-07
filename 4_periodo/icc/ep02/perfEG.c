#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "utils.h"
#include "likwid.h"


double *criarVetor(uint n) {
        double *vetor = malloc(sizeof(double) * n);
        if (vetor == NULL)
                return NULL;
        return vetor;

}

double **criarMatriz(uint n) {
        
        double **matriz = malloc(sizeof(double *) * n);
        if (matriz == NULL)
                return NULL;
        for (uint i = 0; i < n; i++) {
                matriz[i] = malloc(sizeof(double) * n);
        }

        return matriz;
}

void destruirMatriz(double **matriz, uint n) {

        for (uint i = 0; i < n; i++) {
                free(matriz[i]);
        }

        free(matriz);
}

//Le uma matriz quadrada de ordem 'n'
void lerMatriz(double **matriz, uint n) {

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                        scanf("%lf", &matriz[i][j]);
                }
        }
}

//Le uma matriz quadrada de ordem 'n'
void lerSistema(double **matriz, double *vetor,  uint n) {

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                        scanf("%lf", &matriz[i][j]);
                }
                scanf("%lf", &vetor[i]);
        }
}

//Le uma matriz quadrada de ordem 'n'
void imprimirMatriz(double **matriz, uint n) {

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                        printf("%.5lf ", matriz[i][j]);
                }
                printf("\n");
        }
}

void imprimirSistema(double **matriz, double *vetor, uint n) {

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                        printf("%.5lf ", matriz[i][j]);
                }

                printf("%.5lf\n", vetor[i]);
        }
}

void retrossubs(double **matriz, double *b, double *x, uint n) {
        for (int i = n - 1; i >= 0; --i) {
                x[i] = b[i];
                for (uint j = i+1; j < n; ++j)
                        x[i] -= matriz[i][j] * x[j];
                x[i] /= matriz[i][i];
        }
}

uint encontraMax(double **matriz, uint n, uint i) {

        double max = matriz[i][i];
        uint linha = i; 

        for (uint j = i + 1; j < n; j++) {
                if (max < matriz[j][i]) {
                        max = matriz[j][i];
                        linha = j;
                }
        }

        return linha;
}

void trocaLinha(double **matriz, uint n, double *b, int i, uint pivo) {

        double tmp, tmp2;

        //printf("\nb[i] = %lf, b[pivo] = %lf\n", b[i], b[pivo]);
        tmp2 = b[i];
        b[i] = b[pivo];
        b[pivo] = tmp2;

        for (uint j = 0; j < n; j++) {
                tmp = matriz[i][j];
                matriz[i][j] = matriz[pivo][j];
                matriz[pivo][j] = tmp;
        }
}

void eliminacaoGauss(double **matriz, double *b, uint n) {
        /* para cada linha a partir da primeira */
        for (uint i = 0; i < n - 1; ++i) {
                uint pivo = encontraMax(matriz, n, i);
                //printf("pivo = %u, i = %u\n", pivo, i);
                if (i != pivo) {
                        trocaLinha(matriz, n, b, i, pivo);
                        //printf("chamou");
                }
                for(uint k = i + 1; k < n; ++k) {
                        double m = matriz[k][i] / matriz[i][i];

                        matriz[k][i] = 0.0;

                        for (uint j = i + 1; j < n; ++j)
                                matriz[k][j] -= matriz[i][j] * m;
                        b[k] -= b[i] * m;
                }
        }
}

void eliminacaoGaussSemMult(double **matriz, double *b, uint n) {
        /* para cada linha a partir da primeira */
        for (uint i = 0; i < n - 1; ++i) {
                uint pivo = encontraMax(matriz, n, i);
                //printf("pivo = %u, i = %u\n", pivo, i);
                if (i != pivo)
                        trocaLinha(matriz, n, b, i, pivo);
                for (uint k = i + 1; k < n; ++k) {

                        for (uint j = i + 1; j < n; ++j)
                                matriz[k][j] = matriz[k][j]*matriz[i][i] - matriz[i][j]*matriz[k][i];
                b[k] = b[k]*matriz[i][i] - b[i]*matriz[k][i];
                }
        }
}

void eliminacaoGaussSemPiv(double **matriz, double *b, uint n) {
        /* para cada linha a partir da primeira */
        for (uint i = 0; i < n - 1; ++i) {
                //uint pivo = encontraMax(matriz, n, i);
                //printf("pivo = %u, i = %u\n", pivo, i);
                //if (i != pivo)
                        //trocaLinha(matriz, n, b, i, pivo);
                for(uint k = i + 1; k < n; ++k) {
                        double m = matriz[k][i] / matriz[i][i];

                        matriz[k][i] = 0.0;

                        for (uint j = i + 1; j < n; ++j)
                                matriz[k][j] -= matriz[i][j] * m;
                        b[k] -= b[i] * m;
                }
        }
}

double *calcularResiduo(double **matriz, double *b, double *resposta, uint n) {

        double *residuo = criarVetor(n);

        for (uint i = 0; i < n; i++) {
                residuo[i] = 0;
                for (uint j = 0; j < n; j++) {
                        //printf("m = %lf x = %lf\n", matriz[i][j], resposta[i]);
                        residuo[i] += matriz[i][j] * resposta[j];
                }
                residuo[i] -= b[i];
                //printf("residuo = %lf\n", residuo[i]);
        }

        return residuo;
}

void destruirVetor(double *vetor) {
        free(vetor);
}

void lerVetor(double *vetor, uint n) {

        for (uint i = 0; i < n; i++)
                scanf("%lf", &vetor[i]);
}

void imprimirVetor(double *vetor, uint n) {

        for (uint i = 0; i < n; i++) 
                printf("%.5lf ", vetor[i]);
}

void imprimirVetorResposta(double *vetor, uint n) {

        printf("X = [");
        imprimirVetor(vetor, n);
        printf("]\n");
}

void imprimirResiduo(double *vetor, uint n) {
        printf("residuo = [");
        imprimirVetor(vetor, n);
        printf("]\n");
}

void copiarMatriz(double **original, double **nova, uint n) {

        for (uint i = 0; i < n; i++)
                for (uint j = 0; j < n; j++)
                        nova[i][j] = original[i][j];
}

void copiarVetor(double *original, double *novo, uint n) {

        for (uint i = 0; i < n; i++)
                novo[i] = original[i];
}

int main() {

        uint n;
        double **matriz, **matrizAux, *b, *bAux, *resposta, *residuo;

        scanf("%u", &n);
        matriz = criarMatriz(n);
        matrizAux = criarMatriz(n);
        b = criarVetor(n);
        bAux = criarVetor(n);
        resposta = criarVetor(n);

        lerSistema(matriz, b, n);

        for (int i = 0; i < 3; i++) {

                copiarMatriz(matriz, matrizAux, n);
                copiarVetor(b, bAux, n);
                
                double tempo = timestamp();

                LIKWID_MARKER_INIT;
                LIKWID_MARKER_START ("Teste_LIKWID");

                switch (i) {

                case 0:
                        eliminacaoGauss(matrizAux, bAux, n);
                        printf("Eliminação de Gauss:\n");
                        break;

                case 1:
                        eliminacaoGaussSemMult(matrizAux, bAux, n);
                        printf("Eliminação de Gauss (sem multiplicadores):\n");
                        break;

                case 2:
                        eliminacaoGaussSemPiv(matrizAux, bAux, n);
                        printf("Eliminação de Gauss (sem pivoteamento):\n");
                        break;
                }

                retrossubs(matrizAux, bAux, resposta, n);
                residuo = calcularResiduo(matrizAux, bAux, resposta, n);
                tempo = timestamp() - tempo;

                LIKWID_MARKER_STOP ("Teste_LIKWID");
                LIKWID_MARKER_CLOSE;

                printf("\n");
                imprimirSistema(matrizAux, bAux, n);
                printf("\n");

                imprimirVetorResposta(resposta, n);
                imprimirResiduo(residuo, n);
                printf("\nTempo: %lf\n", tempo);
                printf("\n===========================================\n\n");
        }

        destruirMatriz(matriz, n);
        destruirMatriz(matrizAux, n);
        destruirVetor(b);
        destruirVetor(bAux);
        destruirVetor(resposta);
        destruirVetor(residuo);
}
