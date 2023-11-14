#include "bigbro.h"

int main() {
    ArvBin* arvore = planta_arvore();
    int contador_arvbin;
    int contador_lista;
    int stts;
    struct ListaDupla lista = {NULL};
    FILE* fpt;
    fpt = fopen("arq.txt", "r");
    if(fpt == NULL) {
        printf("Erro ao ler o arquivo...");
        return 0;
    }
    char* cpf = (char*)malloc(9*sizeof(char));
    int status;
    int nos = 0;
    int nos_ab;
    int nos_ld;
    while (fscanf(fpt, "%8s", cpf) == 1 && fscanf(fpt, "%d", &status) == 1) {
        if (strcmp(cpf, "x") == 0) {
            break;
        }
        nos_ab = adiciona_arvore(arvore, cpf, status);
        nos_ld = adiciona_ord_lista(&lista, cpf, status);
        if(nos_ab == 1 && nos_ld == 1)
        nos++;
    }
    fclose(fpt);


    int opc = 0;
        //printf("Digite a opcao desejada:\n0 - Ver numero de nos;\n1 - Procurar por CPF;\n2 - Exibir a lista encadeada;\n3 - Exibir arvore binaria.\n");
        {char* texto = (char*)calloc(11, sizeof(char));
        fgets(texto, 11, stdin);
        if(texto[0] == '1'){
            for(int i = 0; i < 8; i++){
                cpf[i] = texto[i+2];
            }
            opc = 1;
        }
        opc = (texto[0] == '0') ? 0 : opc;
        opc = (texto[0] == '2') ? 2 : opc;
        opc = (texto[0] == '3') ? 3 : opc;
        } //parte para colher a opcao do usuario
        switch(opc) {
            case 0:
                printf("NL:%d NA:%d", nos, nos);
                printf("\n");
                break;
            case 1:
                //printf("Digite o CPF que deseja buscar:\n");
                removeTNL(cpf);
                struct No* atual_ab = acha_arvbin(arvore, cpf, &contador_arvbin);
                struct No* atual_ld = acha_lista(&lista, cpf, &contador_lista);
                    if(atual_ld != NULL && atual_ab != NULL){
                        stts = atual_ld->status;
                    }
                    else
                        stts = -1;
                printf("S:%d NL:%d NA:%d", stts, contador_lista, contador_arvbin);
                printf("\n");
                break;
            case 2: 
                imprime_lista(&lista);
                break;
            case 3:
                imprime_arvore(arvore);
                break;
            default:
                //printf("Opcao invalida...");
                break;
        }
    return 0;
}