#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

struct no {
    struct no *esq;
    struct no *dir;
    int info;
    int altura;
};

int main() {

    int op = 1, aux;
    tipo_no *arvore = malloc(sizeof(tipo_no)), *no_aux;
    arvore = NULL;

    while (op != 0) {
        printf("\n\nESCOLHA:\n");
        printf("\t1. Inserir novo elemento\n");
        printf("\t2. Deletar elemento\n");
        printf("\t3. Buscar elemento\n");
        printf("\t4. Imprimir pre_order\n");
        printf("\t5. Imprimir in_order\n");
        printf("\t6. Imprimir post_order\n");
        printf("\t7. Imprimir arvore\n");
        printf("\t0. Sair\n");

        printf("\t\nOPCAO: ");
        scanf("%d", &op);

        switch (op) {
        case 1:
            printf("Insira o valor do novo elemento: ");
            scanf("%d", &aux);

            no_aux = busca_binaria(arvore, aux);
            if(no_aux)
                printf("Esse número já existe na árvore\n");
            else
                arvore = insere(arvore, aux);

            break;
        case 2:
            printf("Insira o valor do elemento a ser deletado: ");
            scanf("%d", &aux);

            no_aux = busca_binaria(arvore, aux);
            if(!no_aux)
                printf("Esse número não existe na árvore\n");
            else
                arvore = remover(arvore, aux);

            break;

        case 3:
            printf("Insira o valor do elemento: ");
            scanf("%d", &aux);

            no_aux = busca_binaria(arvore, aux);
            if(!no_aux)
                printf("Esse número não existe na árvore\n");
            else
                printf("Elemento encontrado: %d", no_aux->info);
            
            break;
        
        case 4:
            printf("PRE-ORDER:\n");
            pre_order(arvore);
            break;

        case 5:
            printf("IN-ORDER:\n");
            in_order(arvore);
            break;
        
        case 6:
            printf("POS-ORDER:\n");
            pos_order(arvore);
            break;

        case 7:
            printf("Imprimindo arvore completa:\n");
            imprime_arvore(arvore, 1);
            break;

        default:
            printf("Opção inválida!!\n");
            break;
        }
    }
    

    return 0;
}

tipo_no* novo_no(int info) {
    tipo_no *raiz = malloc(sizeof(tipo_no));
    
    if(!raiz) {
        printf("ERRO AO ALOCAR\n");
        return NULL;
    }

    raiz->info = info;
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->altura = 0;

    return raiz;
}

tipo_no* insere(tipo_no *raiz, int info) {
    
    if(!raiz) {
        raiz = novo_no(info);
        return raiz;
    }

    if(info < raiz->info)
        raiz->esq = insere(raiz->esq, info);
    else if (info > raiz->info)
        raiz->dir = insere(raiz->dir, info);

    raiz->altura = maior(altura(raiz->esq), altura(raiz->dir) + 1);

    int diferenca = diferenca_altura(raiz);

    if(diferenca > 1 && info < raiz->esq->info)
        return rotacao_direita(raiz);

    if(diferenca < -1 && info > raiz->dir->info)
        return rotacao_esquerda(raiz);

    if(diferenca > 1 && info > raiz->esq->info)
        return rotacao_esquerda_direita(raiz);

    if(diferenca < -1 && info < raiz->dir->info)
        return rotacao_direita_esquerda(raiz);

    return raiz;
}

int altura(tipo_no *no) {
    if(!no)
        return -1;
    
    return no->altura;
}

int diferenca_altura(tipo_no *no) {
    if(!no)
        return 0;

    return altura(no->esq) - altura(no->dir);
}

int maior(int esq, int dir) {
    return (esq > dir) ? esq : dir;
}

tipo_no* remover(tipo_no *raiz, int info) {
    if(!raiz)
        return raiz;

    if(info < raiz->info)
       raiz->esq = remover(raiz->esq, info);
    
    else if(info > raiz->info)
        raiz->dir = remover(raiz->dir, info);

    else {
        if(!(raiz->esq) || !(raiz->dir)) {
            tipo_no *aux = raiz->esq ? raiz->esq : raiz->dir;

            if(!aux) {
                aux = raiz;
                raiz = NULL;
            } else
                *raiz = *aux;

            free(aux);
        } else {
            tipo_no *aux = menor_direita(raiz->dir);
            raiz->info = aux->info;
            raiz->dir = remover(raiz->dir, aux->info);
        }
    }

    if(!raiz)
        return raiz;

    raiz->altura = maior(altura(raiz->esq), altura(raiz->dir) + 1);

    int diferenca = diferenca_altura(raiz);

    if(diferenca > 1 && diferenca_altura(raiz->esq) >= 0)
        return rotacao_direita(raiz);
    
    if(diferenca > 1 && diferenca_altura(raiz->esq) < 0)
        return rotacao_esquerda_direita(raiz);

    if(diferenca < -1 && diferenca_altura(raiz->dir) >= 0)
        return rotacao_esquerda(raiz);
    
    if(diferenca < -1 && diferenca_altura(raiz->dir) < 0)
        return rotacao_direita_esquerda(raiz);

    return raiz;
}

tipo_no* rotacao_direita(tipo_no *no) {
    tipo_no *esq = no->esq;
    tipo_no *dir = esq->dir;

    esq->dir = no;
    no->esq = dir;

    no->altura = maior(altura(no->esq), altura(no->dir) + 1);
    esq->altura = maior(altura(esq->esq), altura(esq->dir) + 1);

    return esq;
}

tipo_no* rotacao_esquerda(tipo_no *no) {
    tipo_no *dir = no->dir;
    tipo_no *esq = dir->esq;

    dir->esq = no;
    no->dir = esq;

    no->altura = maior(altura(no->esq), altura(no->dir) + 1);
    dir->altura = maior(altura(dir->esq), altura(dir->dir) + 1);

    return dir;
}

tipo_no* rotacao_esquerda_direita(tipo_no *no) {
    no->esq = rotacao_esquerda(no);

    return rotacao_direita(no);
}

tipo_no* rotacao_direita_esquerda(tipo_no *no) {
    no->dir = rotacao_direita(no);

    return rotacao_esquerda(no);
}

tipo_no* menor_direita(tipo_no *raiz) {
    tipo_no *busca = raiz;

    while (busca->esq)
        busca = busca->esq;
    
   
    return busca;    
}

tipo_no* busca_binaria(tipo_no *raiz, int info) {
    if(!raiz)
        return NULL;

    if(info == raiz->info)
        return raiz;

    if(raiz->info > info)
        return busca_binaria(raiz->esq, info);
    else
        return busca_binaria(raiz->dir, info);

}

void in_order(tipo_no *raiz) {
    if(raiz) {
        in_order(raiz->esq);
        printf(" [%d] ", raiz->info);
        in_order(raiz->dir);
    }
}

void pre_order(tipo_no *raiz) {
    if(raiz) {
        printf(" [%d] ", raiz->info);
        pre_order(raiz->esq);
        pre_order(raiz->dir);
    }
}

void pos_order(tipo_no *raiz) {
    if(raiz) {
        pos_order(raiz->esq);
        pos_order(raiz->dir);
        printf(" [%d] ", raiz->info);
    }
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

void imprime_arvore(tipo_no *raiz, int altura) {
    int i;
    if (raiz) {
        imprime_arvore(raiz->dir, altura + 1);
        printf("\n\n");

        for (i = 0; i < altura; i++) 
            printf("\t");

        printf("%d", raiz->info);

        imprime_arvore(raiz->esq, altura + 1);
    }
}