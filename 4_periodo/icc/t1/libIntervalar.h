typedef unsigned int uint;

typedef struct NumIntervalar {

        double menor, maior;

} NumIntervalar;

double minDouble(double a, double b);

double maxDouble(double a, double b);

NumIntervalar doubleToNumIntervalar(double num);

double erroAbsoluto(NumIntervalar num);

double erroRelativo(NumIntervalar num);

NumIntervalar somaIntervalar(NumIntervalar n1, NumIntervalar n2);

NumIntervalar subtracaoIntervalar(NumIntervalar n1, NumIntervalar n2);

NumIntervalar multiplicacaoIntervalar(NumIntervalar n1, NumIntervalar n2);

NumIntervalar divisaoIntervalar(NumIntervalar n1, NumIntervalar n2);

NumIntervalar expIntervalar(NumIntervalar n, uint p);

void imprimirNumIntervalar(NumIntervalar num);
