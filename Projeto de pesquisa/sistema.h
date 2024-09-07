#ifndef SISTEMA_H  
#define SISTEMA_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados Dados;

typedef enum tipo Tipo;

typedef enum situacao Situacao;

typedef union nome Nome;

Dados* alocar_dados(int total);

void adicionar_projeto(Dados *dados);

#endif
