#include "libSistemaIntervalar.h"

//Cria um vetor de n elementos do tipo double
double *criarVetorDouble(uint n);

//Lê os pontos xi e yi de entrada colocando seus valores nos vetores vetorX e vetorY
void lerEntrada(double *vetorX, double *vetorY, uint nPontos);

//Calcula os valores de resíduo para cada ponto dos vetores vetorX e vetorY, e preenche o vetorR com eles
void calcularResiduo(NumIntervalar *vetorR, NumIntervalar *vetorCoef, NumIntervalar *vetorX, NumIntervalar *vetorY, uint grau, uint nPontos);

//Gera o sistema linear utilizando o método dos mínimos quadrados.
//Matriz contém os coeficientes, vetorX e vetorY os pontos da entrada e vetorB os termos independentes
void gerarSistemaIntervalar(NumIntervalar **matriz, NumIntervalar *vetorX, NumIntervalar *vetorY, NumIntervalar *vetorB, uint grau, uint nPontos);
