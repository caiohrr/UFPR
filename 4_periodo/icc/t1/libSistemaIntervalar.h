#include "libIntervalar.h"

//Cria um vetor de números intervalares com 'n' elementos
NumIntervalar *criarVetorIntervalar(uint n);

//Cria uma matriz quadrada de números intervalares de ordem 'n'
NumIntervalar **criarMatrizIntervalar(uint n);

//Libera a memória para um vetor de números intervalares
void destruirVetorIntervalar(NumIntervalar *vetor);

//Imprime um vetor de números intervalares de tamanho 'n' com notação científica
void imprimirVetorIntervalar(NumIntervalar *vetor, uint n);

//Destrói uma matriz quadrada de números intervalares de ordem 'n'
void destruirMatrizIntervalar(NumIntervalar **matriz, uint n);

//Le uma matriz quadrada de números intervalares ordem 'n'
void lerMatrizIntervalar(NumIntervalar **matriz, uint n);

//Imprime uma matriz quadrada de ordem 'n'
void imprimirMatrizIntervalar(NumIntervalar **matriz, uint n);

//Copia a matriz origirnal de números intervalares de ordem n
//para a matriz nova
void copiarMatriz(NumIntervalar **original, NumIntervalar **nova, uint n);

//Imprime um sistema linear de números intervalares com notação científica
void imprimirSistemaIntervalar(NumIntervalar **matriz, NumIntervalar *vetor, uint n);

//Encontra a linha que possui o número intervalar de maior valor de
//uma matriz de grau 'n' em uma coluna 'i'
uint encontraMaxIntervalar(NumIntervalar **matriz, uint n, uint i);

//Realiza a retrossubstituição para uma matriz de grau 'n', vetor de termos indepentes b,
//e coloca os valores das incógnitas encontradas no vetor x
void retrossubsIntervalar(NumIntervalar **matriz, NumIntervalar *b, NumIntervalar *x, uint n);

//Troca as linhas 'i' e 'pivo'
void trocaLinhaIntervalar(NumIntervalar **matriz, uint n, NumIntervalar *b, int i, uint pivo);

//Realiza a eliminação de Gauss com pivoteamento parcial para uma matriz de números intervalares
//de ordem 'n' e vetor de termos independentes b
void eliminacaoGauss(NumIntervalar **matriz, NumIntervalar *b, uint n);
