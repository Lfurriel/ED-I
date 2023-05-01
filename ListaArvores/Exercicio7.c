/*7)  Escreva  uma  função  que  verifique  se  uma  árvore  binária  é cheia.  Definição:
uma  AB  é  dita  cheia  se  todos  os  seus  nós  têm  exatamente  0  ou  2  filhos
(estritamente binária), e todas as folhas estão no mesmo nível. */

#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int info;
    struct no *esq;
    struct no *dir;
} no;

int cheia(no *raiz) {

    if (!raiz)
        return 0;

    if ((raiz->esq && !(raiz->dir)) || (raiz->dir && !(raiz->esq)))
        return 0;

    int altura_esq, altura_dir;
    altura_esq = calcula_altura(raiz->esq);
    altura_dir = calcula_altura(raiz->dir);

    if (altura_esq != altura_dir)
        return 0;

    int verifica_esq = cheia(raiz->esq);
    int verifica_dir = cheia(raiz->dir);

    if (verifica_esq != verifica_dir)
        return 0;

    return 1;
}

int calcula_altura(no *t) {
    if (!t) // Se nó t é vazio/nulo.
        return 0;
    int altE = calcula_altura(t->esq);
    int altD = calcula_altura(t->dir);
    if (altE > altD)
        return (altE + 1);

    return (altD + 1);
}