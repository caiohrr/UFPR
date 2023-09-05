#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

double **criarMatriz(unsigned int n) {
        
        double **matriz = malloc(sizeof(double *) * n);
        if (matriz == NULL)
                return NULL;
        for (unsigned int i = 0; i < n; i++) {
                matriz[i] = malloc(sizeof(double) * n);
        }

        return matriz;
}

void destruirMatriz(double **matriz, unsigned int n) {

        for (unsigned int i = 0; i < n; i++) {
                free(matriz[i]);
        }

        free(matriz);
}

//Le uma matriz quadrada de ordem 'n'
void lerMatriz(double **matriz, unsigned int n) {

        for (unsigned int i = 0; i < n; i++) {
                for (unsigned int j = 0; j < n; j++) {
                        scanf("%lf", &matriz[i][j]);
                }
        }
}

//Le uma matriz quadrada de ordem 'n'
void imprimirMatriz(double **matriz, unsigned int n) {

        for (unsigned int i = 0; i < n; i++) {
                for (unsigned int j = 0; j < n; j++) {
                        printf("%.4lf ", matriz[i][j]);
                }
                printf("\n");
        }
}

void imprimirMatrizSolucao(double **matriz, double *vetor, unsigned int n) {

        for (unsigned int i = 0; i < n; i++) {
                for (unsigned int j = 0; j < n; j++) {
                        printf("%.4lf ", matriz[i][j]);
                }

                printf("%.4lf\n", vetor[i]);
        }
}

void retrossubs(double **matriz, double *b, double *x, uint n) {
        for (int i = n - 1; i >= 0; --i) {
                x[i] = b[i];
                for (int j = i+1; j < n; ++j)
                        x[i] -= matriz[i][j] * x[j];
                x[i] /= matriz[i][i];
        }
}

uint encontraMax(double **matriz, uint n, uint i) {

        double max = matriz[i][i];

        for (int j = i + 1; j < n; j++) {
                if (max < matriz[j][i])
                        max = j;
        }

        return max;
}

void trocaLinha(double **matriz, uint n, double *b, int i, uint pivo) {

        double tmp;
        
        for (int j = 0; j < n; j++) {
                tmp = matriz[i][j];
                matriz[i][j] = matriz[pivo][j];
                matriz[pivo][j] = tmp;
        }

}

void eliminacaoGauss(double **matriz, double *b, uint n) {
        /* para cada linha a partir da primeira */
        for (int i = 0; i < n - 1; ++i) {
                uint pivo = encontraMax(matriz, n, i);
                printf("pivo = %u\n", pivo);
                if (i != pivo)
                        trocaLinha(matriz, n, b, i, pivo);
                for(int k = i + 1; k < n; ++k) {
                        double m = matriz[k][i] / matriz[i][i];

                        matriz[k][i] = 0.0;

                        for (int j = i + 1; j < n; ++j)
                                matriz[k][j] -= matriz[i][j] * m;
                        b[k] -= b[i] * m;
                }
        }
}

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
                printf("%.4lf ", vetor[i]);

        printf("\n");
}

int main() {

        unsigned int n;
        double **matriz, *b, *resposta;

        //double b[] = {15.77, -20.49};
        //double b[] = {1, 0, 0};


        scanf("%u", &n);
        matriz = criarMatriz(n);
        b = criarVetor(n);
        resposta = criarVetor(n);

        lerMatriz(matriz, n);
        lerVetor(b, n);

        imprimirMatriz(matriz, n);
        eliminacaoGauss(matriz, b, n);
        retrossubs(matriz, b, resposta, n);

        //imprimirMatriz(matriz, n);
        //imprimirVetor(b, n);
        imprimirMatrizSolucao(matriz, b, n);
        imprimirVetor(resposta, n);

        destruirMatriz(matriz, n);
        destruirVetor(b);
        destruirVetor(resposta);
}
