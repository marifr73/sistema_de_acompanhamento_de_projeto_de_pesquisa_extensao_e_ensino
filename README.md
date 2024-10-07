# Sistema de Acompanhamento de Projetos de Pesquisa, Extensão e Ensino

## Sumário:
- Introdução
- Utilidade
- Problematica
- Executar Projeto
- Funcionalidades
- Desenvolvimento
- Desenvolvedores

### Introdução
#
Olá, somos alunos da UFERSA (Universidade Rural do Semi- Árido) campus Pau Dos Ferros, este projeto refere-se a diciplina: Algoritimo e Estrutura de Dados I, ministrada pela docente Dra. Rosana Cibely.

Projeto desenvolvido em C para acompanhar projetos do tipo de Pesquisa, Extensão e Ensino. O sistema nos posibilita cadastra projetos, buscar, consultar por tipo e situação, editar dados do projeto com base em seu ID e por fim excluir o projeto.

### Utilidade
#
O projeto tem o propósito de ajuda no acompanhamento e gestão de projetos de pesquisa, extensão e ensino, estando eles em andamento, cancelados ou concluídos.

### Problematica
#
A necessidade de um sistema de acompanhamento de Projetos de Pesquisa, Extensão e Ensino surge de vários problemas e desafios no gerenciamento desses projetos. Esses desafios criam um ambiente em que o manual de gerenciamento se torna ineficaz.

### Executar Projeto
#
1º clone o repósitorio do projeto: 

```
git clone https://github.com/classroom-ufersa/sistema_de_acompanhamento_de_projeto_de_pesquisa_extensao_e_ensino.git
```
2º Executa o progrma: 
```
gcc -c main.c
gcc -c sistema.c
gcc -o main.exe sistema.c main.c
```
- Para Windows execute com `./main` e Linux use `./main.exe`

### Funcionalidades: 
#

| Menu               | Status               |
| ----------------- | ---------------------------------------------------------------- |
| [1] - Adicionar Projeto       | ✅ |
| [2] - Listar projetos     | ✅ |
| [3] - Consultar projeto por tipo   | ✅ |
| [4] - Consultar projeto por situação     | ✅ |
| [5] - Buscar projeto por ID     | ✅ |
| [6] - Editar projeto     | ✅ |
| [7] - Excluir projeto     | ✅ |
| [8] - Sair     | ✅ |

### Desenvolvimento
#
#### Lista Encadeada
- Para o desenvolvimento do sistema, foram utilizadas listas encadeadas simples, onde cada nó guarda informações de um projeto e aponta para o próximo. 

Exemplo Visual:
```
Projeto 1 -> Projeto 2 -> Projeto 3 -> NULL
```
#### Tipos estruturados
 
>**enum situacao**
```c
enum situacao{
    concluido = 1,
    andamento,
    cancelado
};
```
>**enum tipo**
```c
enum tipo{
    pesquisa = 1,
    extensao,
    ensino
};
```
>**struct data**
```c
struct data{
    int dia_inicio, mes_inicio, ano_inicio;
    int dia_termino, mes_termino, ano_termino;
};
```
>**struct nome**
```c
struct nome{  
    char titulo_projeto[100];  
    char coordenador[100];  
    char alunos_envolvidos[50][100];  
    char orgao_financeiro[100];
};
```
>**struct dados**
```c
struct dados{
    int codigo_identificador;
    char descricao_do_projeto[500];
    Data data;
    Nome nome;
    Tipo tipo;
    Situacao situacao;
};
```
>**struct no**
```c
struct no {
    int id_unico;
    Dados projeto;
    struct no *prox;
};   
```
### Desenvolverores 
#

| [<img loading="lazy" src="https://avatars.githubusercontent.com/u/141454612?v=4" width=115><br><sub> Maria Francisca </sub>](https://github.com/marifr73) | [<img loading="lazy" src="https://avatars.githubusercontent.com/u/58538765?v=4" width=115><br><sub> Pedro Carlos </sub>](https://github.com/PedroCarlos30) |
| :------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
