#include "sistema.h"

int main() {
    No *lista = NULL;
    int opcao = 0, codigo_para_excluir;
    char *nome_arquivo = "projetos.txt";

    ler_arquivo(&lista, nome_arquivo);

    do {
        printf("\nDigite uma opcao:\n");
        printf("1. Adicionar projeto\n");
        printf("2. Listar projetos\n");
        printf("3. Consultar projeto por tipo\n");
        printf("4. Consultar projeto por situacao\n");
        printf("5. Buscar projeto por codigo\n");
        printf("6. Editar projeto\n");
        printf("7. Excluir projeto\n");
        printf("8. Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida! Insira um numero.\n");
            while (getchar() != '\n');
            opcao = 0;
            continue; 
        }

        switch (opcao){
            case 1:
                adicionar_projeto(&lista);
                abrir_arquivo(lista, nome_arquivo);
                break;
            case 2:
                listar_projeto(lista);
                break;
            case 3:
                consultar_projeto_por_tipo(lista);
                break;
            case 4:
                consultar_projeto_por_situacao(lista);
                break;
            case 5:
                buscar_projeto_por_codigo(lista);
                break;
            case 6:
                editar_dados_do_projeto(lista);
                abrir_arquivo(lista, nome_arquivo);
                break;
            case 7:
                if (lista == NULL) {
                    printf("A lista está vazia.\n");
                } else {
                    printf("Digite o codigo do projeto para excluir: ");
                    if (scanf("%d", &codigo_para_excluir) == 1) {
                        excluir_projeto(&lista, codigo_para_excluir);
                        abrir_arquivo(lista, nome_arquivo);
                    } else {
                        printf("Código invalido!\n");
                        while (getchar() != '\n'); 
                    }
                }
                break;
            case 8:
                liberar_lista(lista); 
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao não cadastrada!\n");
                break;
        }
    } while (opcao != 8);
    return 0;
}
