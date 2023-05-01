/*11) Implementa uma função para realizar buscas em uma ABB de números
inteiros. Protótipo: no *busca (no *raiz, int elemento).*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int info;
    struct no *esq;
    struct no *dir;
} no;

no *busca (no *raiz, int elemento) {

    if(!raiz)
        return NULL;
        
    if (elemento == raiz->info)
        return raiz;
        
    if (elemento > raiz->info)
        return busca(raiz->dir, elemento);
        
    return busca(raiz->esq, elemento);
}   