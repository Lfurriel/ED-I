#include <stdio.h>
#include <locale.h>
#include "rubro-negra.c"

/**
 * Função principal do programa. Nela serão fornecidas opções ao usuário para testar as propriedades da
 * árvore binária (inserção, remoção, busca binária, entre outras)
 * 
 * @note Autores: Bianca Lançoni de Oliveira, Gabriel Scarano de Oliveira, Júlia Rodrigues Marques do Nascimento, 
 * Lucas Furriel Rodrigues, Pedro Benedicto de Melo Cardana
 * @return 0 ao finalizar a execução.
*/
int main() {
   char input[100];

   setlocale(LC_ALL, "pt_BR.utf8");

   NO *raiz = NULL, *busca;
   int escolha, elem, qtd;

   do {
      escolha = menu();
      switch (escolha) {
         case 0:
            printf("ADEUS!");
            break;

         case 1:
            printf("Digite quantos nos deseja inserir: ");
            fgets(input, sizeof(input), stdin);
            qtd = strtol(input, NULL, 10);

            for (int i = 0; i < qtd; i++) {
               printf("Digite o valor a ser inserido: ");
               fgets(input, sizeof(input), stdin);
               elem = strtol(input, NULL, 10);
               if (!raiz) {
                  raiz = novo_no(elem, NULL);
                  raiz->cor = PRETO;
                  printf("No inserido com sucesso!\n");
               } else {
                  if (insere_no(&raiz, elem))
                     printf("No inserido com sucesso!\n");
                  else
                     printf("Erro ao inserir no\n");
               }
            }
            break;

         case 2:
            printf("Digite o valor a ser deletado: ");
            fgets(input, sizeof(input), stdin);
            elem = strtol(input, NULL, 10);
            if (deleta_no(&raiz, elem))
               printf("No deletado com sucesso\n");
            else
               printf("Erro ao deletar no\n");
            break;

         case 3:
            if (raiz)
               em_ordem(raiz);
            else
               printf("Arvore vazia!\n");
            break;

         case 4:
            if (raiz)
               pos_ordem(raiz);
            else
               printf("Arvore vazia!\n");
            break;

         case 5:
            if (raiz)
               pre_ordem(raiz);
            else
               printf("Arvore vazia!\n");
            break;

         case 6:
            if (raiz)
               imprime_arvore(raiz, 0);
            else
               printf("Arvore vazia!\n");
            break;

         case 7:
            busca = NULL;
            printf("Digite o valor a ser procurado: ");
            fgets(input, sizeof(input), stdin);
            elem = strtol(input, NULL, 10);
            busca = busca_binaria(raiz, elem);
            if (busca != NULL) {
               printf("Elemento encontrado: ");
               printa_no(busca, "\n");
            } else
               printf("Elemento nao encontrado!\n");
            break;
         case 8:
            if (raiz) {
               qtd = conta_nos_pretos(raiz);
               printf("Existem %d nos " ANSI_BLACK "pretos" ANSI_BLACK, qtd);
            } else
               printf("Arvore vazia!\n");
            break;

         case 9:
            if (raiz) {
               qtd = calcula_altura(raiz);
               printf("Altura da arvore: %d", qtd);
            } else
               printf("Arvore vazia!\n");
            break;
         case 10:
            if (raiz) {
               qtd = num_total_nos(raiz);
               printf("Arvore tem %d nos", qtd);
            } else
               printf("Arvore vazia!\n");
            break;

         case 11:
            raiz = expurgar_arvore(raiz);
            break;

         default:
            printf("Opcao invalida\n");
            break;
      }
   } while (escolha);

   return 0;
}