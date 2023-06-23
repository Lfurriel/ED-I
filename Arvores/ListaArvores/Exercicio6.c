/*6)  Escreva as seguintes funções para manipular árvores binárias: 
a)  Função  que  retorna  o  maior  elemento  da  árvore  (dado  um  campo  chave 
inteiro). 
b)  Função que retorne o total de nós folhas de uma AB.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int info; 
  struct no *esq; 
  struct no *dir; 
} no; 

//a)  Função  que  retorna  o  maior  elemento  da  árvore  (dado  um  campo  chave inteiro).
no* busca_maior_abb(no *raiz) {
	no *busca = raiz;
	while (busca->dir)
		busca = busca->dir;

	return busca;    
}

//a)  Função  que  retorna  o  maior  elemento  da  árvore  (dado  um  campo  chave inteiro).
no* busca_maior_ab(no *raiz) {

	if (!raiz)
		return NULL;

	int maior, esq, dir;
	maior = raiz->info;

	no *maior_no;

	if (raiz->esq) {
		esq = busca_maior_ab(raiz->esq).info;
		if (esq > maior) {
			maior_no = raiz->esq;
			maior = esq;
		}
	} 
	
	if (raiz->dir) {
		dir = busca_maior_ab(raiz->dir).info;
		if (dir > maior) {
			maior_no = raiz->dir;
			maior = dir;
		}
	}
  
  return maior_no;
}

//b)  Função que retorne o total de nós folhas de uma AB
int total_no_folha (no *raiz) {
	if (!raiz)
		return 0;
	if (!(raiz->esq) && !(raiz->dir))
		return 1;
	else	
		return (total_no_folha(raiz->esq) + total_no_folha(raiz->dir));
}
