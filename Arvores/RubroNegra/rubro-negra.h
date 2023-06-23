#define TRUE 1
#define FALSE 0
#define boolean int

#define PRETO 0
#define VERMELHO 1
#define color int

typedef struct node NO;

//Auxiliares

int menu();
int calcula_altura(NO* no);
int num_total_nos(NO* no);
boolean no_folha(NO *raiz);
NO * busca_binaria(NO *raiz, int elem);
NO * expurgar_arvore(NO *arvore);
void printa_no(NO *no, char *espacamento);
int conta_nos_pretos(NO* no);
// -----------------------------------------------------------------------------

//Inserção e remoção:

NO * novo_no(int elem, NO *raiz);
boolean insere_no(NO **raiz, int elem);
boolean deleta_no(NO **raiz, int elem);
NO * rotacao_esq(NO *no);
NO * rotacao_dir(NO *no);
void checa_no_insercao(NO *no);
void verifica_raiz(NO **raiz, NO **verifca);
boolean verifica_caso1(NO *removido);
void verifica_caso2(NO *removido, boolean remover, boolean direita, NO **raiz);
// -----------------------------------------------------------------------------

//Imprimir árvore:

void pre_ordem (NO *raiz);
void em_ordem (NO *raiz);
void pos_ordem (NO *raiz);
void imprime_arvore(NO *no, int nivel);
// -----------------------------------------------------------------------------