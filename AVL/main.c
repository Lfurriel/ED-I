/**
 * Implementação de uma árvore AVL (Adelson Velsky e Landis)
 * 
 * @author Júlia Rodrigues Marques do Nascimento
 * @author Lucas Furriel Rodrigues
*/

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

/**
 * Aloca um espaço na memória para um novo nó da árvore
 * 
 * @param info inteiro que representa a informação salva no nó
 * @returns nó criado
*/
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

/**
 * Busca na árvore binária a posição que será inserido o novo nó de acordo com a informação, após
 *  inserção é feito o balanceamento da árvore
 * 
 * @param info inteiro que representa a informação salva no nó
 * @returns nó
*/
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

/**
 * Função recursiva que calcula a altura de uma árvore partindo de um nó raiz
 * 
 * @param no nó da árvore 
 * @returns altura da árvore
*/
int altura(tipo_no *no) {
    if(!no)
        return -1;
    
    return no->altura;
}

/**
 * Função que calcula o fator de balanceamento de um nó
 * 
 * @param no nó da árvore 
 * @returns inteiro
*/
int diferenca_altura(tipo_no *no) {    if(!no)
        return 0;

    return altura(no->esq) - altura(no->dir);
}

/**
 * Ternário que retorna qual o maior inteiro dentre duas opções
 * 
 * @param esq valor A
 * @param dir valor B
 * 
 * @returns o maior inteiro
*/
int maior(int esq, int dir) {
    return (esq > dir) ? esq : dir;
}

/**
 * Função que busca na AVL um nó a ser removido e após remoção
 * faz novamente o balanceamento da árvore
 * 
 * @param raiz nó raiz de árvore/sub-árvore
 * @param info valor do nó a ser removido
 * 
 * @returns nó da árvore
*/
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

    if(diferenca < -1 && diferenca_altura(raiz->dir) >= 0)
            return rotacao_esquerda(raiz);
    if(diferenca > 1 && diferenca_altura(raiz->esq) >= 0)
        return rotacao_direita(raiz);
    
    if(diferenca > 1 && diferenca_altura(raiz->esq) < 0)
        return rotacao_esquerda_direita(raiz);

    
    
    if(diferenca < -1 && diferenca_altura(raiz->dir) < 0)
        return rotacao_direita_esquerda(raiz);

    return raiz;
}

/**
 * Rotação simples à direita
 * 
 * @param raiz nó raiz que será feito a rotação
 * 
 * @returns nó da árvore
*/
tipo_no* rotacao_direita(tipo_no *raiz) {
    tipo_no *nova_raiz = raiz->esq;
    tipo_no *filho = nova_raiz->dir;

    nova_raiz->dir = raiz;
    raiz->esq = filho;

    raiz->altura = maior(altura(raiz->esq), altura(raiz->dir) + 1);
    nova_raiz->altura = maior(altura(nova_raiz->esq), altura(nova_raiz->dir) + 1);

    return nova_raiz;
}

/**
 * Rotação simples à esquerda
 * 
 * @param raiz nó raiz que será feito a rotação
 * 
 * @returns nó da árvore
*/
tipo_no* rotacao_esquerda(tipo_no *raiz) {
    tipo_no *nova_raiz = raiz->dir;
    tipo_no *filho = nova_raiz->esq;

    nova_raiz->esq = raiz;
    raiz->dir = filho;

    raiz->altura = maior(altura(raiz->esq), altura(raiz->dir) + 1);
    nova_raiz->altura = maior(altura(nova_raiz->esq), altura(nova_raiz->dir) + 1);

    return nova_raiz;
}

/**
 * Rotação dupla à direita
 * 
 * @param no nó raiz que será feito a rotação
 * 
 * @returns nó da árvore
*/
tipo_no* rotacao_esquerda_direita(tipo_no *no) {
    no->esq = rotacao_esquerda(no);

    return rotacao_direita(no);
}

/**
 * Rotação dupla à esqurda
 * 
 * @param no nó raiz que será feito a rotação
 * 
 * @returns nó da árvore
*/
tipo_no* rotacao_direita_esquerda(tipo_no *no) {
    no->dir = rotacao_direita(no);

    return rotacao_esquerda(no);
}

/**
 * Busca na AVL o menor elemento da sub-árvore direita
 * 
 * @param no nó raiz da sub-árvore
 * 
 * @returns "menor dos maiores"
*/
tipo_no* menor_direita(tipo_no *raiz) {
    tipo_no *busca = raiz;

    while (busca->esq)
        busca = busca->esq;
    
   
    return busca;    
}

/**
 * Busca na AVL binariamente de forma recursiva um elemento na AVL
 * 
 * @param raiz nó raiz
 * @param info elemento a ser procurado
 * 
 * @returns "menor dos maiores"
*/
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

/**
 * Printa de forma "em ordem" os elementos da AVL
 * 
 * @param raiz nó raiz
*/
void in_order(tipo_no *raiz) {
    if(raiz) {
        in_order(raiz->esq);
        printf(" [%d] ", raiz->info);
        in_order(raiz->dir);
    }
}

/**
 * Printa de forma "pré ordem" os elementos da AVL
 * 
 * @param raiz nó raiz
*/
void pre_order(tipo_no *raiz) {
    if(raiz) {
        printf(" [%d] ", raiz->info);
        pre_order(raiz->esq);
        pre_order(raiz->dir);
    }
}

/**
 * Printa de forma "pós ordem" os elementos da AVL
 * 
 * @param raiz nó raiz
*/
void pos_order(tipo_no *raiz) {
    if(raiz) {
        pos_order(raiz->esq);
        pos_order(raiz->dir);
        printf(" [%d] ", raiz->info);
    }
}

/**
 * Remove da memória todos os elementos da AVL
 * 
 * @param raiz nó raiz
*/
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

/**
 * Printa os elementos da AVL
 * 
 * @param raiz nó raiz
 * @param altura altura da árvore
*/
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