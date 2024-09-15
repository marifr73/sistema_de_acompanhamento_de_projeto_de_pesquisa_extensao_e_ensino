#include "sistema.h"

int main() {
    No *lista = NULL;
    int opcao, codigo_para_excluir;

    do {
        printf("\nDigite uma opção:\n");
        printf("1. Adicionar projeto\n");
        printf("2. Imprimir Projeto\n");
        printf("3. Excluir projeto\n");
        printf("4. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar_projeto(&lista);
                break;

            case 2:
                imprimir_projeto(lista);
                break;

            case 3:
                if (lista == NULL) {
                    printf("A lista está vazia.\n");
                } else {
                    printf("Digite o código do projeto para excluir: ");
                    scanf("%d", &codigo_para_excluir);
                    excluir_projeto(&lista, codigo_para_excluir);
                }
                break;

            case 4:
                liberar_lista(lista);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 4);     
    return 0;
}
