#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>


struct elem {
    tipo_chave chave;
};

struct no {
    tipo_elem elem;
    struct no *esq;
    struct no *dir;
};

int main() {

    tipo_no *arvere = malloc(sizeof(tipo_no));
    arvere = NULL;
    tipo_elem elem; 

    for(int i = 1; i < 10; i++) {
        scanf(" %d", &elem.chave);
        printf("julia: %d\n", elem.chave);
        arvere = insere(arvere, elem);
    }

    printf("\nIN ORDER:\n");
    in_order(arvere);

    elem.chave = 17;
    printf("\nBusca recursiva: %d\n", busca_binaria_recursiva(arvere, elem)->elem.chave);

    elem.chave = 9;
    printf("Busca interativa: %d\n", busca_binaria_interativo(arvere, elem)->elem.chave);
    
    printf("Remoção: \n");
    elem.chave = 17;
    remover(arvere, elem);
    in_order(arvere);

    expurgar(&arvere);
    if(!arvere)
        printf("\nEXPURGADO");

    return 0;
}

tipo_no* cria_raiz(tipo_no *raiz, tipo_elem elem) {
    raiz = malloc(sizeof(tipo_no));
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->elem = elem;
    return raiz;
}

tipo_no* insere(tipo_no *raiz, tipo_elem elem) {

    if(!raiz) {
        raiz = cria_raiz(raiz, elem);
        return raiz;
    }

    if(elem.chave < raiz->elem.chave)
        raiz->esq = insere(raiz->esq, elem);

    if(elem.chave > raiz->elem.chave)
        raiz->dir = insere(raiz->dir, elem);

    return raiz;
}

tipo_no* busca_binaria_recursiva(tipo_no *raiz, tipo_elem elem) {
    if(!raiz)
        return NULL;

    if(elem.chave == raiz->elem.chave)
        return raiz;

    if(raiz->elem.chave > elem.chave)
        return busca_binaria_recursiva(raiz->esq, elem);
    else
        return busca_binaria_recursiva(raiz->dir, elem);

}

tipo_no* busca_binaria_interativo(tipo_no *raiz, tipo_elem elem) {
    tipo_no *busca = raiz;

    while(busca) {
        if(busca->elem.chave == elem.chave)
            return busca;
        else if (busca->elem.chave > elem.chave)
            busca = busca->esq;
        else
            busca = busca->dir;
    }

    return NULL;
}

tipo_no* remover(tipo_no *raiz,  tipo_elem elem) {
    if(!raiz)
        return raiz;
    else if (elem.chave > raiz->elem.chave) 
        raiz->dir = remover(raiz->dir, elem);

    else if(elem.chave < raiz->elem.chave)
        raiz->esq = remover(raiz->esq, elem);

    else if (elem.chave == raiz->elem.chave) { 
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
            raiz->elem = aux->elem;
            raiz->esq = remover(raiz->esq, aux->elem);

            //OU
            /*tipo_no *aux = menor_direita(raiz->dir);
            raiz->elem = aux->elem;
            raiz->dir = remover(raiz->dir, aux->elem);*/
        }
    }

    return raiz; 
}

tipo_no *maior_esquerda(tipo_no *raiz) {
    // If there's no leaf to the right, then this is the maximum key value
    if (raiz->dir)
        return maior_esquerda(raiz->dir);
    
    return raiz;
}

tipo_no *menor_direita(tipo_no *raiz) {
    // If there's no leaf to the right, then this is the maximum key value
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
        printf(" [%d] ", raiz->elem.chave);
        in_order(raiz->dir);
    }
}