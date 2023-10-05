#include "libIntervalar.h"

NumIntervalar *criarVetorIntervalar(uint n);

void destruirVetorIntervalar(NumIntervalar *vetor);

//void lerVetor(double *vetor, uint n);

void imprimirVetorIntervalar(NumIntervalar *vetor, uint n);

void destruirMatrizIntervalar(NumIntervalar **matriz, uint n);

//Le uma matriz quadrada de ordem 'n'
void lerMatrizIntervalar(NumIntervalar **matriz, uint n);

//Imprime uma matriz quadrada de ordem 'n'
void imprimirMatrizIntervalar(NumIntervalar **matriz, uint n);

void copiarMatriz(NumIntervalar **original, NumIntervalar **nova, uint n);

//Imprime um sistema linear
void imprimirSistemaNumIntervalar(NumIntervalar **matriz, NumIntervalar *vetor, uint n);

//Encontra o valor maximo em uma coluna 'i' 
uint encontraMaxIntervalar(NumIntervalar **matriz, uint n, uint i);

void retrossubsIntervalar(NumIntervalar **matriz, NumIntervalar *b, NumIntervalar *x, uint n);

//Troca as linhas 'i' e 'pivo'
void trocaLinhaIntervalar(NumIntervalar **matriz, uint n, NumIntervalar *b, int i, uint pivo);

void eliminacaoGauss(NumIntervalar **matriz, NumIntervalar *b, uint n);
