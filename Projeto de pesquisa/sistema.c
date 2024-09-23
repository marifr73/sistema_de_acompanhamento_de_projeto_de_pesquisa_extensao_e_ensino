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
    char titulo_projeto[100];  
    char coordenador[100];  
    char alunos_envolvidos[50][100];  
    char orgao_financeiro[100];
};

struct dados {
    int codigo_identificador;
    char data_inicio[11];
    char data_termino[11];
    char descricao_do_projeto[500];
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

void listar_projeto(No *lista){
    while (lista != NULL) {
        printf("\nTítulo do projeto: %s\t\n", lista->projeto.nome.titulo_projeto);

        printf("Código do projeto: %d\t\n", lista->projeto.codigo_identificador);

        printf("Data de início: %s\t\n", lista->projeto.data_inicio);

        switch (lista->projeto.situacao) {
            case concluido:
                printf("Situação: Concluído\n");
                break;
            case andamento:
                printf("Situação: Andamento\n");
                break;
            case cancelado:
                printf("Situação: Cancelado\n");
                break;
            default:
                printf("Situação desconhecida!\n");
                break;
        }

        printf("Data de Término: %s\t\n", lista->projeto.data_termino);

        printf("Coordenador: %s\t\n", lista->projeto.nome.coordenador);
        
        printf("Alunos Envolvidos: \n");
        int i = 0;
        while (i < 50 && lista->projeto.nome.alunos_envolvidos[i][0] != '\0') {
            printf("%s\n", lista->projeto.nome.alunos_envolvidos[i]);
            i++;
        }

        printf("Órgão Financeiro: %s\t\n", lista->projeto.nome.orgao_financeiro);

        printf("Descrição do Projeto: \n");
        printf("%s\n", lista->projeto.descricao_do_projeto);
        printf("--------------------");
        lista = lista->prox;
        printf("--------------------\n\n");
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

void consultar_projeto_por_tipo(No *lista){
    int tipo;
    printf("Informe o tipo de projeto:\n1. Pesquisa\n2. Extensão\n3. Ensino\n");
    scanf("%d", &tipo);
    getchar();

    while (lista != NULL) {
        if (lista->projeto.tipo == tipo) {
            printf("Título do projeto: %s\t\n", lista->projeto.nome.titulo_projeto);
            printf("Código do projeto: %d\t\n", lista->projeto.codigo_identificador);
            printf("Data de início: %s\t\n", lista->projeto.data_inicio);
            printf("Coordenador: %s\t\n", lista->projeto.nome.coordenador);
            printf("Descrição: %s\n\n", lista->projeto.descricao_do_projeto);
        }
        lista = lista->prox;
    }
}

void consultar_projeto_por_situacao(No *lista){
    int situacao;
    printf("Informe a situação do projeto:\n1. Concluído\n2. Andamento\n3. Cancelado\n");
    scanf("%d", &situacao);
    getchar();

    while (lista != NULL){
        if (lista->projeto.situacao == situacao){
            printf("Título do projeto: %s\t\n", lista->projeto.nome.titulo_projeto);
            printf("Código do projeto: %d\t\n", lista->projeto.codigo_identificador);
            printf("Data de início: %s\t\n", lista->projeto.data_inicio);
            printf("Coordenador: %s\t\n", lista->projeto.nome.coordenador);
            printf("Descrição: %s\n\n", lista->projeto.descricao_do_projeto);
        }
        lista = lista->prox;
    }
}

void listar_projeto_unico(No *lista){
    if (lista == NULL){
        printf("\nProjeto não encontrado!\n");
        return;
    }

    printf("\nTítulo do projeto: %s\t\n", lista->projeto.nome.titulo_projeto);
    printf("Código do projeto: %d\t\n", lista->projeto.codigo_identificador);
    printf("Data de início: %s\t\n", lista->projeto.data_inicio);

    switch (lista->projeto.situacao) {
        case concluido:
            printf("Situação: Concluído\n");
            break;
        case andamento:
            printf("Situação: Andamento\n");
            break;
        case cancelado:
            printf("Situação: Cancelado\n");
            break;
        default:
            printf("Situação desconhecida!\n");
            break;
    }

    printf("Data de Término: %s\t\n", lista->projeto.data_termino);
    printf("Coordenador: %s\t\n", lista->projeto.nome.coordenador);

    printf("Alunos Envolvidos: \n");
    int i = 0;
    while (i < 50 && lista->projeto.nome.alunos_envolvidos[i][0] != '\0') {
        printf("%s\n", lista->projeto.nome.alunos_envolvidos[i]);
        i++;
    }

    printf("Órgão Financeiro: %s\t\n", lista->projeto.nome.orgao_financeiro);
    printf("Descrição do Projeto: \n%s\n", lista->projeto.descricao_do_projeto);
    printf("--------------------\n\n");
}

void buscar_projeto_por_codigo(No *lista){
    int codigo;
    printf("\nInforme o código do projeto: ");
    scanf("%d", &codigo);
    getchar();

    while (lista != NULL) {
        if (lista->projeto.codigo_identificador == codigo) {
            listar_projeto_unico(lista);
            return;
        }
        lista = lista->prox;
    }
    printf("\nProjeto não encontrado!\n");
}

void editar_dados_do_projeto(No *lista) {
    int codigo;

    printf("\nDigite o código do projeto que deseja editar: ");
    scanf("%d", &codigo);
    getchar();

    No *aux = lista;

    while (aux != NULL) {
        if (aux->projeto.codigo_identificador == codigo) {
            printf("Novo título: ");
            scanf(" %[^\n]", aux->projeto.nome.titulo_projeto);
            getchar();

            printf("Nova data de início: ");
            scanf(" %[^\n]", aux->projeto.data_inicio);
            getchar();

            int nova_situacao;
            printf("Nova situação:\n1. Concluído\n2. Andamento\n3. Cancelado\n");
            scanf("%d", &nova_situacao);
            getchar();

            switch (nova_situacao) {
                case 1:
                    aux->projeto.situacao = concluido;
                    printf("Data de término: ");
                    scanf(" %[^\n]", aux->projeto.data_termino);
                    break;
                case 2:
                    aux->projeto.situacao = andamento;
                    aux->projeto.data_termino[0] = '\0';
                    break;
                case 3:
                    aux->projeto.situacao = cancelado;
                    aux->projeto.data_termino[0] = '\0';
                    break;
                default:
                    printf("Situação inválida.\n");
                    break;
            }

            printf("Novo coordenador: ");
            scanf(" %[^\n]", aux->projeto.nome.coordenador);
            getchar();

            int num_alunos;
            printf("Número de alunos envolvidos: ");
            scanf("%d", &num_alunos);
            getchar();

            int i;
            for (i = 0; i < num_alunos; i++) {
                printf("Nome do aluno %d: ", i + 1);
                scanf(" %[^\n]", aux->projeto.nome.alunos_envolvidos[i]);
                getchar();
            }

            printf("Novo órgão financeiro: ");
            scanf(" %[^\n]", aux->projeto.nome.orgao_financeiro);
            getchar();

            printf("Nova descrição: ");
            scanf(" %[^\n]", aux->projeto.descricao_do_projeto);
            getchar();

            printf("Projeto editado com sucesso!\n");
            return;
        }
        aux = aux->prox;
    }

    printf("Projeto com código %d não encontrado.\n", codigo);
}

void ler_arquivo(No **lista, char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rt");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char buffer[256];
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

            fscanf(arquivo, "Data de inicio: %[^\n]\n", novo->projeto.data_inicio);

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

            fscanf(arquivo, "Descrição do projeto: %[^\n]\n", novo->projeto.descricao_do_projeto);

            novo->prox = *lista;
            *lista = novo;
        
        } else {
            free(novo);
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
