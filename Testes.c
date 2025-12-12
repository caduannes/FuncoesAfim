#include "Cliente.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* nome;
    int ID;
} cliente;

cliente* ordenar_ClientesID(cliente* clientes, size_t num_Clientes){

    cliente* ordenado = malloc(num_Clientes * sizeof(cliente));
    if (!ordenado) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    for (size_t i = 0; i < num_Clientes; i++) {
        ordenado[i] = clientes[i];
    }

    for(size_t i=0; i<num_Clientes - 1; i++){
        for(size_t j=0; j<num_Clientes - i - 1; j++){
            if(ordenado[j].ID > ordenado[j+1].ID){
                cliente temp = ordenado[j];
                ordenado[j] = ordenado[j+1];
                ordenado[j+1] = temp;
            }
        }
    }
    return ordenado;
}

cliente* ordenar_ClientesNome(cliente* clientes, size_t num_Clientes) {
    cliente* ordenado = malloc(num_Clientes * sizeof(cliente));
    if (!ordenado) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    for (size_t i = 0; i < num_Clientes; i++) {
        ordenado[i] = clientes[i];
    }
    for (size_t i = 0; i < num_Clientes - 1; i++) {
        for (size_t j = 0; j < num_Clientes - i - 1; j++) {
            if (strcmp(ordenado[j].nome, ordenado[j + 1].nome) > 0) {
                cliente temp = ordenado[j];
                ordenado[j] = ordenado[j + 1];
                ordenado[j + 1] = temp;
            }
        }
    }
    return ordenado;
}

char* quemVCquerEncontrar(cliente* clientes, size_t num_Clientes, char destino[]){

        printf("Quem voce quer encontrar?\n");
        for(int i=0; i<num_Clientes; i++){
            printf("%s\n", clientes[i].nome);
        }
        scanf("%19s", destino);
    return destino;
}

cliente* busca_Linear(cliente* clientes, size_t num_Clientes){

    cliente* ordenadosNome = ordenar_ClientesNome(clientes, num_Clientes);

    char procurado[20];
    quemVCquerEncontrar(ordenadosNome, num_Clientes, procurado);

    for(size_t i=0;i < num_Clientes; i++){
        if(strcmp(clientes[i].nome, procurado) == 0){
            cliente* achado = &clientes[i];
            printf("'%s', ID:%d\n", achado->nome, achado->ID);
        return achado;
        }
    }
    printf("Cliente nao encontrado\n");
    return NULL;
}

cliente* busca_Binaria(cliente* clientes, size_t num_Clientes){

    cliente* ordenadosNome = ordenar_ClientesNome(clientes, num_Clientes);

    if(num_Clientes + num_Clientes < num_Clientes){
        return NULL;
    }

    char procurado[20];
    quemVCquerEncontrar(ordenadosNome, num_Clientes, procurado);

    size_t menor = 0;
    size_t maior = num_Clientes - 1;

    while(menor <= maior){
        size_t mediano = (menor + maior) / 2;
        int c = strcmp(ordenadosNome[mediano].nome, procurado);

        if(c == 0){
            cliente* achado = &ordenadosNome[mediano];
            printf("'%s', ID:%d\n", achado->nome, achado->ID);
            return achado;
        }
        else if(c < 0){
            menor = mediano + 1;
        }else{
            if(mediano == 0) break;
            maior = mediano - 1;
        }
    }
        printf("Cliente nao encontrado!\n");
        free(ordenadosNome);
    return NULL;
}

int main(){



        //do{
        //printf("=====MENU=====\n");
        //printf("1 = Imprimir clientes ordenados\n");
        //printf("2 = Buscar linearmente\n");
        //printf("3 = Buscar binariamente\n");
        //printf("4 = Buscar por Hash\n");
        //printf("0 = Sair\n");
        //scanf("%d", &opcao);

        //switch(opcao){
            //case 1:
                //do{
                //printf("====MENU====\n");
                //printf("1 - Ordenados por ID\n");
                //printf("2 - Ordenados por nome\n");
                //printf("0 - Voltar\n");
                //scanf("%d", &opcaoOrdenacao);

                    //switch(opcaoOrdenacao){
                    //case 1:
                        //imprimirClientesOrdenadosID(clientes,num_Clientes);
                    //break;
                    //case 2:
                        //imprimirClientesOrdenadosNome(clientes,num_Clientes);
                    //break;
                    //case 0:
                        //printf("Saindo. . .\n");
                    //break;
                    //}
                //}while(opcaoOrdenacao != 0);
            //break;
            //case 2:
                //busca_Linear(clientes, num_Clientes);
                //break;
            //case 3:
                //busca_Binaria(clientes, num_Clientes);
                //break;
            //case 4:
                //busca_Hash();
                //break;
            //case 0:
                //printf("Saindo . . . \n");
                //break;
            //default:
                //printf("Opção invalida\n");
            //break;
        //}
        //}while(opcao != 0);
    return 0;
}
