#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdint.h>
#include <stdlib.h>
#include "libIntervalar.h"

double minDouble(double a, double b) {
        return (a < b) ? a : b;
}

double maxDouble(double a, double b) {
        return (a > b) ? a : b;
}

NumIntervalar doubleToNumIntervalar(double num) {

        NumIntervalar num_inter;

        num_inter.menor = nextafterf(num, num * 2);
        num_inter.maior = nextafterf(num, num / 2);

        return num_inter;
}

double erroAbsoluto(NumIntervalar num) {

        return num.maior - num.menor;
}

double erroRelativo(NumIntervalar num) {

        if (fabs(num.menor) <= DBL_EPSILON)
                return 0;

        return (num.maior - num.menor) / num.menor;
}

NumIntervalar somaIntervalar(NumIntervalar n1, NumIntervalar n2) {

        NumIntervalar resultado;

        resultado.menor = n1.menor + n2.menor;
        resultado.maior = n1.maior + n2.maior;

        return resultado; 
}

NumIntervalar subtracaoIntervalar(NumIntervalar n1, NumIntervalar n2) {

        NumIntervalar resultado;
        resultado.menor = n1.menor - n2.menor;
        resultado.maior = n1.maior - n2.maior;

        return resultado; 
}

NumIntervalar multiplicacaoIntervalar(NumIntervalar n1, NumIntervalar n2) {

        NumIntervalar resultado;
        resultado.menor = minDouble(minDouble(n1.menor * n2.menor, n1.menor * n2.maior), minDouble(n1.maior * n2.menor, n1.maior * n2.maior));
        resultado.maior = maxDouble(maxDouble(n1.menor * n2.menor, n1.menor * n2.maior), maxDouble(n1.maior * n2.menor, n1.maior * n2.maior));

        return resultado; 
}

NumIntervalar divisaoIntervalar(NumIntervalar n1, NumIntervalar n2) {

        NumIntervalar resultado;

        if (n2.menor < 0 && n2.maior > 0) {
                resultado.menor = -INFINITY;
                resultado.maior = INFINITY;
        } else {

                NumIntervalar tmp = n2;
                double tmp2;

                tmp2 = tmp.menor;
                tmp.menor = 1 / tmp.maior;
                tmp.maior = 1 / tmp2;

                resultado = multiplicacaoIntervalar(n1, tmp);
        }

        return resultado; 
}

NumIntervalar expIntervalar(NumIntervalar n, uint p) {

        NumIntervalar resultado;
        
        if (p == 0) {
                resultado.menor = resultado.maior = 0;
        } else if ((p % 2 != 0) || (n.menor >= 0)) {
                resultado.menor = pow(n.menor, p);
                resultado.maior = pow(n.maior, p);
        } else if (n.maior < 0) { 
                resultado.menor = pow(n.maior, p);
                resultado.maior = pow(n.menor, p);
        } else {
                resultado.menor = 0;
                resultado.maior = maxDouble(pow(n.menor, p), pow(n.maior, p));
        }

        return resultado;
}


void imprimirNumIntervalar(NumIntervalar num) {
        printf("[%1.8e, %1.8e]", num.menor, num.maior);
}
