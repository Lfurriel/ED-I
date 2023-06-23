# Árvore Binária de Busca

Implementação de uma árvore binária de busca, apresentamos as seguintes funções:

~~~ c
tipo_no* cria_raiz(tipo_no *raiz, tipo_elem elem);
tipo_no* insere(tipo_no *raiz, tipo_elem elem);
tipo_no* busca_binaria_recursiva(tipo_no *raiz, tipo_elem elem);
tipo_no* busca_binaria_interativo(tipo_no *raiz, tipo_elem elem);
tipo_no* remover(tipo_no *raiz,  tipo_elem elem);
tipo_no *maior_esquerda(tipo_no *raiz);
tipo_no *menor_direita(tipo_no *raiz);
void expurgar(tipo_no **raiz);
void in_order(tipo_no *raiz);
~~~

Apresenta também as structs:

~~~ c
struct elem {
    tipo_chave chave;
};

struct no {
    tipo_elem elem;
    struct no *esq;
    struct no *dir;
};
~~~

## Implementação de funções

Explicação sobre as funções

### **cria_raiz**

Aloca e cria um novo nó

### **insere**

Função recursiva para inserção de um novo elemento na árvore.
Busca uma nova folha para inserir. Por se tratar de uma árvore binária, essa busca é feita com uso de '<' e '>'.

Caso novo elemento seja < que o elemento já inserido -> caminhamos para o filho da esquerda.

Caso novo elemento seja > que o elemento já inserido -> caminhamos para o filho da direita.

### **busca_binaria_recursiva**

Como o próprio nome diz é uma busca de elemento de forma recursiva.

Caso o elemento procurado seja menor que o nó atual -> caminhamos pra esquerda.

Caso o elemento procurado seja maior que o nó atual -> caminhamos pra direita.

### **busca_binaria_interativa**

Funciona da mesma forma que a busca recursiva porém dessa vez estamos em um laço *while*.

### **remover**

Nessa função buscamos de forma recursiva o elemento a ser removido e em seguida tratamos de 3 casos para remoção:

Caso 1 -> Elemento removido é uma folha. Neste caso apenas removemos da memória o nó.

Caso 2 -> Elemento removido apresenta apenas um único filho. Neste caso passamos o filho (a direita ou a esquerda) para a posição do pai e em seguida removemos da memória o nó.

Caso 3 -> Elemento removido apresenta dois filhos. Podemos tratar esse caso de duas formas, a primeira é mudar o nó a ser removido pelo maior elemento da sub-árvore a esquerda ou mudar o nó removido pelo menor elemento da sub-árvore a direita.

### **maior_esquerda**

Busca o maior elemento da sub-árvore a esquerda.

### **menor_direita**

Busca o menor elemento da sub-árvore a direita.

### **expurgar**

Passa por todos os nós da árvore limpando da memória.

### **in_order**

Printa elementos da árvore em ordem.
