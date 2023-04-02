#include "lista.h"  //Carrega o arquivo .h criado
#include <stdio.h>  //Para usar printf ,...
#include <stdlib.h> //Para usar malloc, free, exit ...
#include <string.h> //Para usar strcmp

#define MAX 100 // estimativa do tamanho m�ximo da lista
#define TRUE 1  // define tipo boleano � n�o existe em C
#define FALSE 0
#define boolean int

// Implementa��o: lista seq.

// Opera��es
//-------------------------------------------
boolean Vazia(lista *L) {
  // Retorna true (1): se vazia, false (0): caso contr�rio
  return (L->nelem == 0);
}

boolean Cheia(lista *L) {
  // Retorna true (1): se cheia, false (0): caso contr�rio
  return (L->nelem == MAX);
}

void Definir(lista *L) {
  /*Cria uma lista vazia. Este procedimento deve ser chamado
  para cada nova lista antes de qualquer outra opera��o.*/
  L->nelem = 0;
  L->A[0].chave = 0;
}

void Apagar(lista *L) {
  // Apaga "logicamente" uma lista
  L->nelem = 0;
}

boolean Inserir_posic(tipo_elem x, int p, lista *L) {
  /*Insere x, que � um novo elemento na posi��o p da lista
  Se L = a_1, a_2,... a_n ent�o temos a_1, a_2, ...
  a_{p-1}, x, a_{p+1}, ... an.
  Devolve true se sucesso, false c.c. (isto �: L n�o tem nenhuma
  posi��o p ou lista cheia). Obs: Opera��o para LISTA N�O-ORDENADA */

  int q;

  if (Cheia(L) || p > L->nelem + 1 || p < 1) {
    // Lista cheia ou posi��o n�o existe
    return FALSE;
  } else {
    for (q = L->nelem; q >= p; q--) // Copia vizinho p/ direita
      L->A[q + 1] = L->A[q];

    L->A[p] = x;
    L->nelem++;
    return TRUE; // Inser��o feita com sucesso
  }
}

void Remover_posic(int *p, lista *L) {
  /*S� � ativada ap�s a busca ter retornado a posi��o p
  do elemento a ser removido - Nro de Mov = (nelem � p)*/

  int i;

  for (i = *p + 1; i <= L->nelem; i++)
    L->A[i - 1] = L->A[i];

  L->nelem--;
}

void Impr_elem(tipo_elem t) {
  printf("chave: %d\n", t.chave);
  printf("nome: %s\n", t.info.nome);
  printf("idade: %d\n", t.info.idade);
  printf("media final: %4.2f\n", t.info.media_final);
  //... (demais dados)
}

void Imprimir(lista *L) {
  // Imprime os elementos na sua ordem de preced�ncia

  int i;

  if (!Vazia(L))
    for (i = 1; i <= L->nelem; i++) {
      printf("\n--------------------\n\n");
      Impr_elem(L->A[i]);
    }
  printf("\n--------------------\n");
}

int Tamanho(lista *L) {
  // Retorna o tamanho da lista. Se L � vazia retorna 0

  return L->nelem;
}

// Implementa��es para listas ordenadas
//-------------------------------------------
boolean Buscar_ord(tipo_chave x, lista *L, int *p) {
  /*Retorna true se x ocorre na posi��o p. Se x ocorre mais de
  uma vez, retorna a posi��o da primeira ocorr�ncia. Se x n�o
  ocorre, retorna false. Para listas ORDENADAS*/

  int esq, dir, meio;
  esq = 1;
  dir = L->nelem;

  while (esq <= dir) {
    meio = (esq + dir) / 2;
    if (L->A[meio].chave == x) {
      *p = meio;
      return TRUE;
    } else if (L->A[meio].chave < x) {
      esq = meio + 1;
    } else {
      dir = meio - 1;
    }
  }
  return FALSE;

  //....
}

boolean Busca_bin(tipo_chave x, lista *L, int *p) {
  /*Retorna em p a posi��o de x na lista ORDENADA e true.
  //Se x n�o ocorre, retorna false*/

  // Implementa��o de busca bin�ria
  int inf = 1;
  int sup = L->nelem;
  int meio;

  while (!(sup < inf)) {
    meio = (inf + sup) / 2;
    if (L->A[meio].chave == x) {
      *p = meio; // Sai da busca
      return TRUE;
    } else {
      if (L->A[meio].chave < x)
        inf = meio + 1;
      else
        sup = meio - 1;
    }
  }
  return FALSE;
}

boolean Remover_ch(tipo_chave x, lista *L) {
  /*Remo��o dada a chave. Retorna true, se removeu, ou
  false, c.c.*/

  int *p;
  boolean removeu = FALSE;

  if (Busca_bin(x, L, p)) // Procura via busca bin�ria
  {
    Remover_posic(p, L);
    removeu = TRUE;
  }

  return removeu;
}

void numerar(lista *L) {
  int i;
  for (i = 0; i <= L->nelem; i++)
    L->A[i].chave = (i + 1);
}

boolean Inserir_ord_Nome(tipo_elem x, lista *L) {
  if (Cheia(L)) {
    return FALSE;
  }
  int i;
  for (i = L->nelem; i > 0 && strcmp(x.info.nome, L->A[i].info.nome) < 0; i--) {
    L->A[i + 1] = L->A[i];
  }
  L->A[i + 1] = x;
  L->nelem++;
  return TRUE;
}

boolean Inserir_ord_ch(tipo_elem x, lista *L) {
  if (Cheia(L) || Repetido(x.chave, L)) {
    return FALSE;
  }
  int i;
  for (i = L->nelem; i > 0 && x.chave < L->A[i].chave; i--) {
    L->A[i + 1] = L->A[i];
  }
  L->A[i + 1] = x;
  L->nelem++;
  return TRUE;
}

boolean Buscar_Nome(char *nome, lista *L, int *p) {

  int i;
  for (i = 1; i <= L->nelem; i++) {
    if (strcmp(L->A[i].info.nome, nome) == 0) {
      *p = i;
      return TRUE;
    }
  }
  return FALSE;
}

boolean Buscar_ord_Nome(char *nome, lista *L, int *p) {
  int esq = 1, dir = L->nelem, meio;
  while (esq <= dir) {
    meio = (esq + dir) / 2;
    if (strcmp(nome, L->A[meio].info.nome) == 0) {
      *p = meio;
      return TRUE;
    } else if (strcmp(nome, L->A[meio].info.nome) < 0) {
      dir = meio - 1;
    } else {
      esq = meio + 1;
    }
  }
  return FALSE;
}

boolean Buscar(tipo_chave x, lista *L, int *p) {
  /*Retorna true, se x ocorre na posi��o p. Se x ocorre mais de
  uma vez, retorna a posi��o da primeira ocorr�ncia. Se x n�o
  ocorre, retorna false. Para listas N�O-ORDENADAS*/

  if (!Vazia(L)) {
    int i = 1;
    while (i <= L->nelem)
      if (L->A[i].chave == x) {
        *p = i;
        return TRUE;
      } else
        i++;
  }
  return FALSE; // Retorna false se n�o encontrou
}

boolean Repetido(tipo_chave chave, lista *L) {
  for (int i = 0; i <= L->nelem; i++) {
    if (L->A[i].chave == chave) {
      return TRUE;
    }
  }
  return FALSE;
}
//-------------------------------------------
