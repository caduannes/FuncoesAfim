#include "Cliente.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 5

typedef struct Cliente{
    int ID;
    char nome[30];
    struct Cliente* proximo;
    struct Cliente* anterior;
} Cliente;//struct cliente

typedef struct Tabela{
    int indice;
    Cliente* cabeca;
} tabelaEspalhamento;//tabela apenas com o indice e ponteiro apontando para o começo das listas

tabelaEspalhamento* TABELA[TAMANHO_TABELA];

int funcaoEspalhamento(int ID) {
    return ID % TAMANHO_TABELA;
}
void alocado(void* ponteiro){
    if(!ponteiro){
    printf("Sem memoria\n");
    exit(1);
    }
}

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Cliente* alterarDados(Cliente* novo){
    Cliente* alteracao = novo;

    if(alteracao->ID == 0){
        printf("Digite seu ID: \n");
        scanf("%d", &alteracao->ID);
    }
    limparBuffer();

    printf("Digite seu nome: \n");
    fgets(alteracao->nome, 30, stdin);
    alteracao->nome[strcspn(alteracao->nome, "\n")] = '\0';

    return alteracao;
}
Cliente* criar(tabelaEspalhamento** TABELA){
    Cliente* novo = (Cliente*) malloc(sizeof(Cliente));
    alocado(novo);

    novo->ID = 0;
    novo = alterarDados(novo);
    novo->proximo = NULL;
    novo->anterior = NULL;

    int indice = funcaoEspalhamento(novo->ID);

    Cliente* CABECA = TABELA[indice]->cabeca;//faço a tabela apontar para a cabeca dessa lista
    Cliente* atual = CABECA->proximo;
    Cliente* anterior = CABECA;

    if(atual == NULL){
        CABECA->proximo = novo;
        novo->anterior = CABECA;
        return novo;
    }

        while(atual != NULL && atual->ID < novo->ID){
            anterior = atual;
            atual = atual->proximo;
        }//chegando no lugar a ser inserido o novo cliente

        if(atual != NULL && atual->ID == novo->ID){
            printf("Usuario ja cadastrado\n");
            free(novo);
            return CABECA;
        }//para usuario já cadastrado

        anterior->proximo = novo;
        novo->anterior = anterior;
        novo->proximo = atual;

        if(atual != NULL){
            atual->anterior = novo;
        }
    return novo;
}

Cliente* procurar(tabelaEspalhamento** TABELA){
    int chave;
    printf("Digite o ID a ser encontrado: \n");
    scanf("%d", &chave);

    int indice = funcaoEspalhamento(chave);
    Cliente* CABECA = TABELA[indice]->cabeca;
    Cliente* auxiliar = CABECA->proximo;

    while(auxiliar != NULL && auxiliar->ID < chave){
        auxiliar = auxiliar->proximo;
    }
    if(auxiliar != NULL && auxiliar->ID == chave){
        return auxiliar;
    }
    return NULL;
}

void editar(tabelaEspalhamento** TABELA){
    Cliente* aEditar = procurar(TABELA);

    if(aEditar == NULL){
        printf("Cliente nao encontrado\n");
        return;
    }
    alterarDados(aEditar);
    printf("Dados atualizados com sucesso\n");
    printf("ID:%d, Nome:%s\n", aEditar->ID, aEditar->nome);
}

void imprimir(tabelaEspalhamento** TABELA){
    printf("\n====== TABELA ======\n");

    for (int i = 0; i < TAMANHO_TABELA; i++){
        printf("[%d] -> ", i);

        Cliente* CABECA = TABELA[i]->cabeca;
        Cliente* auxiliar = CABECA->proximo;

        if (auxiliar == NULL) {
            printf("NULL\n");
            continue;
        }
        while (auxiliar != NULL) {
            printf("(ID:%d, Nome:%s) -> ", auxiliar->ID, auxiliar->nome);
            auxiliar = auxiliar->proximo;
        }
        printf("NULL\n");
    }
}
void remover(tabelaEspalhamento** TABELA){
    Cliente* aRemover = procurar(TABELA);
    if (aRemover == NULL) {
        printf("Cliente nao encontrado\n");
        return;
    }
    int indice = funcaoEspalhamento(aRemover->ID);

    Cliente* CABECA = TABELA[indice]->cabeca;
    Cliente* atual = CABECA->proximo;
    Cliente* anterior = CABECA;

    while(atual != NULL && atual->ID < aRemover->ID){
        anterior = atual;
        atual = atual->proximo;
    }
    if(atual == NULL || atual->ID != aRemover->ID){
        printf("Cliente nao encontrado\n");
        return;
    }
    //Removendo
       anterior->proximo = atual->proximo;
       if(atual->proximo != NULL){
            atual->proximo->anterior = anterior;
        }
        free(atual);
        printf("Removido com sucesso\n");
}
int manipularCLientes(){
    int opcao;
    tabelaEspalhamento* TABELA[TAMANHO_TABELA];

    for(int i = 0; i < TAMANHO_TABELA; i++){
        TABELA[i] = (tabelaEspalhamento*) malloc(sizeof(tabelaEspalhamento));
        alocado(TABELA[i]);
        TABELA[i]->indice = i;

        TABELA[i]->cabeca = (Cliente*) malloc(sizeof(Cliente));
        alocado(TABELA[i]->cabeca);
        TABELA[i]->cabeca->proximo = NULL;
        TABELA[i]->cabeca->anterior = NULL;
    }
    do{
        printf("======MENU======\n");
        printf("1- Para criar\n");
        printf("2- Para procurar\n");
        printf("3- Para editar\n");
        printf("4- Para imprimir\n");
        printf("5- Para remover\n");
        printf("0- Para sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                criar(TABELA);
                break;
            case 2:{
                Cliente* c = procurar(TABELA);
                if (c != NULL) {
                    printf("Cliente encontrado!\n");
                    printf("ID: %d\n", c->ID);
                    printf("Nome: %s\n", c->nome);
                } else {
                    printf("Cliente não encontrado.\n");
                }
                break;
            }
            case 3:
                editar(TABELA);
                break;
            case 4:
                imprimir(TABELA);
                break;
            case 5:
                remover(TABELA);
                break;
            case 0:
                printf("Saindo\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    }while(opcao != 0);
    return 0;
}
