#ifndef BINARY_SEACRH_TREE
#define BINARY_SEACRH_TREE

typedef struct no tipo_no;

tipo_no* cria_raiz(tipo_no *raiz, int chave);
tipo_no* insere(tipo_no *raiz, int chave);
tipo_no* busca_binaria_recursiva(tipo_no *raiz, int chave);
tipo_no* busca_binaria_interativo(tipo_no *raiz, int chave);
tipo_no* remover(tipo_no *raiz,  int chave);
tipo_no *maior_esquerda(tipo_no *raiz);
tipo_no *menor_direita(tipo_no *raiz);
void expurgar(tipo_no **raiz);
void in_order(tipo_no *raiz);

tipo_no* cria_arvore(tipo_no *raiz, int *vet, int len);

#endif 
