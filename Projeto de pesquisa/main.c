#include "sistema.h"

int main(){
    No *lista = NULL;
    int opcao = 0, proximo_id = 1;
    char *nome_arquivo = "projetos.txt";

    ler_arquivo(&lista, nome_arquivo, &proximo_id);

    do {
        printf("\nDigite uma opcao:\n");
        printf("1. Adicionar projeto\n");
        printf("2. Listar projetos\n");
        printf("3. Consultar projeto por tipo\n");
        printf("4. Consultar projeto por situação\n");
        printf("5. Buscar projeto por ID\n");
        printf("6. Editar projeto\n");
        printf("7. Excluir projeto\n");
        printf("8. Sair\n");
        printf("Opcao: ");

        char input[9];
        scanf("%s", input);
        //atoi é uma função em C que converte uma string em um número inteiro
        opcao = atoi(input);

        switch (opcao) {
            case 1:
                if (strcmp(input, "1") != 0) {
                    printf("Opcao invalida não cadastrada!\n");
                } else {
                    adicionar_projeto(&lista, &proximo_id, nome_arquivo);
                    abrir_arquivo(lista, nome_arquivo);
                }
                break;
            case 2:
                if (strcmp(input, "2") != 0) {
                    printf("Opcao invalida não cadastrada!\n");
                } else {
                    listar_projeto(lista);
                }
                break;
            case 3:
                if (strcmp(input, "3") != 0) {
                    printf("Opcao invalida não cadastrada!\n");
                } else {
                    consultar_projeto_por_tipo(lista);
                }
                break;
            case 4:
                if (strcmp(input, "4") != 0) {
                    printf("Opcao invalida não cadastrada!\n");
                } else {
                    consultar_projeto_por_situacao(lista);
                }
                break;
            case 5:
                if (strcmp(input, "5") != 0) {
                    printf("Opcao invalida não cadastrada!\n");
                } else {
                    buscar_projeto_por_codigo(lista);
                }
                break;
            case 6:
                if (strcmp(input, "6") != 0) {
                    printf("Opcao invalida não cadastrada!\n");
                } else {
                    editar_dados_do_projeto(lista);
                    abrir_arquivo(lista, nome_arquivo);
                }
                break;
            case 7:
                if (strcmp(input, "7") != 0) {
                    printf("Opcao invalida não cadastrada!\n");
                } else {
                    if (lista == NULL) {
                        printf("A lista está vazia.\n");
                    } else {
                        printf("Digite o ID do projeto para excluir: ");
                        int id_para_excluir;
                        if (scanf("%d", &id_para_excluir) == 1) {
                            excluir_projeto(&lista, id_para_excluir);
                            abrir_arquivo(lista, nome_arquivo);
                        } else {
                            printf("ID inválido!\n");
                            while (getchar() != '\n');
                        }
                    }
                }
                break;
            case 8:
                if (strcmp(input, "8") != 0) {
                    printf("Opcao invalida não cadastrada!\n");
                } else {
                    liberar_lista(lista);
                    printf("Saindo...\n");
                }
                break;
            default:
                printf("Opcao não cadastrada!\n");
                break;
        }
    } while (opcao != 8);
    return 0;
}
