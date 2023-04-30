#ifndef AVL
#define AVL

typedef struct no tipo_no;

tipo_no* novo_no(int info);
tipo_no* insere(tipo_no *raiz, int info);
int altura(tipo_no *no);
int diferenca_altura(tipo_no *no);
int maior(int esq, int dir);
tipo_no* remover(tipo_no *raiz, int info);
tipo_no* rotacao_direita(tipo_no *no);
tipo_no* rotacao_esquerda(tipo_no *no);
tipo_no* rotacao_esquerda_direita(tipo_no *no);
tipo_no* rotacao_direita_esquerda(tipo_no *no);
tipo_no* menor_direita(tipo_no *raiz);
tipo_no* busca_binaria(tipo_no *raiz, int info);
void in_order(tipo_no *raiz);
void pre_order(tipo_no *raiz);
void pos_order(tipo_no *raiz);
void expurgar(tipo_no **raiz);
void imprime_arvore(tipo_no *raiz, int altura);

#endif