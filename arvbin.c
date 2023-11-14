#include "bigbro.h"


//funcoes gerais
void removeTNL(char *cpf) {
    int length = strlen(cpf);
    if (length > 0 && cpf[length - 1] == '\n') {
        cpf[length - 1] = '\0';
    }
}

int compara_cpf(char* a, char* b) {
        if (strlen(a) < 8 || strlen(b) < 8) {
        return 2;
    }
    for(int i = 0; i < 8; i++) {
        if(a[i] > b[i])
            return 1;
        if(a[i] < b[i])
            return -1;
    }
    return 0;
}

//funcoes arvore
ArvBin* planta_arvore(void) {
    ArvBin* raiz = (ArvBin*)malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

int adiciona_arvore(ArvBin* raiz, char* cpf, int status) {
    if(raiz == NULL) {
        return 0;
    }
    struct No* novo;
    novo = (struct No*)malloc(sizeof(struct No));
    if(novo == NULL){
        return 0;
    }
    strcpy(novo->cpf, cpf);
    removeTNL(novo->cpf);
    novo->status = status;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL) {
        *raiz = novo;
    }
    else {
        struct No* atual = *raiz;
        struct No* ant = NULL;
        while(atual != NULL){
                ant = atual;
                if(compara_cpf(cpf, atual->cpf) == 0){
                    free(novo);
                    return 0;
                }
                if(compara_cpf(cpf, atual->cpf) == 1)
                    atual = atual->dir;
                else
                    atual = atual->esq;
        }
                if(compara_cpf(cpf, ant->cpf) == 1)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

struct No* acha_arvbin(ArvBin* raiz, char *cpf, int *contador) {
    if(raiz == NULL)
    return NULL;
    struct No* atual = *raiz;
    *contador = 0;
    while(atual != NULL){
        (*contador)++;
        if(compara_cpf(cpf, atual->cpf) == 0){
            return atual;
        }
        if(compara_cpf(cpf, atual->cpf) == 1)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return NULL;
}

void imprime_arvore(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%s %d\n",(*raiz)->cpf, (*raiz)->status);
        imprime_arvore(&((*raiz)->esq));
        imprime_arvore(&((*raiz)->dir));
    }
}

//funcoes lista

struct No* criaNo(char cpf[9], int status) {
    struct No* novo = (struct No*)malloc(sizeof(struct No));
    if (novo != NULL) {
        strcpy(novo->cpf, cpf);
        novo->status = status;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

void imprime_lista(struct ListaDupla *lista) {
    struct No *atual = lista->cabeca;
    while (atual != NULL) {
        printf("%s %d\n", atual->cpf, atual->status);
        atual = atual->dir;
    }
}

struct No* acha_lista(struct ListaDupla *lista, char cpf[9], int* contador) {
    struct No *atual = lista->cabeca;
    if(contador != NULL)
    *contador = 0;
    while (atual != NULL) {
        if(contador != NULL)
        (*contador)++;
        int comparacao = compara_cpf(cpf, atual->cpf);
        if (comparacao == 0) {
            return atual;
        } else if (comparacao == -1) {
            return NULL; 
        }
        atual = atual->dir;
    }
    return NULL;
}

int adiciona_ord_lista(struct ListaDupla *lista, char cpf[9], int status) {

    if (acha_lista(lista, cpf, NULL) != NULL) {
        return 0;
    }
    struct No* novo = criaNo(cpf, status);
    if (lista->cabeca == NULL) {
        lista->cabeca = novo;
    } else {
        struct No* atual = lista->cabeca;
        struct No* anterior = NULL;
        // Encontrar o local correto na lista para inserir o novo nó
        while (atual != NULL && compara_cpf(cpf, atual->cpf) > 0) {
            anterior = atual;
            atual = atual->dir;
        }
        // Inserir o novo nó na posição correta
        if (anterior == NULL) {
            // Inserir no início da lista
            novo->dir = lista->cabeca;
            lista->cabeca->esq = novo;
            lista->cabeca = novo;
        } else {
            // Inserir no meio ou no final da lista
            novo->dir = atual;
            novo->esq = anterior;
            anterior->dir = novo;
            if (atual != NULL) {
                atual->esq = novo;
            }
        }
    }
    return 1;
}