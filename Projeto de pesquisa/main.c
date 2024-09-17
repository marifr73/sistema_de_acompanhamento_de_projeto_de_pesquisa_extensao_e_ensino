#include "sistema.h"

int main(){
    No *lista = NULL;
    int opcao, codigo_para_excluir;
    char *nome_arquivo = "projetos.txt";

    ler_arquivo(&lista, nome_arquivo);

    do {
        printf("\nDigite uma opção:\n");
        printf("1. Adicionar projeto\n");
        printf("2. Listar projetos\n");
        printf("3. Imprimir projeto\n");
        printf("4. Excluir projeto\n");
        printf("5. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao){
            case 1:
                adicionar_projeto(&lista);
                abrir_arquivo(lista, nome_arquivo);
                break;

            case 2:
                lista_projeto(lista);
                break;

            case 3:
                imprimir_projeto(lista);
                break;

            case 4:
                if (lista == NULL) {
                    printf("A lista está vazia.\n");
                } else {
                    printf("Digite o código do projeto para excluir: ");
                    scanf("%d", &codigo_para_excluir);
                    getchar();
                    excluir_projeto(&lista, codigo_para_excluir);
                    abrir_arquivo(lista, nome_arquivo);
                }
                break;

            case 5:
                liberar_lista(lista);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}
