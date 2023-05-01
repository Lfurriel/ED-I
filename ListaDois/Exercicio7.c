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

int cheia(no *raiz)
{

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

no *cria_raiz(no *raiz, int chave)
{
    raiz = malloc(sizeof(no));
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->info = chave;
    return raiz;
}

no *insere(no *raiz, int chave)
{

    if (!raiz)
    {
        raiz = cria_raiz(raiz, chave);
        return raiz;
    }

    if (chave < raiz->info)
        raiz->esq = insere(raiz->esq, chave);

    if (chave > raiz->info)
        raiz->dir = insere(raiz->dir, chave);

    return raiz;
}

int calcula_altura(no *t)
{
    if (!t) // Se nó t é vazio/nulo.
        return 0;
    int altE = calcula_altura(t->esq);
    int altD = calcula_altura(t->dir);
    if (altE > altD)
        return (altE + 1);

    return (altD + 1);
}

int main()
{
    no *arvere = malloc(sizeof(no));
    arvere = NULL;
    int chave;

    /*
    10
    8
    7
    9
    14
    13
    15
    */

    for (int i = 1; i <= 7; i++)
    {
        scanf(" %d", &chave);
        arvere = insere(arvere, chave);
    }

    if (cheia(arvere))
        printf("cheia!\n");
    else
        printf("Não\n");
}