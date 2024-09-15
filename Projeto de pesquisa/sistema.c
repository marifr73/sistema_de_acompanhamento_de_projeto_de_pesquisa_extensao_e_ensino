#include "sistema.h"

enum situacao{
    concluido = 1,
    andamento,
    cancelado
};

enum tipo{
    pesquisa = 1,
    extensao,
    ensino
};

union nome{  
    char titulo_projeto[50];  
    char coordenador[50];  
    char alunos_envolvidos[10][50];  
    char orgao_financeiro[20];  
};

struct dados {
    int codigo_identificador;
    char data_inicio[11];
    char data_termino[11];
    char descricao_do_projeto[300];
    Nome nome;
    Tipo tipo;
    Situacao situacao;
};

struct no {
    Dados projeto;
    struct no *prox;
};

No* alocar_no() {
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("Sem memória!\n");
        exit(1);
    }
    novo->prox = NULL;
    return novo;
}

void adicionar_projeto(No **lista) {
    No *novo = alocar_no();
    int alunos, i, orgao_fi;
    
    printf("Informe o tipo do seu projeto: \n1. Pesquisa\n2. Extensão\n3. Ensino\n");
    scanf("%d", &novo->projeto.tipo);
    getchar();

    switch (novo->projeto.tipo) {
        case 1:
            novo->projeto.tipo = pesquisa;
            strcpy(novo->projeto.descricao_do_projeto, "Pesquisa");

            printf("Título do projeto: ");
            scanf(" %[^\n]", novo->projeto.nome.titulo_projeto);
            getchar();

            printf("\nInforme o código do projeto: ");
            scanf("%d", &novo->projeto.codigo_identificador);

            printf("\nData de início (Dia/Mês/Ano): ");  
            scanf(" %[^\n]", novo->projeto.data_inicio); 
            getchar();

            printf("\nSituação do projeto: \n1. Concluido\n2. Andamento\n3. Cancelado\n");
            scanf("%d", &novo->projeto.situacao);

            if (novo->projeto.situacao == 1) {
                printf("\nData de Termino (Dia/Mês/Ano): ");
                scanf(" %[^\n]", &novo->projeto.data_termino);
                getchar();
            } else if(novo->projeto.situacao == 2) {
                printf("\nProjeto em andamento!\n");
            } else if(novo->projeto.situacao == 3){
                printf("\nProjeto Cancelado!\n");
            } else{
                printf("Código não identificado!");
            }

            printf("\nInforme o nome do coordenador: ");
            scanf(" %[^\n]", novo->projeto.nome.coordenador);
            getchar();

            printf("\nInforme o numero total de alunos envolvidos: ");  
            scanf("%d", &alunos);  
            getchar();

            for (i = 0; i < alunos; i++){  
                printf("Nome do aluno %d: ", i + 1);  
                scanf(" %[^\n]", novo->projeto.nome.alunos_envolvidos[i]);
                getchar();  
            }

            printf("\nHá órgão financeiro? \n1. Sim\n2. Não\n");
            scanf("%d", &orgao_fi);
            getchar();

            if (orgao_fi == 1) {
                printf("\nInforme o nome do órgão financeiro: ");
                scanf(" %[^\n]", novo->projeto.nome.orgao_financeiro);
                getchar();
            } else if (orgao_fi == 2) {
                printf("\nNão há orgão financeiro!");
            } else{
                printf("Código não identificado!");
            }

            printf("\nDescreva o seu projeto: ");
            scanf(" %[^\n]", novo->projeto.descricao_do_projeto);
            getchar();
            break;

        case 2:
            novo->projeto.tipo = extensao;
            strcpy(novo->projeto.descricao_do_projeto, "Extensão");

            printf("Título do projeto: ");
            scanf(" %[^\n]", novo->projeto.nome.titulo_projeto);
            getchar();

            printf("\nInforme o código do projeto: ");
            scanf("%d", &novo->projeto.codigo_identificador);

            printf("\nData de início (Dia/Mês/Ano): ");  
            scanf(" %[^\n]", novo->projeto.data_inicio); 
            getchar();

            printf("\nSituação do projeto: \n1. Concluido\n2. Andamento\n3. Cancelado\n");
            scanf("%d", &novo->projeto.situacao);

            if (novo->projeto.situacao == 1) {
                printf("\nData de Termino (Dia/Mês/Ano): ");
                scanf(" %[^\n]", &novo->projeto.data_termino);
                getchar();
            } else if(novo->projeto.situacao == 2) {
                printf("\nProjeto em andamento!\n");
            } else if(novo->projeto.situacao == 3){
                printf("\nProjeto Cancelado!\n");
            } else{
                printf("Código não identificado!");
            }

            printf("\nInforme o nome do coordenador: ");
            scanf(" %[^\n]", novo->projeto.nome.coordenador);
            getchar();

            printf("\nInforme o numero total de alunos envolvidos: ");  
            scanf("%d", &alunos);  
            getchar();

            for (i = 0; i < alunos; i++){  
                printf("Nome do aluno %d: ", i + 1);  
                scanf(" %[^\n]", novo->projeto.nome.alunos_envolvidos[i]);
                getchar();  
            }

            printf("\nHá órgão financeiro? \n1. Sim\n2. Não\n");
            scanf("%d", &orgao_fi);
            getchar();

            if (orgao_fi == 1) {
                printf("\nInforme o nome do órgão financeiro: ");
                scanf(" %[^\n]", novo->projeto.nome.orgao_financeiro);
                getchar();
            } else if (orgao_fi == 2) {
                printf("\nNão há orgão financeiro!");
            } else{
                printf("Código não identificado!");
            }

            printf("\nDescreva o seu projeto: ");
            scanf(" %[^\n]", novo->projeto.descricao_do_projeto);
            getchar();
            break;

        case 3:
            novo->projeto.tipo = ensino;
            strcpy(novo->projeto.descricao_do_projeto, "Ensino");

            printf("Título do projeto: ");
            scanf(" %[^\n]", novo->projeto.nome.titulo_projeto);
            getchar();

            printf("\nInforme o código do projeto: ");
            scanf("%d", &novo->projeto.codigo_identificador);

            printf("\nData de início (Dia/Mês/Ano): ");  
            scanf(" %[^\n]", novo->projeto.data_inicio); 
            getchar();

            printf("\nSituação do projeto: \n1. Concluido\n2. Andamento\n3. Cancelado\n");
            scanf("%d", &novo->projeto.situacao);

            if (novo->projeto.situacao == 1) {
                printf("\nData de Termino (Dia/Mês/Ano): ");
                scanf(" %[^\n]", &novo->projeto.data_termino);
                getchar();
            } else if(novo->projeto.situacao == 2) {
                printf("\nProjeto em andamento!\n");
            } else if(novo->projeto.situacao == 3){
                printf("\nProjeto Cancelado!\n");
            } else{
                printf("Código não identificado!");
            }

            printf("\nInforme o nome do coordenador: ");
            scanf(" %[^\n]", novo->projeto.nome.coordenador);
            getchar();

            printf("\nInforme o numero total de alunos envolvidos: ");  
            scanf("%d", &alunos);  
            getchar();

            for (i = 0; i < alunos; i++){  
                printf("Nome do aluno %d: ", i + 1);  
                scanf(" %[^\n]", novo->projeto.nome.alunos_envolvidos[i]);
                getchar();  
            }

            printf("\nHá órgão financeiro? \n1. Sim\n2. Não\n");
            scanf("%d", &orgao_fi);
            getchar();

            if (orgao_fi == 1) {
                printf("\nInforme o nome do órgão financeiro: ");
                scanf(" %[^\n]", novo->projeto.nome.orgao_financeiro);
                getchar();
            } else if (orgao_fi == 2) {
                printf("\nNão há orgão financeiro!");
            } else{
                printf("Código não identificado!");
            }

            printf("\nDescreva o seu projeto: ");
            scanf(" %[^\n]", novo->projeto.descricao_do_projeto);
            getchar();
            break;     

            default:
            printf("Tipo inválido!\n");
            free(novo);
            return;
    }

    novo->prox = *lista;
    *lista = novo;
}

void imprimir_projeto(No *lista) {
    while (lista != NULL) {
        printf(" --- Título do projeto ---\n");
        printf("%s\n", lista->projeto.nome.titulo_projeto);

        printf(" --- Código do projeto ---\n");
        printf("%d\n", lista->projeto.codigo_identificador);

        printf(" --- Data de início ---\n");
        printf("%s\n", lista->projeto.data_inicio);

        printf(" --- Situação ---\n");
        switch (lista->projeto.situacao) {
            case concluido:
                printf("Concluído\n");
                break;
            case andamento:
                printf("Andamento\n");
                break;
            case cancelado:
                printf("Cancelado\n");
                break;
            default:
                printf("Situação desconhecida\n");
                break;
        }

        printf(" --- Data de Término ---\n");
        printf("%s\n", lista->projeto.data_termino);

        printf(" --- Coordenador ---\n");
        printf("%s\n", lista->projeto.nome.coordenador);
        
        printf(" --- Alunos Envolvidos ---\n");
        int i = 0;
        while (i < 10 && lista->projeto.nome.alunos_envolvidos[i][0] != '\0') {
            printf("%s\n", lista->projeto.nome.alunos_envolvidos[i]);
            i++;
        }

        printf(" --- Órgão Financeiro ---\n");
        printf("%s\n", lista->projeto.nome.orgao_financeiro);

        printf(" --- Descrição do Projeto ---\n");
        printf("%s\n", lista->projeto.descricao_do_projeto);

        lista = lista->prox;
    }
}

void excluir_projeto(No **lista, int codigo_identificador) {
    No *aux = *lista;
    No *ant = NULL;

    while (aux != NULL && aux->projeto.codigo_identificador != codigo_identificador) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Projeto não encontrado.\n");
        return;
    }

    if (ant == NULL) {
        *lista = aux->prox;
    } else {
        ant->prox = aux->prox;
    }

    free(aux);
    printf("Projeto foi removido com sucesso.\n");
}

void liberar_lista(No *lista) {
    No *ant = lista;
    while (ant != NULL) {
        No *temp = ant;
        ant = ant->prox;
        free(temp);
    }
}
