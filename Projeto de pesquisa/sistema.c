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

struct nome{  
    char titulo_projeto[50];  
    char coordenador[50];  
    char alunos_envolvidos[50][50];  
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

No *alocar_no(){
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        exit(1);
    }
    novo->prox = NULL;
    return novo;
}

void adicionar_projeto(No **lista){
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        exit(1);
    }
    novo->prox = NULL;

    int alunos, i, orgao_fi, tipo_projeto, situacao_projeto;
    
    printf("Informe o tipo do seu projeto: \n1. Pesquisa\n2. Extensão\n3. Ensino\n");
    scanf("%d", &tipo_projeto);
    getchar();

    switch (tipo_projeto) {
        case 1:
            novo->projeto.tipo = pesquisa;
            strcpy(novo->projeto.descricao_do_projeto, "Pesquisa");
            break;
        case 2:
            novo->projeto.tipo = extensao;
            strcpy(novo->projeto.descricao_do_projeto, "Extensão");
            break;
        case 3:
            novo->projeto.tipo = ensino;
            strcpy(novo->projeto.descricao_do_projeto, "Ensino");
            break;
        default:
            printf("Tipo inválido!\n");
            free(novo);
            return;
    }

    printf("Título do projeto: ");
    scanf(" %[^\n]", novo->projeto.nome.titulo_projeto);
    getchar();

    printf("\nInforme o código do projeto: ");
    scanf("%d", &novo->projeto.codigo_identificador);

    printf("\nData de início (Dia/Mês/Ano): ");  
    scanf(" %[^\n]", novo->projeto.data_inicio); 
    getchar();

    printf("\nSituação do projeto: \n1. Concluído\n2. Andamento\n3. Cancelado\n");
    scanf("%d", &situacao_projeto);

    switch (situacao_projeto) {
        case 1:
            novo->projeto.situacao = concluido;
            printf("\nData de Término (Dia/Mês/Ano): ");
            scanf(" %[^\n]", novo->projeto.data_termino);
            getchar();
            break;
        case 2:
            novo->projeto.situacao = andamento;
            printf("\nProjeto em andamento!\n");
            novo->projeto.data_termino[0] = '\0';
            break;
        case 3:
            novo->projeto.situacao = cancelado;
            printf("\nProjeto Cancelado!\n");
            novo->projeto.data_termino[0] = '\0';
            break;
        default:
            printf("Código não identificado!");
            free(novo);
            return;
    }

    printf("\nInforme o nome do coordenador: ");
    scanf(" %[^\n]", novo->projeto.nome.coordenador);
    getchar();

    printf("\nInforme o número total de alunos envolvidos: ");  
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
        printf("\nNão há órgão financeiro!\n");
    } else {
        printf("Código não identificado!");
    }

    printf("\nDescreva o seu projeto: ");
    scanf(" %[^\n]", novo->projeto.descricao_do_projeto);
    getchar();

    novo->prox = *lista;
    *lista = novo;
}

void imprimir_projeto(No *lista){
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
        while (i < 50 && lista->projeto.nome.alunos_envolvidos[i][0] != '\0') {
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

void lista_projeto(No *lista){
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    while (lista != NULL) {
        printf(" \n--- Título do projeto ---\n");
        printf("%s\n", lista->projeto.nome.titulo_projeto);

        printf(" \n--- Código do projeto ---\n");
        printf("%d\n", lista->projeto.codigo_identificador);

        lista = lista->prox;
    }
}

void excluir_projeto(No **lista, int codigo_identificador){
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
    abrir_arquivo(*lista, "projetos.txt");
}

void abrir_arquivo(No *lista, char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "w"); 
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int i;
    No *aux = lista;
    while (aux != NULL) {
        fprintf(arquivo, "Tipo: ");
        switch (aux->projeto.tipo) {
            case pesquisa:
                fprintf(arquivo, "Pesquisa\n");
                break;
            case extensao:
                fprintf(arquivo, "Extensão\n");
                break;
            case ensino:
                fprintf(arquivo, "Ensino\n");
                break;
            default:
                fprintf(arquivo, "Desconhecido\n");
                break;
        }

        fprintf(arquivo, "Título do projeto: %s\n", aux->projeto.nome.titulo_projeto);
        fprintf(arquivo, "Código do projeto: %d\n", aux->projeto.codigo_identificador);
        fprintf(arquivo, "Data de inicio: %s\n", aux->projeto.data_inicio);

        fprintf(arquivo, "Situação: ");
        switch (aux->projeto.situacao) {
            case concluido:
                fprintf(arquivo, "Concluído\n");
                break;
            case andamento:
                fprintf(arquivo, "Andamento\n");
                break;
            case cancelado:
                fprintf(arquivo, "Cancelado\n");
                break;
            default:
                fprintf(arquivo, "Desconhecido\n");
                break;
        }

        if (aux->projeto.data_termino[0] != '\0') {
            fprintf(arquivo, "Data de Término: %s\n", aux->projeto.data_termino);
        } else {
            fprintf(arquivo, "Data de Término: --/--/----\n");
        }

        fprintf(arquivo, "Coordenador: %s\n", aux->projeto.nome.coordenador);

        int num_alunos = 0;
        while (num_alunos < 50 && aux->projeto.nome.alunos_envolvidos[num_alunos][0] != '\0') {
            num_alunos++;
        }
        fprintf(arquivo, "Total de alunos: %d\n", num_alunos);

        for (i = 0; i < num_alunos; i++) {
            fprintf(arquivo, "Alunos envolvidos: %s\n", aux->projeto.nome.alunos_envolvidos[i]);
        }

        if (aux->projeto.nome.orgao_financeiro[0] != '\0') {
            fprintf(arquivo, "Órgão Financeiro: %s\n", aux->projeto.nome.orgao_financeiro);
        } else {
            fprintf(arquivo, "Órgão Financeiro: Não há órgão financeiro!\n");
        }

        fprintf(arquivo, "Descrição do projeto: %s\n\n", aux->projeto.descricao_do_projeto);

        aux = aux->prox;
    }

    fclose(arquivo);
}

void ler_arquivo(No **lista, char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char tipo[50], situacao[50], orgao_financeiro[50], data_termino[12];
    No *novo;
    int i;

    while (!feof(arquivo)) {
        novo = alocar_no();

        if (fscanf(arquivo, "Tipo: %[^\n]\n", tipo) == 1) {
            if (strcmp(tipo, "Pesquisa") == 0) {
                novo->projeto.tipo = pesquisa;
            } else if (strcmp(tipo, "Extensão") == 0) {
                novo->projeto.tipo = extensao;
            } else if (strcmp(tipo, "Ensino") == 0) {
                novo->projeto.tipo = ensino;
            }

            fscanf(arquivo, "Título do projeto: %[^\n]\n", novo->projeto.nome.titulo_projeto);

            fscanf(arquivo, "Código do projeto: %d\n", &novo->projeto.codigo_identificador);
            
            fscanf(arquivo, "Data de início: %[^\n]\n", novo->projeto.data_inicio);

            fscanf(arquivo, "Situação: %[^\n]\n", situacao);
            if (strcmp(situacao, "Concluído") == 0) {
                novo->projeto.situacao = concluido;
            } else if (strcmp(situacao, "Andamento") == 0) {
                novo->projeto.situacao = andamento;
            } else if (strcmp(situacao, "Cancelado") == 0) {
                novo->projeto.situacao = cancelado;
            }

            fscanf(arquivo, "Data de Término: %[^\n]\n", data_termino);
            if (strcmp(data_termino, "--/--/----") == 0) {
                novo->projeto.data_termino[0] = '\0';
            } else {
                strncpy(novo->projeto.data_termino, data_termino, sizeof(novo->projeto.data_termino) - 1);
                novo->projeto.data_termino[sizeof(novo->projeto.data_termino) - 1] = '\0';
            }

            fscanf(arquivo, "Coordenador: %[^\n]\n", novo->projeto.nome.coordenador);

            int num_alunos;
            
            fscanf(arquivo, "Total de alunos: %d\n", &num_alunos);
            for (i = 0; i < num_alunos; i++) {
                fscanf(arquivo, "Alunos envolvidos: %[^\n]\n", novo->projeto.nome.alunos_envolvidos[i]);
            }

            fscanf(arquivo, "Órgão Financeiro: %[^\n]\n", orgao_financeiro);
            if (strcmp(orgao_financeiro, "Não há órgão financeiro!") == 0) {
                novo->projeto.nome.orgao_financeiro[0] = '\0';
            } else {
                strncpy(novo->projeto.nome.orgao_financeiro, orgao_financeiro, sizeof(novo->projeto.nome.orgao_financeiro) - 1);
                novo->projeto.nome.orgao_financeiro[sizeof(novo->projeto.nome.orgao_financeiro) - 1] = '\0';
            }

            fscanf(arquivo, "Descrição do Projeto: %[^\n]\n", novo->projeto.descricao_do_projeto);

            novo->prox = *lista;
            *lista = novo;
        } else {
            free(novo);
            break;
        }
    }

    fclose(arquivo);
}

void liberar_lista(No *lista){
    No *ant = lista;
    while (ant != NULL) {
        No *temp = ant;
        ant = ant->prox;
        free(temp);
    }
}
