/*14) Escreva uma função que, dada uma ABB qualquer composta de inteiros,
imprima todos os elementos menores que N.
Protótipo: int *menores_valores (no *raiz, int N).*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int info;
    struct no *esq;
    struct no *dir;
} no;

int *menores_valores (no *t, int num) {
  int tam = tamanho(t);
  int *vet = malloc(tam * sizeof(int));
  int indice = 0;

  menores_valores_rec(t, vet, indice, num);
  
  return vet;
}

int *menores_valores_rec (no *t, int *vet, int indice, int num) {
  if (!t)
    return vet;

  menores_valores_rec(t->esq, vet, indice, num);

  if (t->info < num) {
    vet[indice] = t->info;
    indice ++;
  }
  menores_valores_rec(t->dir, vet, indice, num);
  return vet;
}

int tamanho(no *t) {
  if (!t)
    return 0;
  return 1 + tamanho(t->dir) + tamanho(t->esq);
}