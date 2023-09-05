#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct NumIntervalar {

        float menor, maior;

} NumIntervalar;

typedef union {

    float f;
    int32_t i;

} Float_t;

int ulpsDiff(float a, float b) {

    Float_t A, B;
    A.f = a;
    B.f = b;
    
    int ulpsDiff = abs(A.i - B.i);

    return ulpsDiff - 1;
}

float minFloat(float a, float b) {
        return (a < b) ? a : b;
}

float maxFloat(float a, float b) {
        return (a > b) ? a : b;
}

NumIntervalar floatToNumIntervalar(float num) {

        NumIntervalar num_inter;

        num_inter.menor = nextafterf(num, num * 2);
        num_inter.maior = nextafterf(num, num / 2);

        return num_inter;
}

float erroAbsoluto(NumIntervalar num) {

        return num.maior - num.menor;
}

float erroRelativo(NumIntervalar num) {

        if (fabs(num.menor) <= FLT_EPSILON)
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
        resultado.menor = minFloat(minFloat(n1.menor * n2.menor, n1.menor * n2.maior), minFloat(n1.maior * n2.menor, n1.maior * n2.maior));
        resultado.maior = maxFloat(maxFloat(n1.menor * n2.menor, n1.menor * n2.maior), maxFloat(n1.maior * n2.menor, n1.maior * n2.maior));

        return resultado; 
}

NumIntervalar divisaoIntervalar(NumIntervalar n1, NumIntervalar n2) {

        NumIntervalar resultado;

        if (n2.menor < 0 && n2.maior > 0) {
                resultado.menor = -INFINITY;
                resultado.maior = INFINITY;
        } else {

                NumIntervalar tmp = n2;
                float tmp2;

                tmp2 = tmp.menor;
                tmp.menor = 1 / tmp.maior;
                tmp.maior = 1 / tmp2;

                resultado = multiplicacaoIntervalar(n1, tmp);
        }

        return resultado; 
}

void imprimirNumIntervalar(NumIntervalar num) {
        printf("[%1.8e, %1.8e]", num.menor, num.maior);
}

int main() {

        float x[5];
        char op[4];

        scanf("%f %c %f %c %f %c %f %c %f", &x[0], &op[0], &x[1], &op[1], &x[2], &op[2], &x[3], &op[3], &x[4]);
        
        NumIntervalar a, b;
        
        a = floatToNumIntervalar(x[0]);
        for (int i = 0; i < 4; i++) {

                printf("%d:\n", i + 1);
                b = floatToNumIntervalar(x[i + 1]);

                imprimirNumIntervalar(a);
                printf(" %c ", op[i]);
                imprimirNumIntervalar(b);
                printf(" =\n");

                switch (op[i]) {
                        case '+':
                                a = somaIntervalar(a, b);
                        break;

                        case '-':
                                a = subtracaoIntervalar(a, b);
                        break;

                        case '*':
                                a = multiplicacaoIntervalar(a, b);
                        break;

                        case '/':
                                a = divisaoIntervalar(a, b);
                        break;

                }

                imprimirNumIntervalar(a);
                printf("\nEA: %1.8e; ER: %1.8e; ULPs: %d\n\n", erroAbsoluto(a), erroRelativo(a), ulpsDiff(a.menor, a.maior));
        }

        //printf("%1.8e %c %1.8e %c %1.8e %c %1.8e %c %1.8e\n", x1, o1, x2, o2, x3, o3, x4, o4, x5);

        return 0;
}
