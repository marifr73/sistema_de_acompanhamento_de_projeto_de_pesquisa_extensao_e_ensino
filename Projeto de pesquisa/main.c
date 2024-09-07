#include "sistema.h"

int main(){
    int total = 50;
    Dados *dados = alocar_dados(total);
    if (dados == NULL) {
        exit(1); 
    }

    adicionar_projeto(dados);

    free(dados);

    return 0;
}
