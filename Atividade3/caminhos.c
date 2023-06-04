#include "caminhos.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

struct grafo {
  int nos;
  int **matriz;
};

Grafo *cria_grafo() {
  Grafo *grafo = malloc(sizeof(Grafo));
  grafo->nos = 0;
  grafo->matriz = NULL;
  return grafo;
}

void le_arquivo(Grafo **grafo, char *arquivo) {
  FILE *fp = fopen(arquivo, "r");
  int i, o, d, val_peso;

  int num;
  fscanf(fp, "%d", &num);
  (*grafo)->nos = num;

  (*grafo)->matriz = (int **)calloc(num, sizeof(int *));

  for (int i = 0; i < num; i++)
    (*grafo)->matriz[i] = (int *)calloc(num, sizeof(int));

  while (!feof(fp)) {
    fscanf(fp, "%d%d%d", &o, &d, &val_peso);
    (*grafo)->matriz[o][d] = val_peso;
  }

  fclose(fp);
}
