typedef struct grafo Grafo;

/**
 * Aloca um grafo na memoria
 */
Grafo *cria_grafo();

/**
 * Lê de um arquivo as informações a ser preenchidas no grafo
 */
void le_arquivo(Grafo **grafo, char *aquivo);
