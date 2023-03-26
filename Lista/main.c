#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.c"

int main()
{
    int op = 1;
    char pal[60];
    TLista *cabeca = NULL, *achou;

    definir(&cabeca); // inicializa

    if(vazia())
        printf("LISTA VAZIA\n");
    else
        printf("LISTA NÃO ESTÁ VAZIA\n");

    if(cheia())
        printf("LISTA CHEIA\n");
    else
        printf("LISTA NÃO ESTÁ CHEIA\n");

    while (op) //laço para inserir diversos elementos
    {
        insire_ordenado(&cabeca);
        printf("Inserir novo? <1> SIM, <0> NÃO\n");
        scanf(" %d", &op);
        if(quantidade_elementos == MAX) {
            printf("NÃO É POSSÍVEL INSERIR MAIS ELEMENTOS\n");
            op = 0;
        }
    }

    if(cheia())
        printf("LISTA CHEIA\n");
    else
        printf("LISTA NÃO ESTÁ CHEIA\n");

    apresentar_lista(cabeca); //Apresenta a lista por inteiro

    printf("\n\nDigite o id que quer buscar: ");
    scanf(" %d", &op);
    achou = buscar_id(cabeca, op);
    if(achou)
        printf("ACHAMOS REGISTRO %d, NOME: %s\n", achou->id, achou->nome);
    else
        printf("NÃO ACHOU");

    printf("\n\nDigite o id que quer remover: ");
    scanf(" %d", &op);
    remove_id(&cabeca, op);
    apresentar_lista(cabeca);

    printf("\n\nDigite o nome que quer buscar: ");
    scanf(" %s", pal);

    achou = buscar_nome(cabeca, pal);
    if(achou)
        printf("ACHAMOS REGISTRO %d, NOME: %s\n", achou->id, achou->nome);
    else
        printf("NÃO ACHOU");

    printf("\n\nDigite o nome que quer remover: ");
    scanf(" %s",pal);
    remove_nome(&cabeca, pal);
    apresentar_lista(cabeca);

    apagar(&cabeca);
    apresentar_lista(cabeca);

    if(vazia())
        printf("LISTA VAZIA\n");
    else
        printf("LISTA NÃO ESTÁ VAZIA\n");

}