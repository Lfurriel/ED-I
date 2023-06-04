#include "caminhos.c"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  Grafo *grafo = cria_grafo();
  le_arquivo(&grafo, "digrafo.txt");

  int caminho_minimo[grafo->nos];
  int i, j, c = 0;

  for (j = 0; j < grafo->nos; j++)
    caminho_minimo[j] = INT_MAX;

  caminho_minimo[c] = 0;

  for (i = 0; i < grafo->nos; i++) {
    for (j = 1; j < grafo->nos; j++) {
      if (grafo->matriz[i][j] != 0 &&
          (grafo->matriz[i][j] + caminho_minimo[i] < caminho_minimo[j])) {
        printf("[%d][%d]: %d\n", i, j, grafo->matriz[i][j]);
        caminho_minimo[j] = caminho_minimo[i] + grafo->matriz[i][j];
      }
    }
  }

  printf("Dist:");
  for (i = 0; i < grafo->nos; i++) {
    printf(" [%d] ", caminho_minimo[i]);
  }

  return 0;
}