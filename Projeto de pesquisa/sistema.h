#ifndef SISTEMA_H  
#define SISTEMA_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados Dados;

typedef struct no No;

typedef enum tipo Tipo;

typedef enum situacao Situacao;

typedef union nome Nome;

No* alocar_no();

void adicionar_projeto(No **lista);

void imprimir_projeto (No *lista);

void excluir_projeto(No **lista, int codigo_identificador);

void liberar_lista(No *lista);

#endif
