//TAD: matriz real m x n (m: linhas e n: colunas)

//Tipo Exportado 
typedef struct matriz Matriz;

//Funções exportadas
//------------------------------------------------------
//Funções cria: aloca e retorna matriz m x n
Matriz *cria(int m, int n);

//Funções libera: libera a mem�ria de uma matriz
void libera(Matriz *mat);

//Funções acessa: retorna o valor do elemento [i][j]
float acessa(Matriz *mat, int i, int j);

//Funções atribui: atribui valor ao elemento [i][j]
void atribui(Matriz* mat, int i, int j, float v);

//Funções linhas: retorna nro de linhas da matriz
int linhas(Matriz* mat);

//Funções colunas: retorna nro de colunas da matriz
int colunas(Matriz* mat);
//------------------------------------------------------

