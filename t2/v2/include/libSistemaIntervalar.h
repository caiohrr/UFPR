//Caio Henrique Ramos Rufino (GRR20224386)
//Frank Wolff Hannemann (GRR20224758)

#include "libIntervalar.h"

//Cria um vetor de números intervalares com 'n' elementos
NumIntervalar *criarVetorIntervalar(long long n);

//Cria uma matriz quadrada de números intervalares de ordem 'n'
NumIntervalar *criarMatrizIntervalar(long long n);

//Libera a memória para um vetor de números intervalares
void destruirVetorIntervalar(NumIntervalar *vetor);

//Imprime um vetor de números intervalares de tamanho 'n' com notação científica
void imprimirVetorIntervalar(NumIntervalar *vetor, long long n);

//Destrói uma matriz quadrada de números intervalares de ordem 'n'
void destruirMatrizIntervalar(NumIntervalar *matriz);

//Le uma matriz quadrada de números intervalares ordem 'n'
void lerMatrizIntervalar(NumIntervalar *matriz, long long n);

//Imprime uma matriz quadrada de ordem 'n'
void imprimirMatrizIntervalar(NumIntervalar *matriz, long long n);

//Copia a matriz origirnal de números intervalares de ordem n
//para a matriz nova
void copiarMatriz(NumIntervalar *original, NumIntervalar *nova, long long n);

//Imprime um sistema linear de números intervalares com notação científica
void imprimirSistemaIntervalar(NumIntervalar *matriz, NumIntervalar *vetor, long long n);

//Encontra a linha que possui o número intervalar de maior valor de
//uma matriz de grau 'n' em uma coluna 'i'
long long encontraMaxIntervalar(NumIntervalar *matriz, long long n, long long i);

//Realiza a retrossubstituição para uma matriz de grau 'n', vetor de termos indepentes b,
//e coloca os valores das incógnitas encontradas no vetor x
void retrossubsIntervalar(NumIntervalar *matriz, NumIntervalar *b, NumIntervalar *x, long long n);

//Troca as linhas 'i' e 'pivo'
void trocaLinhaIntervalar(NumIntervalar *matriz, long long n, NumIntervalar *b, int i, long long pivo);

//Realiza a eliminação de Gauss com pivoteamento parcial para uma matriz de números intervalares
//de ordem 'n' e vetor de termos independentes b
void eliminacaoGauss(NumIntervalar *matriz, NumIntervalar *b, long long n);
