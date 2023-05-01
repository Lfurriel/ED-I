#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>




struct no {
    int chave;
    struct no *esq;
    struct no *dir;
};

int main() {

    tipo_no *arvere = malloc(sizeof(tipo_no));
    arvere = NULL;
    int chave; 

    for(int i = 1; i < 10; i++) {
        scanf(" %d", &chave);
        arvere = insere(arvere, chave);
    }

    printf("\nIN ORDER:\n");
    in_order(arvere);

    chave = 17;
    printf("\nBusca recursiva: %d\n", busca_binaria_recursiva(arvere, chave)->chave);

    chave = 9;
    printf("Busca interativa: %d\n", busca_binaria_interativo(arvere, chave)->chave);
    
    printf("Remoção: \n");
    chave = 17;
    remover(arvere, chave);
    in_order(arvere);

    expurgar(&arvere);
    if(!arvere)
        printf("\nEXPURGADO");
}

tipo_no* cria_arvore(tipo_no *raiz, int *vet, int len) {
    int metade = len/2;
    raiz = malloc(sizeof(tipo_no));
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->chave = vet[metade];

    int *vet_esq = malloc(metade * sizeof(int));
    int *vet_dir = malloc(metade * sizeof(int));

    int j = 0;

    printf("vet_esq: ");
    for(int i = 0; i < metade; i++) {
        vet_esq[i] = vet[i];
        printf(" %d", vet_esq[i]);
    }

    printf("\nvet_dir: ");
    for(int i = metade+1; i < len; i++) {
        vet_dir[j++] = vet[i];
        printf(" %d", vet_dir[i]);
    }
    if(metade != 0) {
        raiz->esq = cria_arvore(raiz->esq, vet_esq, metade);
        raiz->dir = cria_arvore(raiz->dir, vet_dir, metade);
    }

    return raiz;    
}

tipo_no* cria_raiz(tipo_no *raiz, int chave) {
    raiz = malloc(sizeof(tipo_no));
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->chave = chave;
    return raiz;
}

tipo_no* insere(tipo_no *raiz, int chave) {

    if(!raiz) {
        raiz = cria_raiz(raiz, chave);
        return raiz;
    }

    if(chave < raiz->chave)
        raiz->esq = insere(raiz->esq, chave);

    if(chave > raiz->chave)
        raiz->dir = insere(raiz->dir, chave);

    return raiz;
}

tipo_no* busca_binaria_recursiva(tipo_no *raiz, int chave) {
    if(!raiz)
        return NULL;

    if(chave == raiz->chave)
        return raiz;

    if(raiz->chave > chave)
        return busca_binaria_recursiva(raiz->esq, chave);
    else
        return busca_binaria_recursiva(raiz->dir, chave);

}

tipo_no* busca_binaria_interativo(tipo_no *raiz, int chave) {
    tipo_no *busca = raiz;

    while(busca) {
        if(busca->chave == chave)
            return busca;
        else if (busca->chave > chave)
            busca = busca->esq;
        else
            busca = busca->dir;
    }

    return NULL;
}

tipo_no* remover(tipo_no *raiz,  int chave) {
    if(!raiz)
        return raiz;
    else if (chave > raiz->chave) 
        raiz->dir = remover(raiz->dir, chave);

    else if(chave < raiz->chave)
        raiz->esq = remover(raiz->esq, chave);

    else if (chave == raiz->chave) { 
        if(!raiz->esq && !raiz->dir) { //CASO 1
            free(raiz);
            return NULL;

        } else if (!raiz->esq) { //CASO 2
            tipo_no *aux = raiz;
            raiz = raiz->dir;
            free(aux);
            return raiz;

        } else if (!raiz->dir) { //CASO 2
            tipo_no *aux = raiz;
            raiz = raiz->esq;
            free(aux);
            return raiz;

        } else { //CASO 3
            tipo_no *aux = maior_esquerda(raiz->esq);
            raiz->chave = aux->chave;
            raiz->esq = remover(raiz->esq, aux->chave);

            //OU
            /*tipo_no *aux = menor_direita(raiz->dir);
            raiz->chave = aux->chave;
            raiz->dir = remover(raiz->dir, aux->chave);*/
        }
    }

    return raiz; 
}

tipo_no *maior_esquerda(tipo_no *raiz) {
    
    if (raiz->dir)
        return maior_esquerda(raiz->dir);
    
    return raiz;
}

tipo_no *menor_direita(tipo_no *raiz) {
    
    if (raiz->esq)
        return maior_esquerda(raiz->esq);
    
    return raiz;
}

void expurgar(tipo_no **raiz) {
   if ((*raiz)) {
        if((*raiz)->esq)
            expurgar(&(*raiz)->esq);
        if((*raiz)->dir)
            expurgar(&(*raiz)->dir);

        free((*raiz));
        *raiz = NULL;
    }
}

void in_order(tipo_no *raiz) {
    if(raiz) {
        in_order(raiz->esq);
        printf(" [%d] ", raiz->chave);
        in_order(raiz->dir);
    }
}