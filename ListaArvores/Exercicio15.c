/*15) Sabe-se que uma ABB balanceada/perfeitamente balanceada possuem as
estruturas ideais para buscas. No entanto, inserções e remoções podem
desbalancear a árvore, tornando as buscas ineficientes. A fim de contorna esse
problema, implemente o seguinte algoritmo de rebalanceamento:
A partir de um vetor ordenado de valores distintos, realizar os seguintes passos:

1. O registro do meio é inserido na ABB vazia (como raiz).
2. Tome a metade esquerda do array, e então repita o passo 1) para a sub-
árvore esquerda.
3. Aplique a mesma ideia para a metade direita e sub-árvore direita.
4. Repita o processo até não poder dividir mais.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int info;
    struct no *esq;
    struct no *dir;
} tipo_no;

tipo_no* cria_arvore(tipo_no *raiz, int *vet, int len) {
    int metade = len/2;
    raiz = malloc(sizeof(tipo_no));
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->chave = vet[metade];

    int *vet_esq = malloc(metade * sizeof(int));
    int *vet_dir = malloc(metade * sizeof(int));

    int j = 0;
    for(int i = 0; i < metade; i++) {
        vet_esq[i] = vet[i];
        printf(" %d", vet_esq[i]);
    }
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