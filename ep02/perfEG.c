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

//Copia o vetor original e coloca seus valores no novo
void copiarVetor(double *original, double *novo, uint n) {

        for (uint i = 0; i < n; i++)
                novo[i] = original[i];
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

//Imprime uma matriz quadrada de ordem 'n'
void imprimirMatriz(double **matriz, uint n) {

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                        printf("%.5lf ", matriz[i][j]);
                }
                printf("\n");
        }
}

void copiarMatriz(double **original, double **nova, uint n) {

        for (uint i = 0; i < n; i++)
                for (uint j = 0; j < n; j++)
                        nova[i][j] = original[i][j];
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

//Imprime um sistema linear
void imprimirSistema(double **matriz, double *vetor, uint n) {

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                        printf("%.5lf ", matriz[i][j]);
                }

                printf("%.5lf\n", vetor[i]);
        }
}

//Imprime o vetor resposta no formato correto
void imprimirVetorResposta(double *vetor, uint n) {

        printf("X = [");
        imprimirVetor(vetor, n);
        printf("]\n");
}

//Encontra o valor maximo em uma coluna 'i' 
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

void retrossubs(double **matriz, double *b, double *x, uint n) {
        for (int i = n - 1; i >= 0; --i) {
                x[i] = b[i];
                for (uint j = i+1; j < n; ++j)
                        x[i] -= matriz[i][j] * x[j];
                x[i] /= matriz[i][i];
        }
}

//Troca as linhas 'i' e 'pivo'
void trocaLinha(double **matriz, uint n, double *b, int i, uint pivo) {

        double tmp, tmp2;

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

        // para cada linha a partir da primeira
        for (uint i = 0; i < n - 1; ++i) {
                uint pivo = encontraMax(matriz, n, i);
                if (i != pivo)
                        trocaLinha(matriz, n, b, i, pivo);

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

        // para cada linha a partir da primeira
        for (uint i = 0; i < n - 1; ++i) {
                uint pivo = encontraMax(matriz, n, i);
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

        for (uint i = 0; i < n - 1; ++i) {
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
                        residuo[i] += matriz[i][j] * resposta[j];
                }
                residuo[i] -= b[i];
        }

        return residuo;
}

//imprime o residuo no formato correto
void imprimirResiduo(double *vetor, uint n) {
        printf("residuo = [");
        imprimirVetor(vetor, n);
        printf("]\n");
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

        copiarMatriz(matriz, matrizAux, n);
        copiarVetor(b, bAux, n);

        double tempo = timestamp();

        LIKWID_MARKER_INIT;
        LIKWID_MARKER_START ("eliminacaoGauss");

        eliminacaoGauss(matrizAux, bAux, n);
        printf("Eliminação de Gauss:\n");

        retrossubs(matrizAux, bAux, resposta, n);
        residuo = calcularResiduo(matrizAux, bAux, resposta, n);
        tempo = timestamp() - tempo;

        LIKWID_MARKER_STOP ("eliminacaoGauss");
        LIKWID_MARKER_CLOSE;

        printf("\n");
        imprimirSistema(matrizAux, bAux, n);
        printf("\n");

        imprimirVetorResposta(resposta, n);
        imprimirResiduo(residuo, n);
        printf("\nTempo: %lf\n", tempo);
        printf("\n===========================================\n\n");

        //Fim primeiro

        copiarMatriz(matriz, matrizAux, n);
        copiarVetor(b, bAux, n);

        tempo = timestamp();

        LIKWID_MARKER_INIT;
        LIKWID_MARKER_START ("eliminacaoGaussSemMult");

        eliminacaoGaussSemMult(matrizAux, bAux, n);
        printf("Eliminação de Gauss (sem multiplicadores):\n");

        retrossubs(matrizAux, bAux, resposta, n);
        residuo = calcularResiduo(matrizAux, bAux, resposta, n);
        tempo = timestamp() - tempo;

        LIKWID_MARKER_STOP ("eliminacaoGaussSemMult");
        LIKWID_MARKER_CLOSE;

        printf("\n");
        imprimirSistema(matrizAux, bAux, n);
        printf("\n");

        imprimirVetorResposta(resposta, n);
        imprimirResiduo(residuo, n);
        printf("\nTempo: %lf\n", tempo);
        printf("\n===========================================\n\n");

        //Fim segundo

        copiarMatriz(matriz, matrizAux, n);
        copiarVetor(b, bAux, n);

        tempo = timestamp();

        LIKWID_MARKER_INIT;
        LIKWID_MARKER_START ("eliminacaoGaussSemPiv");

        eliminacaoGaussSemPiv(matrizAux, bAux, n);
        printf("Eliminação de Gauss (sem pivoteamento):\n");


        retrossubs(matrizAux, bAux, resposta, n);
        residuo = calcularResiduo(matrizAux, bAux, resposta, n);
        tempo = timestamp() - tempo;

        LIKWID_MARKER_STOP ("eliminacaoGaussSemPiv");
        LIKWID_MARKER_CLOSE;

        printf("\n");
        imprimirSistema(matrizAux, bAux, n);
        printf("\n");

        imprimirVetorResposta(resposta, n);
        imprimirResiduo(residuo, n);
        printf("\nTempo: %lf\n", tempo);
        printf("\n===========================================\n\n");

        //Fim terceiro

        destruirMatriz(matriz, n);
        destruirMatriz(matrizAux, n);
        destruirVetor(b);
        destruirVetor(bAux);
        destruirVetor(resposta);
        destruirVetor(residuo);
}
