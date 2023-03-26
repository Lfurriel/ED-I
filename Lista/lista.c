#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

int quantidade_elementos;

typedef struct lista
{
    int seq;
    int id;
    char nome[60];
    int idade;
    float media;
    struct lista *prox;
} TLista;

int vazia() { return quantidade_elementos == 0; }

int cheia() { return quantidade_elementos == MAX; }

void definir(TLista **cabeca)
{
    quantidade_elementos = 0;
    (*cabeca) = NULL;
}

void apagar(TLista **cabeca)
{
    quantidade_elementos = 0;
    (*cabeca) = NULL;
}

void insire_ordenado(TLista **lista)
{
    TLista *novo = malloc(sizeof(TLista)), *busca, *busca_prev;
    int flag = 1;
    printf("Digite o id: ");
    scanf("%d", &novo->id);
    printf("Digite o nome: ");
    scanf("%s", novo->nome);
    printf("Digite a idade: ");
    scanf("%d", &novo->idade);
    printf("Digite a média: ");
    scanf("%f", &novo->media);
    novo->prox = NULL;

    if (!(*lista)) // Lista vazia (insere na cabeça)
        *lista = novo;
    else if (strcmp(novo->nome, (*lista)->nome) < 0) // Elemento inserido na cabeça
    {
        novo->prox = (*lista);
        *lista = novo;
    }
    else
    {
        busca = (*lista)->prox;
        busca_prev = (*lista);

        while (busca && flag)
        {
            if (strcmp(novo->nome, busca->nome) <= 0)
            {
                flag = 0;
                novo->prox = busca;
                busca_prev->prox = novo;
            }

            busca_prev = busca;
            busca = busca->prox;
        }
        if (flag)
            busca_prev->prox = novo;
    }
    numerar((*lista)); // Ordena os elementos inseridos
    quantidade_elementos++;
}

void numerar(TLista *lista)
{
    int i = 1;
    while (lista)
    {
        lista->seq = i;
        lista = lista->prox;
        i++;
    }
}

TLista *buscar_id(TLista *lista, int id)
{
    TLista *busca = lista;
    while (busca)
    {
        if (busca->id == id)
            return busca;
        busca = busca->prox;
    }
    return busca;
}

TLista *buscar_nome(TLista *lista, char *nome)
{
    TLista *busca = lista;
    while (busca)
    {
        if (strcmp(busca->nome, nome) == 0)
            return busca;
        busca = busca->prox;
    }
    return busca;
}

void remove_id(TLista **lista, int id)
{
    TLista *busca = (*lista), *busca_prev;
    int flag = 0;

    if (busca->id == id)
    {
        (*lista) = (*lista)->prox;
        flag = 1;
    }
    else if ((*lista)->prox)
    {
        busca_prev = (*lista);
        while (busca->prox && !flag)
        {
            busca = busca->prox;
            if (busca->id == id)
            {
                busca_prev->prox = busca->prox;
                flag = 1;
            }
            busca_prev = busca;
        }
    }

    if (flag)
    {
        printf("REMOVENDO %s\n", busca->nome);
        free(busca);
        quantidade_elementos--;
        numerar((*lista));
    }
    else
        printf("NÃO ENCONTRADO!\n");
}

void remove_nome(TLista **lista, char *nome)
{
    TLista *busca = (*lista), *busca_prev;
    int flag = 0;

    if (strcmp(busca->nome, nome) == 0)
    {
        (*lista) = (*lista)->prox;
        flag = 1;
    }
    else if ((*lista)->prox)
    {
        busca_prev = (*lista);
        while (busca->prox && !flag)
        {
            busca = busca->prox;
            if (strcmp(busca->nome, nome) == 0)
            {
                busca_prev->prox = busca->prox;
                flag = 1;
            }
            busca_prev = busca;
        }
    }

    if (flag)
    {
        printf("REMOVENDO %s\n", busca->nome);
        free(busca);
        quantidade_elementos--;
        numerar((*lista));
    }
    else
        printf("NÃO ENCONTRADO!\n");
}

void apresentar_lista(TLista *lista)
{
    printf("\n\nQUANTIDADE DE REGISTROS:\t%d\n", quantidade_elementos);
    while (lista)
    {
        printf("\n---------------- %d ----------------\n", lista->seq);
        printf("ID:\t%d\n", lista->id);
        printf("NOME:\t%s\n", lista->nome);
        printf("IDADE:\t%d\n", lista->idade);
        printf("MÉDIA:\t%.2f\n", lista->media);
        lista = lista->prox;
    }
    printf("\n-----------------------------------\n");
}
