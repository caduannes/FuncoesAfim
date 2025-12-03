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
    
        printf("Quem você quer encontrar?\n");
        for(int i=0; i<num_Clientes; i++){
            printf("%s\n", clientes[i].nome);
        }
        scanf("%19s", destino); 
    return destino;
}

cliente* busca_Linear(cliente* clientes, size_t num_Clientes){
    
    char procurado[20];
    quemVCquerEncontrar(clientes, num_Clientes, procurado);

    for(size_t i=0;i < num_Clientes; i++){
        if(strcmp(clientes[i].nome, procurado) == 0){
            cliente* achado = &clientes[i];
            printf("A busca linear achou '%s' e o seu ID é:%d\n", achado->nome, achado->ID);
        return achado;
        }
    }
    printf("Cliente não encontrado\n");
    return NULL;
}

cliente* busca_Binaria(cliente* ordenadosNome, size_t num_Clientes){
    
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
            printf("Encontrado: %s com ID %d\n", achado->nome, achado->ID);
            return achado;
        }
        else if(c < 0){
            menor = mediano + 1;
        }else{
            if(mediano == 0) break;
            maior = mediano - 1;
        }
    }
        printf("Cliente não encontrado!\n");
        free(ordenadosNome);
    return NULL;
}

int main(){
    
    int opcao;
    cliente clientes[] = {
        {"Carlos", 10}, {"Marcondes", 50}, {"Fernando", 67}, {"Caio", 32},
        {"Gabriela", 20}, {"Pedro", 05}, {"Thiele", 16}};
        
        size_t num_Clientes = sizeof(clientes) / sizeof(cliente);
        
        printf("=====MENU=====\n");
        printf("Imprimir clientes ordenados = 0\n");
        printf("Buscar linearmente = 1\n");
        printf("Buscar binariamente = 2\n");
        printf("Buscar por Hash = 3\n");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 0:
                cliente* ordenadosID = ordenar_ClientesID(clientes, num_Clientes);
                if (ordenadosID) {
                    printf("Clientes ordenados por ID:\n");
                for (size_t i = 0; i < num_Clientes; i++) {
                    printf("%d - %s\n", ordenadosID[i].ID, ordenadosID[i].nome);
                }
                    free(ordenadosID);
                }
                break;
            case 1:
                busca_Linear(clientes, num_Clientes);
                break;
            case 2:
                cliente* ordenadosNome = ordenar_ClientesNome(clientes, num_Clientes);
                busca_Binaria(ordenadosNome, num_Clientes);
                break;
            case 3:
                //busca_Hash();
                break;
            default:
                printf("Opção invalida\n");
            break;
        }
    return 0;
}
