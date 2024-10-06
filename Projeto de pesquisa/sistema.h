#ifndef SISTEMA_H  
#define SISTEMA_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados Dados;

typedef struct data Data;

typedef struct no No;

typedef struct nome Nome;

typedef enum tipo Tipo;

typedef enum situacao Situacao;

/* Função que aloca memória para um novo nó da lista e retorna um ponteiro para o nó 
- Parâmetro int id: ID para o nó, utilizado para diferenciar cada nó na lista*/
No *alocar_no(int id);

/* Função que verifica se a data informada é válida e retorna 1 se for verdade e 0 se for falso 
- Parâmetros: int dia, int mes, int ano: Representam o dia, mês e ano da data que será verificada*/
int verificar_data(int dia, int mes, int ano);

/* Função que adiciona um novo projeto à lista e salva os dados no arquivo após adicionar o projeto 
-Parâmetros: No **lista: Ponteiro para o ponteiro da lista onde o novo projeto será adicionado
             int *proximo_id: Ponteiro para o próximo ID a ser usado
             char *nome_arquivo: Nome do arquivo onde os dados serão salvos
*/
void adicionar_projeto(No **lista, int *proximo_id, char *nome_arquivo);

/* Função que imprime todos os projetos da lista 
-Parâmetro No *lista: Ponteiro para a lista que contém os projetos
*/
void listar_projeto(No *lista);

/* Função que exclui um projeto da lista com base no ID informado
-Parâmetros: No **lista: Ponteiro para o ponteiro da lista
             int id_unico: ID do projeto a ser excluído
*/
void excluir_projeto(No **lista, int id_unico);

/* Função que salva todos os projetos da lista no arquivo
-Parâmetros: No *lista: Ponteiro para a lista que contém os projetos.
             char *nome_arquivo: Nome do arquivo onde os dados serão salvos.
*/
void abrir_arquivo(No *lista, char *nome_arquivo);
 
/* Função que lê os dados dos projetos do arquivo especificado e os carrega na lista, atualizando o ID 
-Parâmetros: No **lista: Ponteiro para o ponteiro da lista onde os projetos serão carregados.
             char *nome_arquivo: Nome do arquivo de onde os dados serão lidos.
             int *proximo_id: Ponteiro para o próximo ID, que será atualizado durante a leitura.*/
void ler_arquivo(No **lista, char *nome_arquivo, int *proximo_id);

/* Função que consulta e exibe os projetos da lista com base no tipo de projeto 
-Parâmetro No *lista: Ponteiro para a lista encadeada que contém os projetos*/
void consultar_projeto_por_tipo(No *lista);

/* Função que consulta e exibe os projetos da lista com base na situação do projeto 
-Parâmetro No *lista: Ponteiro para a lista  que contém os projetos*/
void consultar_projeto_por_situacao(No *lista);

/* Função que exibe todas as informações de um único projeto
-Parâmetro No *projeto: Ponteiro para o projeto que terá suas informações exibidas. */
void listar_projeto_unico(No *projeto);

/* Função que busca um projeto específico na lista com base no código identificador e exibe suas informações  
-Parâmetro No *lista: Ponteiro para a lista que contém os projetos.*/
void buscar_projeto_por_codigo(No *lista);

/* Função que edita os dados de um projeto existente na lista 
-Parâmetro No *lista: Ponteiro para a lista que contém os projetos*/
void editar_dados_do_projeto(No *lista);

/* Função que libera a memória alocada
-Parâmetro No *lista: Ponteiro para a lista cuja memória será liberada.*/
void liberar_lista(No* lista);

#endif
