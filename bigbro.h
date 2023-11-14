#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct No{
    char cpf[9];
    int status;
    struct No *esq;
    struct No *dir;
};

struct ListaDupla {
    struct No *cabeca;
};

typedef struct No* ArvBin;
typedef struct No* Lista;


//funcoes gerais
int compara_cpf(char* a, char* b);
void removeTNL(char* cpf);

//funcoes da arvore
ArvBin* planta_arvore();
int adiciona_arvore(ArvBin* raiz, char *cpf, int status);
struct No* acha_arvbin(ArvBin* raiz, char *cpf, int* contador);
void imprime_arvore(ArvBin* raiz);

//funcoes da lista
Lista* comeca_lista();
int adiciona_ord_lista(struct ListaDupla* comeco, char* cpf, int status);
struct No* acha_lista(struct ListaDupla *lista, char* cpf, int* contador);
void imprime_lista(struct ListaDupla *lista);
struct No* acha_lista(struct ListaDupla *lista, char cpf[9], int* contador);
