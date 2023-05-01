typedef struct no {
    int chave;
    struct no *esq;
    struct no *dir;
} tipo_no;

tipo_no *Rotacao_esquerda(tipo_no *no) {
    tipo_no *dir = no->dir;
    tipo_no *esq = dir->esq;

    dir->esq = no;
    no->dir = esq;

    no->altura = maior(altura(no->esq), altura(no->dir) + 1);
    dir->altura = maior(altura(dir->esq), altura(dir->dir) + 1);

    return dir;
}

tipo_no *Rotacao_direita(tipo_no *no) {
    tipo_no *esq = no->esq;
    tipo_no *dir = esq->dir;

    esq->dir = no;
    no->esq = dir;

    no->altura = maior(altura(no->esq), altura(no->dir) + 1);
    esq->altura = maior(altura(esq->esq), altura(esq->dir) + 1);

    return esq;
}

tipo_no **Rotacao_duplaDir(tipo_no *no) {
    no->esq = rotacao_esquerda(no);

    return rotacao_direita(no);
}

tipo_no Rotacao_duplaEsq(tipo_no *no) {
    no->dir = rotacao_direita(no);

    return rotacao_esquerda(no);
}