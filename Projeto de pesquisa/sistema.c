#include "sistema.h"

enum situacao{
    andamento = 1,
    concluido,
    cancelado
};

enum tipo{
    pesquisa = 1,
    estensao,
    ensino
};

union nome{
    char titulo_projeto, coordenador, alunos_envolvidos, orgao_financeiro;
};

struct dados{
    int codigo_identificador;
    int data_inicio;
    int data_termino;
    char descricao_do_projeto;
    Nome nome;
    Tipo tipo;
    Situacao situacao;
};

