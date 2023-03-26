typedef struct lista TLista;

int vazia();
int cheia();
void definir(TLista **lista);
void apagar(TLista **lista);
void insire_ordenado(TLista **lista);
void numerar(TLista *lista);
TLista* buscar_id(TLista *lista, int id);
TLista* buscar_nome(TLista *lista, char *nome);
void remove_id(TLista **lista, int id);
void remove_nome(TLista **lista, char *nome);
void apresentar_lista(TLista *lista);