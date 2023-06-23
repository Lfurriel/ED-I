/*12) Implemente uma função que realiza a Busca + inserção de um número
inteiro na ABB. Protótipo: no *busca_insere (no *raiz, int elemento).*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int info;
    struct no *esq;
    struct no *dir;
} no;

no *busca_insere (no *raiz, int elemento) {
    if(!raiz) {
        raiz = malloc(sizeof(no));
        raiz->esq = raiz->dir = NULL;
        raiz->info = elemento;

        return raiz;
    }

    if(elemento > raiz->info)
        raiz->dir = busca_insere(raiz->dir, elemento);
    if(elemento < raiz->esq)
        raiz->esq = busca_insere(raiz->esq, elemento);

    return raiz;
}