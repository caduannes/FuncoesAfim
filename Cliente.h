#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "Cliente.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 5

typedef struct Cliente Cliente;//struct cliente

typedef struct Tabela tabelaEspalhamento;//tabela apenas com o indice e ponteiro apontando para o começo das listas

int funcaoEspalhamento(int ID);

void alocado(void* ponteiro);

void limparBuffer();

Cliente* alterarDados(Cliente* novo);

Cliente* criar(tabelaEspalhamento** TABELA);

Cliente* procurar(tabelaEspalhamento** TABELA);

void editar(tabelaEspalhamento** TABELA);

void imprimir(tabelaEspalhamento** TABELA);

void remover(tabelaEspalhamento** TABELA);

int manipularCLientes();

#endif // CLIENTE_H_INCLUDED
