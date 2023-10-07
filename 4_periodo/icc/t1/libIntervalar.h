typedef unsigned int uint;

//Estrutura que contém o intervalo numérico, menor é o início e maior é o fim do intervalo
typedef struct NumIntervalar {

        double menor, maior;

} NumIntervalar;

//Retorna o menor valor entre a e b
double minDouble(double a, double b);

//Retorna o maior valor entre a e b
double maxDouble(double a, double b);

//Retorna a representação intervalar de um double
NumIntervalar doubleToNumIntervalar(double num);

//Retorna o erro absoluto entre o início e o fim do intervalo de num
double erroAbsoluto(NumIntervalar num);

//Retorna o erro relativo entre o início e o fim do intervalo de num
double erroRelativo(NumIntervalar num);

//Retorna a soma intervalar de n1 e n2
NumIntervalar somaIntervalar(NumIntervalar n1, NumIntervalar n2);

//Retorna a subtração intervalar de n1 e n2
NumIntervalar subtracaoIntervalar(NumIntervalar n1, NumIntervalar n2);

//Retorna a multiplicação intervalar de n1 e n2
NumIntervalar multiplicacaoIntervalar(NumIntervalar n1, NumIntervalar n2);

//Retorna a divisão intervalar de n1 e n2
NumIntervalar divisaoIntervalar(NumIntervalar n1, NumIntervalar n2);

//Retorna o valor intervalar de n elevado a p
NumIntervalar expIntervalar(NumIntervalar n, uint p);

//Imprime um número intervalar usando notação científica
void imprimirNumIntervalar(NumIntervalar num);
