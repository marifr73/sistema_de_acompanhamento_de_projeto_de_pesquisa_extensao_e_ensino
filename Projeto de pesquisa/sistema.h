#ifndef SISTEMA_H  
#define SISTEMA_H 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados Dados;

typedef struct no No;

typedef enum tipo Tipo;

typedef enum situacao Situacao;

typedef struct nome Nome;

void adicionar_projeto(No **lista);

void imprimir_projeto(No *lista);

void lista_projeto(No *lista);

void excluir_projeto(No **lista, int codigo_identificador);

void abrir_arquivo(No *lista, char *nome_arquivo);

void ler_arquivo(No **lista, char *nome_arquivo);

void liberar_lista(No *lista);

#endif //SISTEMA_H
