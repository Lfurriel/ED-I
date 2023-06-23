/*13) Implemente uma função que encontra o menor elemento de uma ABB.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int info;
    struct no *esq;
    struct no *dir;
} no;

no *busca_menor(no *raiz) {

    no *busca = raiz;
    while (busca->esq)
        busca = busca->esq;

    return busca;    
}