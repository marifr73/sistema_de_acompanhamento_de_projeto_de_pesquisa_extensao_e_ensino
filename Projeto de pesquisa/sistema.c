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

struct data{
    int dia_inicio, mes_inicio, ano_inicio;
    int dia_termino, mes_termino, ano_termino;
};

struct nome{  
    char titulo_projeto[100];  
    char coordenador[100];  
    char alunos_envolvidos[50][100];  
    char orgao_financeiro[100];
};

struct dados{
    int codigo_identificador;
    char descricao_do_projeto[500];
    Data data;
    Nome nome;
    Tipo tipo;
    Situacao situacao;
};

struct no {
    int id_unico;
    Dados projeto;
    struct no *prox;
};

No* alocar_no(int id) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    novo->id_unico = id;
    novo->prox = NULL;
    return novo;
}

int verificar_data(int dia, int mes, int ano) {
    if (ano < 0) {
        printf("Ano não existe.\n");
        return 0;
    }

    if (mes < 1 || mes > 12) {
        printf("O mês não está entre Janeiro e Dezembro.\n");
        return 0;
    }

    if (dia < 1) {
        printf("Dia não existe.\n");
        return 0;
    }

    if (mes == 2){
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
            if (dia > 29) {
                printf("Dia inválido em fevereiro (ano bissexto).\n");
                return 0;
            }
        } else {
            if (dia > 28) {
                printf("Dia inválido em fevereiro (não bissexto).\n");
                return 0;
            }
        }
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        if (dia > 30) {
            printf("Dia inválido em um mês com 30 dias.\n");
            return 0;
        }
    } else {
        if (dia > 31) {
            printf("Dia inválido em um mês com 31 dias.\n");
            return 0;
        }
    }

    printf("Data válida: %02d/%02d/%04d\n", dia, mes, ano);
    return 1;
}

void adicionar_projeto(No **lista, int *proximo_id, char *nome_arquivo) {
    No *novo = alocar_no((*proximo_id)++);
    int alunos, i, orgao_fi, tipo_projeto, situacao_projeto;
    
    printf("\nInforme o tipo do seu projeto: \n1. Pesquisa\n2. Extensão\n3. Ensino\n");
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

    do {
        printf("\nData de início (Dia/Mês/Ano): ");  
        scanf("%d/%d/%d", &novo->projeto.data.dia_inicio, &novo->projeto.data.mes_inicio, &novo->projeto.data.ano_inicio);
    } while (!verificar_data(novo->projeto.data.dia_inicio, novo->projeto.data.mes_inicio, novo->projeto.data.ano_inicio));

    printf("\nSituação do projeto: \n1. Concluído\n2. Andamento\n3. Cancelado\n");
    scanf("%d", &situacao_projeto);

    switch (situacao_projeto) {
        case 1:
            novo->projeto.situacao = concluido;
            do {
                printf("\nData de Término (Dia/Mês/Ano): ");
                scanf("%d/%d/%d", &novo->projeto.data.dia_termino, &novo->projeto.data.mes_termino, &novo->projeto.data.ano_termino);
            } while (!verificar_data(novo->projeto.data.dia_termino, novo->projeto.data.mes_termino, novo->projeto.data.ano_termino));
            break;
        case 2:
            novo->projeto.situacao = andamento;
            printf("\nProjeto em andamento!\n");
            novo->projeto.data.dia_termino = 0;
            novo->projeto.data.mes_termino = 0;
            novo->projeto.data.ano_termino = 0;
            break;
        case 3: 
            novo->projeto.situacao = cancelado;
            printf("\nProjeto Cancelado!\n");
            novo->projeto.data.dia_termino = 0;
            novo->projeto.data.mes_termino = 0;
            novo->projeto.data.ano_termino = 0;
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

    //adiciona um novo nó no início da lista (lista encadeada simples)
    novo->prox = *lista;
    *lista = novo;

    abrir_arquivo(*lista, nome_arquivo);
}

void listar_projeto(No *lista) {
    if (lista == NULL) {
        printf("Nenhum projeto encontrado!\n");
        return;
    }

    int contador = 0;
    while (lista != NULL) {
        printf("\nID do projeto: %d\n", lista->id_unico);
        printf("Título do projeto: %s\n", lista->projeto.nome.titulo_projeto);
        printf("Código do projeto: %d\n", lista->projeto.codigo_identificador);
        printf("Data de início: %02d/%02d/%04d\n", lista->projeto.data.dia_inicio, lista->projeto.data.mes_inicio, lista->projeto.data.ano_inicio);

        switch (lista->projeto.situacao) {
            case concluido:
                printf("Situação: Concluído\n");
                printf("Data de término: %02d/%02d/%04d\n", lista->projeto.data.dia_termino, lista->projeto.data.mes_termino, lista->projeto.data.ano_termino);
                break;
            case andamento:
                printf("Situação: Andamento\n");
                printf("Data de término: --/--/----\n");
                break;
            case cancelado:
                printf("Situação: Cancelado\n");
                printf("Data de término: --/--/----\n");
                break;
            default:
                printf("Situação desconhecida!\n");
                break;
        }

        if (strlen(lista->projeto.nome.coordenador) > 0) {
            printf("Coordenador: %s\n", lista->projeto.nome.coordenador);
        } else {
            printf("Coordenador: Não informado\n");
        }

        printf("Alunos Envolvidos: ");
        int numAlunos = 0;
        for (int i = 0; i < 50 && lista->projeto.nome.alunos_envolvidos[i][0] != '\0'; i++) {
            numAlunos++;
        }
        int s = 0;
        if (numAlunos > 0) {
            for (int i = 0; i < numAlunos; i++) {
                printf("\n%d Aluno: %s", s + 1, lista->projeto.nome.alunos_envolvidos[i]);
                s++;
                if (i < numAlunos - 1) {
                }
            }
            printf("\n");
        } else {
            printf("Nenhum aluno cadastrado.\n");
        }

        if (strlen(lista->projeto.nome.orgao_financeiro) > 0) {
            printf("Órgão Financeiro: %s\n", lista->projeto.nome.orgao_financeiro);
        } else {
            printf("Órgão Financeiro: Não há órgão financeiro.\n");
        }

        printf("Descrição do Projeto: %s\n", lista->projeto.descricao_do_projeto);
        printf("----------------------------------------\n");

        //move o ponteiro para o proximo no da lista (lista simples)
        lista = lista->prox;
        contador++;
    }

    printf("Total de projetos adicionados: %d\n", contador);
}


void abrir_arquivo(No *lista, char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "wt"); 
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    No *aux = lista;
    while (aux != NULL) {
        fprintf(arquivo, "ID Único: %d\n", aux->id_unico);
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
        fprintf(arquivo, "Data de início: %02d/%02d/%04d\n", aux->projeto.data.dia_inicio, aux->projeto.data.mes_inicio, aux->projeto.data.ano_inicio);

        fprintf(arquivo, "Situação: ");
        switch (aux->projeto.situacao) {
            case concluido:
                fprintf(arquivo, "Concluído\n");
                fprintf(arquivo, "Data de Término: %02d/%02d/%04d\n", aux->projeto.data.dia_termino, aux->projeto.data.mes_termino, aux->projeto.data.ano_termino);
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

        fprintf(arquivo, "Coordenador: %s\n", aux->projeto.nome.coordenador);

        int num_alunos = 0;
        while (num_alunos < 50 && aux->projeto.nome.alunos_envolvidos[num_alunos][0] != '\0') {
            num_alunos++;
        }
        fprintf(arquivo, "Total de alunos: %d\n", num_alunos);

        for (int i = 0; i < num_alunos; i++) {
            fprintf(arquivo, "Alunos envolvidos: %s\n", aux->projeto.nome.alunos_envolvidos[i]);
        }

        if (aux->projeto.nome.orgao_financeiro[0] != '\0') {
            fprintf(arquivo, "Órgão Financeiro: %s\n", aux->projeto.nome.orgao_financeiro);
        } else {
            fprintf(arquivo, "Órgão Financeiro: Não há órgão financeiro!\n");
        }

        fprintf(arquivo, "Descrição do projeto: %s\n\n", aux->projeto.descricao_do_projeto);

        //move o ponteiro para o proximo no da lista (lista simples)
        aux = aux->prox;
    }

    fclose(arquivo);
}


void excluir_projeto(No **lista, int id_unico) {
    No *aux = *lista;
    No *ant = NULL;

    //Percorrer a lista até encontrar o nó com o id_unico ou chegar ao final da lista
    while (aux != NULL && aux->id_unico != id_unico) {
        ant = aux;
        aux = aux->prox;
    }

    // Verifica se o nó com o id_unico foi encontrado
    if (aux == NULL) {
        printf("Projeto com ID %d não encontrado.\n", id_unico);
        return;
    }

    // Se o nó a ser removido é o primeiro nó da lista
    if (ant == NULL) {
        *lista = aux->prox; // Atualiza o ponteiro do início da lista para o próximo nó
    } else {
        ant->prox = aux->prox; 
    }

    // Libera a memória do nó removido
    free(aux);
    printf("Projeto com ID %d excluído com sucesso.\n", id_unico);
}

void consultar_projeto_por_tipo(No *lista){
    int tipo;
    printf("Informe o tipo de projeto:\n1. Pesquisa\n2. Extensão\n3. Ensino\n");
    scanf("%d", &tipo);
    getchar();

    while (lista != NULL) {
        if (lista->projeto.tipo == (Tipo)tipo) {
            printf("Título do projeto: %s\t\n", lista->projeto.nome.titulo_projeto);
            printf("Código do projeto: %d\t\n", lista->projeto.codigo_identificador);
            printf("Data de início: %02d/%02d/%04d\n", lista->projeto.data.dia_inicio, lista->projeto.data.mes_inicio, lista->projeto.data.ano_inicio);
            printf("Coordenador: %s\t\n", lista->projeto.nome.coordenador);
            printf("Descrição: %s\n\n", lista->projeto.descricao_do_projeto);
        }
        //move o ponteiro para o proximo no da lista (lista simples)
        lista = lista->prox; 
    }
}

void consultar_projeto_por_situacao(No *lista){
    int situacao;
    printf("Informe a situação do projeto:\n1. Concluído\n2. Andamento\n3. Cancelado\n");
    scanf("%d", &situacao);
    getchar();

    while (lista != NULL){
        if (lista->projeto.situacao == (Situacao)situacao){
            printf("Título do projeto: %s\t\n", lista->projeto.nome.titulo_projeto);
            printf("Código do projeto: %d\t\n", lista->projeto.codigo_identificador);
            printf("Data de início: %02d/%02d/%04d\n", lista->projeto.data.dia_inicio, lista->projeto.data.mes_inicio, lista->projeto.data.ano_inicio);
            printf("Coordenador: %s\t\n", lista->projeto.nome.coordenador);
            printf("Descrição: %s\n\n", lista->projeto.descricao_do_projeto);
        }
        //move o ponteiro para o proximo no da lista (lista simples)
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
    printf("Data de início: %02d/%02d/%04d\n", lista->projeto.data.dia_inicio, lista->projeto.data.mes_inicio, lista->projeto.data.ano_inicio);

        switch (lista->projeto.situacao) {
            case concluido:
                printf("Situação: Concluído\n");
                printf("Data de término: %02d/%02d/%04d\n", lista->projeto.data.dia_termino, lista->projeto.data.mes_termino, lista->projeto.data.ano_termino);
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
        //move o ponteiro para o proximo no da lista (lista simples)
        lista = lista->prox;
    }
    printf("\nProjeto não encontrado!\n");
}

void editar_dados_do_projeto(No *lista) {
    int id_unico;

    printf("\nDigite o ID do projeto que deseja editar: ");
    scanf("%d", &id_unico);
    getchar();

    No *aux = lista;

    while (aux != NULL) {
        if (aux->id_unico == id_unico) {
            printf("Novo título: ");
            scanf(" %[^\n]", aux->projeto.nome.titulo_projeto);
            getchar();

            int dia, mes, ano;
            printf("Nova data de início (Dia/Mês/Ano): ");
            scanf("%02d/%02d/%04d", &dia, &mes, &ano);
            getchar();
            if (!verificar_data(dia, mes, ano)) {
                printf("Data de início inválida!\n");
                return;
            }
            aux->projeto.data.dia_inicio = dia;
            aux->projeto.data.mes_inicio = mes;
            aux->projeto.data.ano_inicio = ano;

            int nova_situacao;
            printf("Nova situação:\n1. Concluído\n2. Andamento\n3. Cancelado\n");
            scanf("%d", &nova_situacao);
            getchar();

            switch (nova_situacao) {
                case 1:
                    aux->projeto.situacao = concluido;
                    printf("Data de término (Dia/Mês/Ano): ");
                    scanf("%02d/%02d/%04d", &dia, &mes, &ano);
                    getchar();
                    if (!verificar_data(dia, mes, ano)) {
                        printf("Data de término inválida!\n");
                        return;
                    }
                    aux->projeto.data.dia_termino = dia;
                    aux->projeto.data.mes_termino = mes;
                    aux->projeto.data.ano_termino = ano;
                    break;
                case 2:
                    aux->projeto.situacao = andamento;
                    aux->projeto.data.dia_termino = 0;
                    aux->projeto.data.mes_termino = 0;
                    aux->projeto.data.ano_termino = 0;
                    break;
                case 3:
                    aux->projeto.situacao = cancelado;
                    aux->projeto.data.dia_termino = 0;
                    aux->projeto.data.mes_termino = 0;
                    aux->projeto.data.ano_termino = 0;
                    break;
                default:
                    printf("Situação inválida!\n");
                    return;
            }

            printf("Novo coordenador: ");
            scanf(" %[^\n]", aux->projeto.nome.coordenador);
            getchar();

            int num_alunos;
            printf("Número de alunos envolvidos: ");
            scanf("%d", &num_alunos);
            getchar();

            int i, orgao_fi;
            for (i = 0; i < num_alunos; i++) {
                printf("Nome do aluno %d: ", i + 1);
                scanf(" %[^\n]", aux->projeto.nome.alunos_envolvidos[i]);
                getchar();
            }

            printf("\nHá órgão financeiro? \n1. Sim\n2. Não\n");
            scanf("%d", &orgao_fi);
            getchar();

            if (orgao_fi == 1) {
                printf("\nInforme o nome do órgão financeiro: ");
                scanf(" %[^\n]", aux->projeto.nome.orgao_financeiro);
                getchar();
            } else if (orgao_fi == 2) {
                printf("\nNão há órgão financeiro!\n");
                aux->projeto.nome.orgao_financeiro[0] = '\0';
            } else {
                printf("Código não identificado!\n");
            }

            printf("Nova descrição: ");
            scanf(" %[^\n]", aux->projeto.descricao_do_projeto);
            getchar();

            printf("Projeto editado com sucesso!\n");
            return;
        }
        // Move o ponteiro para o próximo nó na lista (lista encadeada simples)
        aux = aux->prox;
    }
    printf("Projeto com ID %d não encontrado.\n", id_unico);
}


void ler_arquivo(No **lista, char *nome_arquivo, int *proximo_id) {
    FILE *arquivo = fopen(nome_arquivo, "rt");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char tipo[50], situacao[50], orgao_financeiro[50];
    int id_unico;
    No *novo;
    int i;

    while (fscanf(arquivo, "ID Único: %d\n", &id_unico) == 1) {
        novo = alocar_no(id_unico);
        if (novo == NULL) {
            printf("Erro ao alocar memória!\n");
            fclose(arquivo);
            return;
        }

        fscanf(arquivo, "Tipo: %[^\n]\n", tipo);
        if (strcmp(tipo, "Pesquisa") == 0) {
            novo->projeto.tipo = pesquisa;
        } else if (strcmp(tipo, "Extensão") == 0) {
            novo->projeto.tipo = extensao;
        } else if (strcmp(tipo, "Ensino") == 0) {
            novo->projeto.tipo = ensino;
        } else {
            free(novo);
            continue;
        }

        fscanf(arquivo, "Título do projeto: %[^\n]\n", novo->projeto.nome.titulo_projeto);
        fscanf(arquivo, "Código do projeto: %d\n", &novo->projeto.codigo_identificador);
        fscanf(arquivo, "Data de início: %02d/%02d/%04d\n", &novo->projeto.data.dia_inicio, &novo->projeto.data.mes_inicio, &novo->projeto.data.ano_inicio);

        fscanf(arquivo, "Situação: %[^\n]\n", situacao);
        if (strcmp(situacao, "Concluído") == 0) {
            novo->projeto.situacao = concluido;
            fscanf(arquivo, "Data de Término: %02d/%02d/%04d\n", &novo->projeto.data.dia_termino, &novo->projeto.data.mes_termino, &novo->projeto.data.ano_termino);
        } else if (strcmp(situacao, "Andamento") == 0) {
            novo->projeto.situacao = andamento;
        } else if (strcmp(situacao, "Cancelado") == 0) {
            novo->projeto.situacao = cancelado;
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

        //adiciona um novo nó no início da lista (lista encadeada simples)
        novo->prox = *lista;
        *lista = novo;

        // Atualize proximo_id
        if (novo->id_unico >= *proximo_id) {
            *proximo_id = novo->id_unico + 1;
        }
    }
    fclose(arquivo);
}

void liberar_lista(No* lista) {
    No* atual = lista;
    No* prox;
    while (atual != NULL) {
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
}
