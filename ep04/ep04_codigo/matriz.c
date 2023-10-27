#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // Para uso de função 'memset()'

#include "matriz.h"

/**
 * Função que gera valores para para ser usado em uma matriz
 * @param i,j coordenadas do elemento a ser calculado (0<=i,j<n)
*  @return valor gerado para a posição i,j
  */
static inline real_t generateRandomA( unsigned int i, unsigned int j) {
        static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
        return ( (i==j) ? (real_t)(BASE<<1) : 1.0 )  * (real_t)random() * invRandMax;
}

/**
 * Função que gera valores aleatórios para ser usado em um vetor
 * @return valor gerado
 *
 */
static inline real_t generateRandomB() {
        static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
        return (real_t)(BASE<<2) * (real_t)random() * invRandMax;
}



/* ----------- FUNÇÕES ---------------- */

/**
 *  Funcao geraMatRow: gera matriz como vetor único, 'row-oriented'
 * 
 *  @param m     número de linhas da matriz
 *  @param n     número de colunas da matriz
 *  @param zerar se 0, matriz  tem valores aleatórios, caso contrário,
 *               matriz tem valores todos nulos
 *  @return  ponteiro para a matriz gerada
 *
 */

MatRow geraMatRow (int m, int n, int zerar) {
        MatRow matriz = (real_t *) malloc(m*n*sizeof(real_t));

        if (matriz) {
                if (zerar)
                        memset(matriz,0,m*n*sizeof(real_t));
                else
                        for (int i=0; i < m; ++i)
                        for (int j=0; j < n; ++j)
                                matriz[i*n + j] = generateRandomA(i, j);
        }

        return (matriz);
}


/**
 *  Funcao geraVetor: gera vetor de tamanho 'n'
 * 
 *  @param n  número de elementos do vetor
 *  @param zerar se 0, vetor  tem valores aleatórios, caso contrário,
 *               vetor tem valores todos nulos
 *  @return  ponteiro para vetor gerado
 *
 */

Vetor geraVetor (int n, int zerar) {
        Vetor vetor = (real_t *) malloc(n*sizeof(real_t));

        if (vetor) {
                if (zerar)
                        memset(vetor,0,n*sizeof(real_t));
                else
                        for (int i=0; i < n; ++i)
                        vetor[i] = generateRandomB();
        }
        return (vetor);
}

/**
 *  \brief: libera vetor
 * 
 *  @param  ponteiro para vetor
 *
 */
void liberaVetor (void *vet) {
        free(vet);
}


/**
 *  Funcao multMatVet:  Efetua multiplicacao entre matriz 'mxn' por vetor
 *                       de 'n' elementos
 *  @param mat matriz 'mxn'
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *  @param res vetor que guarda o resultado. Deve estar previamente alocado e com
 *             seus elementos inicializados em 0.0 (zero)
 *  @return vetor de 'm' elementos
 *
 */

void multMatVet(MatRow mat, Vetor v, int m, int n, Vetor res) {

        /* Efetua a multiplicação */
        if (res) {
                for (int i = 0; i < m; ++i)
                        for (int j = 0; j < n; ++j)
                                res[i] += mat[n * i + j] * v[j];
        }
}

void multMatVetV2(MatRow mat, Vetor v, int m, int n, Vetor res) {
        if (res) {
                int i, j;

                for (i = 0; i < m - m % 4; i += 4) {
                        for (j = 0; j < n; j++) {
                                res[i] += mat[n * i + j] * v[j];
                                res[i + 1] += mat[n * (i + 1) + j] * v[j];
                                res[i + 2] += mat[n * (i + 2) + j] * v[j];
                                res[i + 3] += mat[n * (i + 3) + j] * v[j];
                        }
                }

                for (; i < m; i++) {
                        for (j = 0; j < n; j++) {
                                res[i] += mat[n * i + j] * v[j];
                        }
                }
        }
}


/**
 *  Funcao multMatMat: Efetua multiplicacao de duas matrizes 'n x n' 
 *  @param A matriz 'n x n'
 *  @param B matriz 'n x n'
 *  @param n ordem da matriz quadrada
 *  @param C   matriz que guarda o resultado. Deve ser previamente gerada com 'geraMatPtr()'
 *             e com seus elementos inicializados em 0.0 (zero)
 *
 */

void multMatMat (MatRow A, MatRow B, int n, MatRow C) {
        /* Efetua a multiplicação */
        for (int i=0; i < n; ++i)
                for (int j=0; j < n; ++j)
                        for (int k=0; k < n; ++k)
                                C[i*n+j] += A[i*n+k] * B[k*n+j];
}

//void multMatMatV2(MatRow A, MatRow B, int n, MatRow C, int blockSize) {
//        //int blockSize = 8;  // Choose an appropriate block size based on your architecture
//
//        for (int i = 0; i < n; i += blockSize) {
//                for (int j = 0; j < n; j += blockSize) {
//                        for (int k = 0; k < n; k += blockSize) {
//                                for (int ii = i; ii < i + blockSize && ii < n; ++ii) {
//                                        for (int jj = j; jj < j + blockSize && jj < n; jj += 1) {
//                                                C[ii * n + jj] = 0.0;
//                                                //C[ii * n + jj + 1] = 0.0;
//                                                //C[ii * n + jj + 2] = 0.0;
//                                                //C[ii * n + jj + 3] = 0.0;
//                                                for (int kk = k; kk < k + blockSize && kk < n; ++kk) {
//                                                        C[ii * n + jj] += A[ii * n + kk] * B[kk * n + jj];
//                                                        //C[ii * n + jj] += A[ii * n + kk] * B[kk * n + jj];
//                                                        //C[ii * n + jj] += A[ii * n + kk] * B[kk * n + jj];
//                                                        //C[ii * n + jj] += A[ii * n + kk] * B[kk * n + jj];
//                                                }
//                                        }
//                                }
//                        }
//                }
//        }
//}

void multMatMatV2(MatRow A, MatRow B, int n, MatRow C, int blockSize) {
        //int blockSize = 8;  // Choose an appropriate block size based on your architecture

        for (int i = 0; i < n; i += blockSize) {
                for (int j = 0; j < n; j += blockSize) {
                        for (int k = 0; k < n; k += blockSize) {
                                for (int ii = i; ii < i + blockSize && ii < n; ++ii) {
                                        for (int jj = j; jj < j + blockSize && jj < n - (n % 4); jj += 4) {
                                                C[ii * n + jj] = 0.0;
                                                C[ii * n + jj + 1] = 0.0;
                                                C[ii * n + jj + 2] = 0.0;
                                                C[ii * n + jj + 3] = 0.0;
                                                for (int kk = k; kk < k + blockSize && kk < n; ++kk) {
                                                        C[ii * n + jj] += A[ii * n + kk] * B[kk * n + jj];
                                                        C[ii * n + jj + 1] += A[ii * n + kk] * B[kk * n + jj + 1];
                                                        C[ii * n + jj + 2] += A[ii * n + kk] * B[kk * n + jj + 2];
                                                        C[ii * n + jj + 3] += A[ii * n + kk] * B[kk * n + jj + 3];
                                                }
                                        }
                                }
                        }
                }
        }
}

void multMatMatV2_2(MatRow A, MatRow B, MatRow C, int N, int M, int K) {
    const int block_size = 128 / sizeof(double); // 64 = common cache line size

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            C[K * i + j] = 0;
        }
    }

    for (int i0 = 0; i0 < N; i0 += block_size) {
        int imax = i0 + block_size > N ? N : i0 + block_size;

        for (int j0 = 0; j0 < K; j0 += block_size) {
            int jmax = j0 + block_size > K ? K : j0 + block_size;

            for (int k0 = 0; k0 < M; k0 += block_size) {
                int kmax = k0 + block_size > M ? M : k0 + block_size;

                for (int i1 = i0; i1 < imax; i1++) {
                    for (int j1 = j0; j1 < jmax; j1++) {
                        double sum = 0;

                        for (int k1 = k0; k1 < kmax; k1++) {
                            sum += A[i1 * M + k1] * B[k1 * K + j1];
                        }

                        C[i1 * K + j1] += sum;
                    }
                }
            }
        }
    }
}


//void multMatMatV2_2(MatRow A , MatRow B, MatRow C, int N, int M, int K) {
//        const int block_size = 128 / sizeof(double); // 64 = common cache line size
//        for (int i = 0; i < N; i++) {
//                for(int j = 0; j < K; j++) {
//                        C[K * i + j] = 0;
//                }
//        }
//        for (int i0 = 0; i0 < N; i0 += block_size) {
//                int imax = i0 + block_size > N ? N : i0 + block_size;
//
//                for (int j0 = 0; j0 < M; j0 += block_size) {
//                        int jmax = j0 + block_size > M ? M : j0 + block_size;
//
//                        for (int k0 = 0; k0 < K; k0 += block_size) {
//                                int kmax = k0 + block_size > K ? K : k0 + block_size;
//
//                                for (int j1 = j0; j1 < jmax; ++j1) {
//                                        int sj = M * j1;
//
//                                        for (int i1 = i0; i1 < imax; ++i1) {
//                                                int mi = M * i1;
//                                                int ki = K * i1;
//                                                int kij = ki + j1;
//
//                                                for (int k1 = k0; k1 < kmax; ++k1) {
//                                                        C[kij] += A[mi + k1] * B[sj + k1];
//                                                }
//                                        }
//                                }
//                        }
//                }
//        }
//}


/**
 *  Funcao prnMat:  Imprime o conteudo de uma matriz em stdout
 *  @param mat matriz
 *  @param m número de linhas da matriz
 *  @param n número de colunas da matriz
 *
 */

void prnMat (MatRow mat, int m, int n) {
        for (int i=0; i < m; ++i) {
                for (int j=0; j < n; ++j)
                        printf(DBL_FIELD, mat[n*i + j]);
                printf("\n");
        }
        printf(SEP_RES);
}

/**
 *  Funcao prnVetor:  Imprime o conteudo de vetor em stdout
 *  @param vet vetor com 'n' elementos
 *  @param n número de elementos do vetor
 *
 */

void prnVetor (Vetor vet, int n) {
        for (int i=0; i < n; ++i)
                printf(DBL_FIELD, vet[i]);
        printf(SEP_RES);
}

