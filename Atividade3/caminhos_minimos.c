#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct grafo
{
    int num_no;
    int **matriz;
} Grafo;

Grafo *criar_grafo()
{
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->num_no = 0;
    grafo->matriz = NULL;
    return grafo;
}

void le_arquivo(Grafo **grafo, char *file_name)
{
    FILE *fp = fopen(file_name, "r");
    int i, o, d, val_peso;

    int num;
    fscanf(fp, "%d", &num);
    printf("NUM: %d\n", num);

    (*grafo)->num_no = num;
    (*grafo)->matriz = (int **)calloc(num, sizeof(int *));
    for (i = 0; i < num; i++)
        (*grafo)->matriz[i] = (int *)calloc(num, sizeof(int));

    while (!feof(fp))
    { // ESTOU FORÇANDO BIDIRECIONAL POIS UNILATERAL DÁ ERRO
        fscanf(fp, "%d%d%d", &o, &d, &val_peso);
        (*grafo)->matriz[o][d] = val_peso;
        (*grafo)->matriz[d][o] = val_peso;
    }

    printf("\n\MATRIZ:\n");
    for (i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            printf(" [%d] ", (*grafo)->matriz[i][j]);
        }
        printf("\n");
    }

    fclose(fp);
}

int encontra_menor(int *caminho_minimo, bool visitado[], int num_no)
{
    int menor = INT_MAX;
    int menor_indice = -1;
    int i;

    for (i = 0; i < num_no; i++)
    {
        if (!visitado[i] && caminho_minimo[i] < menor)
        {
            menor = caminho_minimo[i];
            menor_indice = i;
        }
    }

    return menor_indice;
}

void dijkstra(Grafo *grafo, int c)
{
    int *dist = malloc(grafo->num_no * sizeof(int));
    bool *visitado = malloc(grafo->num_no * sizeof(bool));
    int i, j;

    for (i = 0; i < grafo->num_no; i++)
    {
        dist[i] = INT_MAX;
        visitado[i] = false;
    }

    dist[c] = 0;

    for (i = 0; i < grafo->num_no - 1; i++)
    {
        int u = encontra_menor(dist, visitado, grafo->num_no);
        visitado[u] = true;

        for (j = 0; j < grafo->num_no; j++)
        {
            if (!visitado[j] && grafo->matriz[u][j] != 0 && dist[u] != INT_MAX &&
                dist[u] + grafo->matriz[u][j] < dist[j])
            {
                dist[j] = dist[u] + grafo->matriz[u][j];
            }
        }
    }

    printf("Resposta:");
    for (i = 0; i < grafo->num_no; i++)
    {
        if (dist[i] != INT_MAX)
            printf(" [%d] ", dist[i]);
        else
            printf(" [-] ");
    }

    free(dist);
    free(visitado);
}

void expurgar(Grafo *grafo)
{
    for (int i = 0; i < grafo->num_no; i++)
        free(grafo->matriz[i]);
    free(grafo->matriz);
    free(grafo);
}

int main()
{
    Grafo *grafo;
    grafo = criar_grafo();
    le_arquivo(&grafo, "digrafo.txt");

    int no;

    printf("Insere o no para calcular as distancias: ");
    scanf("%d", &no);

    dijkstra(grafo, no);

    return 0;
}
