/* 
Rodrigo Victor          RA: 200897
Natanael Vitorino       RA: 200032

---------------------------------------------------- Método do trapezio ----------------------------------------------------

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tabela
{
    float coef, x, fx, h, result;

} tabela;

void alocaTabela(tabela **pTabela, int tam);
void coletaDados(tabela *pTabela, int grau);
void calculaH(tabela *pTabela, int grau, float menor, float maior, int nDivisoes);
void passoDoX(tabela *pTabela, float menor, float maior, float h, int grau, int nDivisoes);
void calculaFx(tabela *pTabela, int grau, int numDeX, int nDivisoes);
void calculoIntegral(tabela *pTabela, int numDeX, int nDivisoes);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Início que pede a quantidade de pontos, coleta os pontos e verifica o grau da equacao (reta ou parabola) em loop */

int main()
{
    system("color 0A");
    int grau;
    char opc = 's';

    tabela *pTabela = NULL;
    alocaTabela(&pTabela, 1);
    
    do{
        system("cls");
        printf("-------------- Metodo do trapezio --------------\n");
        printf("Digite o grau do polinomio (ate 10): ");
        fflush(stdin); 
        scanf("%d", &grau);
        coletaDados(pTabela, grau);
        printf("\nDeseja informar outra tabela? (S/N)");
        fflush(stdin);
        scanf("%c", &opc);
    } while (opc != 'n' && opc != 'N');
    
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Coleta e armazenamento dos dados inseridos pelo usuário */

void coletaDados(tabela *pTabela, int grau)
{
    int i, nDivisoes;
    char opc = 's';
    float menor, maior, auxIntervalo;
    printf("\n");
    for (i = 0; i <= grau; i++)
    {
        printf("Digite o coeficiente de grau [%d] (x^%d): ", i, i);
        fflush(stdin);
        scanf("%f", &((pTabela + i)->coef));
    }
    printf("\nDigite o intervalo [menor, maior]:\nMenor: ");
    fflush(stdin);
    scanf("%f", &menor);
    printf("\nMaior: ");
    fflush(stdin);
    scanf("%f", &maior);
    if (menor > maior)
    {
        auxIntervalo = menor;
        menor = maior;
        maior = auxIntervalo;
        printf("\nIntervalo corrigido! [MENOR, MAIOR]");
    }
    printf("\n--------------- Intervalo: [%.4f, %.4f] ---------------\n", menor, maior);
    do
    {
        printf("\nDigite o numero de divisoes: ");
        scanf(" %d", &nDivisoes);
        calculaH(pTabela, grau, menor, maior, nDivisoes);
        printf("\n\nDeseja recalcular para outro numero de divisoes? (S/N) ");
        scanf(" %c", &opc);
    } while (opc != 'n' && opc != 'N');
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Calcula o H */

void calculaH(tabela *pTabela, int grau, float menor, float maior, int nDivisoes)
{
    float h;
    h = (maior - menor) / nDivisoes;
    (pTabela->h) = h;
    printf("\nh = (%.4f - %.4f) / %d = %.4f\n\nh = %.4f", maior, menor, nDivisoes, h, h);
    passoDoX(pTabela, menor, maior, h, grau, nDivisoes);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Calcula o passo de X */

void passoDoX(tabela *pTabela, float menor, float maior, float h, int grau, int nDivisoes)
{
    int i, numDeX = ((maior - menor) / h) + 1;
    ((pTabela + 0)->x) = menor;
    ((pTabela + numDeX)->x) = maior;
    for (i = 1; i < numDeX; i++)
    {
        ((pTabela + i)->x) = ((pTabela + i - 1)->x) + h;
    }
    calculaFx(pTabela, grau, numDeX, nDivisoes);
    mostraTabela(pTabela, numDeX, nDivisoes);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Calcula Fx após ter os valores de x */

void calculaFx(tabela *pTabela, int grau, int numDeX, int nDivisoes)
{
    int i, j;
    float aux = 0;
    for (i = 0; i <= numDeX; i++) // Percorre todos os X's
    {
        aux = 0;

        for (j = 0; j <= grau; j++) // Percorre os graus do polinomio a partir do 0
        {
            aux += pow(((pTabela + i)->x), j) * ((pTabela + j)->coef);
        }

        ((pTabela + i)->fx) = aux;
    }
    calculoIntegral(pTabela, numDeX, nDivisoes);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Calulo da Integral */

void calculoIntegral(tabela *pTabela, int numDeX, int nDivisoes){
    int i, j;
    float div, sum = 0, first, last, Itr;

    div = (pTabela->h)/2;

    if(numDeX > 4 && numDeX < 8){                           // Necessario para calcular os valores corretamente 
        for (i = 0; i <= numDeX; i++){
            if(i == 0){
                first = ((pTabela + i)->fx);                // Primeiro valor
            }
            else if(i>0 && i<numDeX){
                sum += ((pTabela + i)->fx);                 // Soma dos valores intermediarios
            }
            else if(i <= numDeX){
                last = ((pTabela + i)->fx);                 // Ultimo valor
            }
        }
    }
    else{
        for (i = 0; i < numDeX; i++){

            if(i == 0){
                first = ((pTabela + i)->fx);                // Primeiro valor
            }
            else if(i>0 && i<(numDeX-1)){
                sum += ((pTabela + i)->fx);                 // Soma dos valores intermediarios
            }
            else if(i < numDeX){
                last = ((pTabela + i)->fx);                 // Ultimo valor
            }

        }
    }

    Itr = div * (first + last + 2 * (sum));                 // Calculo da integracao
    pTabela->result = Itr;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Mostra os X's e F(x)'s */

void mostraTabela(tabela *pTabela, int numDeX, int nDivisoes)
{
    int i;
    printf("\n\n---------------- TABELA ----------------\n  X\t  F(X)\n\n");
    
    for (i = 0; i <= numDeX; i++)
    {
        printf("%.4f\t%.4f\n", (pTabela + i)->x, (pTabela + i)->fx);
    }

    if(nDivisoes==1){
        printf("\nIT = %.4f\n", pTabela->result);
    }
    else{
        printf("\nITR = %.4f\n", pTabela->result);
    }
    
    printf("---------------------------------------------\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Aloca a struct */

void alocaTabela(tabela **pTabela, int tam)
{
    if ((*pTabela = (tabela *)realloc(*pTabela, tam * sizeof(tabela))) == NULL)
    {
        exit(1);
    }
}