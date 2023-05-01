/*8)  Considere a seguinte função, que calcula o percurso pós-ordem em uma AB: 
 
//------------------------------------------- 
void posOrdem (no *t) { 
 if (t != NULL) { 
  posOrdem (t->esq); 
  posOrdem (t->dir); 
  printf ("Dado impresso: %c\n", t->info); 
 } 
} 
//------------------------------------------- 
 
Escreva  uma  função  não-recursiva  para  o  percurso  pós-ordem  acima.  Dica: 
utilizar pilha*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int info;
    struct no *esq;
    struct no *dir;
} no;

typedef struct pilha {
    no *no;
    struct pilha *prox;
} pilha;



void posOrdem_pilha(no *raiz) {
    int i = 0;
    no *pilha[1000];

    if (!raiz)
        return;

    no *aux = raiz;
    no *ultimo = NULL;

    while (aux || i >= 0) {
        if (aux) {
            pilha[i++] = aux;
            aux = aux->esq;
        } else {
            
            no *topo = pilha[i-1];
            if(topo->dir && topo->dir != ultimo)
                aux = topo->dir;
            else {
                printf(" [%d] ", topo->info);
                ultimo = topo;
                --i;
            }         
        }
    }
}

void posOrdem (no *t) { 
    if (t) { 
        posOrdem (t->esq); 
        posOrdem (t->dir); 
        printf (" [%d] ", t->info); 
    } 
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

int main()
{
    no *arvere = malloc(sizeof(no));
    arvere = NULL;
    int chave[7] = {10, 8, 7, 9, 14, 13, 15};

    for (int i = 0; i < 8; i++)
        arvere = insere(arvere, chave[i]);

    printf("\nPOS ORDEM:\n");
    posOrdem(arvere);
    printf("\n\nPILHA:\n");
    posOrdem_pilha(arvere);

    return 0;
}