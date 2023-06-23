/*3)  A estrutura abaixo apresenta a definição de um tipo nó (de árvore binária - AB): 
//------------------------------------------- 
typedef struct no { 
 char info; 
 struct no *esq; 
 struct no *dir; 
} no; 
//------------------------------------------- 
Com base na ED acima, implemente: 
a)  Uma função que verifique se uma árvore binária está vazia.  
Protótipo: int vazia (no *raiz). 
b)  Uma função que faça a alocação dinâmica na memória de um nó de uma AB. 
Protótipo: no *cria_no (char c, no *esq, no *dir) 
c) Uma função que libera na memória um nó da ABB. 
Protótipo: no *libera_no (no *t) 
d)  Uma função que insere um nó à esquerda.  
Protótipo: int insere_esq (no *pai, char elemento). 
e)  Uma  função  que  percorre  toda  a  árvore  (sem  repetir  nós  -  percurso), 
imprimindo seus valores (campo info).  
Protótipo: void imprime_arvore (no *raiz). Aqui, utilize a estratégia/percurso 
de sua preferência.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no { 
 char info; 
 struct no *esq; 
 struct no *dir; 
} no; 

//a)  Uma função que verifique se uma árvore binária está vazia.
int vazia(no *raiz) {
    return (raiz) ? 0 : 1; //Retorna 0 caso exista raiz e 1 caso seja null
}

//b)  Uma função que faça a alocação dinâmica na memória de um nó de uma AB.
no *cria_no (char c, no *esq, no *dir) {
    no *criado = malloc(sizeof(no));
    if(!criado) {
        printf("Falha ao alocar na memória\n");
        return NULL;
    }

    criado->info = c;
    criado->esq = esq;
    criado->dir = dir;

    return criado;
}

//c) Uma função que libera na memória um nó da ABB.
no *libera_no (no *t) {
    no aux;
    if (!t)
        return NULL;
    if (!((*t)->esq)) {
        aux = *t;
        *t = (*t)->dir;
        free(aux);

        return t;

    } else if (!((*t)->dir)) {
        aux = *t;
        *t = (*t)->esq;
        free(aux);

        return t;
    }
    return substitui_menor_dir(t, &(*t)->dir);
}

no *substitui_menor_dir(no *t, no*suc) {
  no aux;

  if (!((*suc)->esq)) {
    (*t)->info = (*suc)->info;
    aux = *suc;
    (*suc) = (*suc)->dir;
    free(aux);

    return suc;
  } else
    suc = substitui_menor_dir(t, &(*suc)->esq);
}

//d)  Uma função que insere um nó à esquerda
int insere_esq (no *pai, char elemento) {
    
    if(!pai)
        return 0;

    no *filho = malloc(sizeof(no));

    if(!filho) {
        printf("Falha ao alocar na memória\n");
        return 0; 
    }

    filho->info = elemento;
    filho->dir = filho->esq = NULL;
    pai->esq = filho;

    return 1;
}

//e)  Uma  função  que  percorre  toda  a  árvore  (sem  repetir  nós  -  percurso),
//imprimindo seus valores (campo info). 
void imprime_arvore (no *raiz) {
    if(raiz) {
        imprime_arvore(raiz->esq);
        printf(" [%c] ", raiz->info);
        imprime_arvore(raiz->dir);
    }
}