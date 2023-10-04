#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "utils.h"
#include "likwid.h"

NumIntervalar *criarVetorIntervalar(uint n) {
        NumIntervalar *vetor = malloc(sizeof(NumIntervalar) * n);
        if (vetor == NULL)
                return NULL;
        return vetor;
}

void destruirVetorIntervalar(NumIntervalar *vetor) {
        free(vetor);
}

//void lerVetor(double *vetor, uint n) {
//        for (uint i = 0; i < n; i++)
//                scanf("%lf", &vetor[i]);
//}

void imprimirVetorIntervalar(NumIntervalar *vetor, uint n) {

        for (uint i = 0; i < n; i++) 
                printf("[%.5lf, %.5lf]", vetor[i].menor, vetor[i].maior);
}

//Copia o vetor original e coloca seus valores no novo
void copiarVetorIntervalar(NumIntervalar *original, NumIntervalar *novo, uint n) {

        for (uint i = 0; i < n; i++) {
                novo.menor[i] = original.menor[i];
                novo.maior[i] = original.maior[i];
        }
}

double **criarMatrizIntervalar(uint n) {

        double **matriz = malloc(sizeof(NumIntervalar *) * n);
        if (matriz == NULL)
                return NULL;
        for (uint i = 0; i < n; i++) {
                matriz[i] = malloc(sizeof(NumIntervalar) * n);
        }

        return matriz;
}

void destruirMatrizIntervalar(NumIntervalar **matriz, uint n) {

        for (uint i = 0; i < n; i++) {
                free(matriz[i]);
        }

        free(matriz);
}

//Le uma matriz quadrada de ordem 'n'
void lerMatrizIntervalar(NumIntervalar **matriz, uint n) {

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                        scanf("%lf %lf", &matriz[i][j].menor, &matriz[i][j].maior);
                }
        }
}

//Imprime uma matriz quadrada de ordem 'n'
void imprimirMatrizIntervalar(NumIntervalar **matriz, uint n) {

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                        printf("[%.5lf %.5lf]", matriz[i][j].menor, matriz[i][j].maior);
                }
                printf("\n");
        }
}

void copiarMatriz(NumIntervalar **original, NumIntervalar **nova, uint n) {

        for (uint i = 0; i < n; i++)
                for (uint j = 0; j < n; j++)
                        nova[i][j].menor = original[i][j].menor;
                        nova[i][j].maior = original[i][j].maior;
}

//Imprime um sistema linear
void imprimirSistemaNumIntervalar(NumIntervalar **matriz, NumIntervalar *vetor, uint n) {

        for (uint i = 0; i < n; i++) {
                for (uint j = 0; j < n; j++) {
                        printf("[%.5lf %.5lf]", matriz[i][j].menor, matriz[i][j].maior);
                }

                printf("[%.5lf %.5lf]\n", vetor[i].menor, vetor[i].maior);
        }
}

//Encontra o valor maximo em uma coluna 'i' 
uint encontraMaxIntervalar(NumIntervalar i **matriz, uint n, uint i) {

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

//Troca as linhas 'i' e 'pivo'
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
                        double m = divisaoIntervalar(matriz[k][i], matriz[i][i]);

                        matriz[k][i].menor = 0.0;
                        matriz[k][i].maior = 0.0;

                        for (uint j = i + 1; j < n; ++j)
                                matriz[k][j] = subtracaoIntervalar(matriz[k][j], multiplicacaoIntervalar(matriz[i][j], m));
                        b[k] -= b[i] * m;
                        b[k] = subtracaoIntervalar(b[k], multiplicacaoIntervalar(b[i], m));
                }
        }
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
