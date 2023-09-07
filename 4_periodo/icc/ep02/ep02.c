#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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

void imprimirMatrizSolucao(double **matriz, double *vetor, uint n) {

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
        
        for (uint j = 0; j < n; j++) {
                tmp2 = b[i];
                b[i] = b[pivo];
                b[pivo] = tmp2;

                tmp = matriz[i][j];
                matriz[i][j] = matriz[pivo][j];
                matriz[pivo][j] = tmp;
        }
}

void eliminacaoGauss(double **matriz, double *b, uint n) {
        /* para cada linha a partir da primeira */
        for (uint i = 0; i < n - 1; ++i) {
                uint pivo = encontraMax(matriz, n, i);
                printf("pivo = %u, i = %u\n", pivo, i);
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
        /* para cada linha a partir da primeira */
        for (uint i = 0; i < n - 1; ++i) {
                uint pivo = encontraMax(matriz, n, i);
                printf("pivo = %u, i = %u\n", pivo, i);
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

void imprimirVetorResposta(double *vetor, uint n) {

        printf("X = [");
        for (uint i = 0; i < n; i++) 
                printf("%.5lf ", vetor[i]);

        printf("]\n");
}

int main() {

        uint n;
        double **matriz, *b, *resposta;

        //double b[] = {15.77, -20.49};
        //double b[] = {1, 0, 0};

        scanf("%u", &n);
        matriz = criarMatriz(n);
        b = criarVetor(n);
        resposta = criarVetor(n);

        lerSistema(matriz, b, n);

        //imprimirMatriz(matriz, n);
        eliminacaoGaussSemPiv(matriz, b, n);
        retrossubs(matriz, b, resposta, n);

        //imprimirMatriz(matriz, n);
        //imprimirVetorResposta(b, n);
        imprimirMatrizSolucao(matriz, b, n);
        imprimirVetorResposta(resposta, n);

        destruirMatriz(matriz, n);
        destruirVetor(b);
        destruirVetor(resposta);
}
