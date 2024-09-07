#include "sistema.h"

enum situacao {
    andamento = 1,
    concluido,
    cancelado
};

enum tipo {
    pesquisa = 1,
    estensao,
    ensino
};

union nome {  
    char titulo_projeto[50];  
    char coordenador[50];  
    char alunos_envolvidos[100];  
    char orgao_financeiro[20];  
};

struct dados {
    int codigo_identificador;
    int data_inicio;
    int data_termino;
    char descricao_do_projeto[300];
    Nome nome;
    Tipo tipo;
    Situacao situacao;
};

Dados* alocar_dados(int total) {
    Dados *dados = malloc(total * sizeof(Dados));
    if (dados == NULL) {
        printf("No memory!\n");
        exit(1);
    }
    return dados;
}

void adicionar_projeto(Dados *dados) {
    do {
        printf("Informe o tipo do seu projeto: \n1. Pesquisa\n2. Extensão\n3. Ensino\n4. Sair\n");
        scanf("%d", &dados->tipo);
        getchar();

        switch (dados->tipo) {
            case 1:
                dados->tipo = pesquisa;
                strcpy(dados->descricao_do_projeto, "Pesquisa");
                printf("Título do projeto: ");
                scanf(" %[^\n]", dados->nome.titulo_projeto);
                getchar();
                printf("Informe o código do projeto: ");
                scanf("%d", &dados->codigo_identificador);
                printf("Data de inicio: ");
                scanf("%d/%d/%d", &dados->data_inicio, &dados->data_inicio, &dados->data_inicio);
                break;

            case 2:
                dados->tipo = estensao;
                strcpy(dados->descricao_do_projeto, "Extensão");
                printf("Título do projeto: ");
                scanf(" %[^\n]", dados->nome.titulo_projeto);
                getchar();
                printf("Informe o código do projeto: ");
                scanf("%d", &dados->codigo_identificador);
                printf("Data de inicio: ");
                scanf("%d/%d/%d", &dados->data_inicio, &dados->data_inicio, &dados->data_inicio);
                break;

            case 3:
                dados->tipo = ensino;
                strcpy(dados->descricao_do_projeto, "Ensino");
                printf("Título do projeto: ");
                scanf(" %[^\n]", dados->nome.titulo_projeto);
                getchar();
                printf("Informe o código do projeto: ");
                scanf("%d", &dados->codigo_identificador);
                printf("Data de inicio: ");
                scanf("%d/%d/%d", &dados->data_inicio, &dados->data_inicio, &dados->data_inicio);
                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Tipo não encontrado!\n");
                break;
        }
    } while (dados->tipo != 4);
}
