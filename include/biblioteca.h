#ifndef BIBLIOTECA_H  // Evita incluir as mesmas declarações mais de uma vez.
#define BIBLIOTECA_H  // Marca este arquivo como já incluído.

#define TAMANHO_TEXTO 160  // Limite dos campos de texto dos cadastros.

// struct: agrupa os dados de cada livro em um único registro.
typedef struct {
    int id, ano, total, disponivel;  // Identificação, publicação e controle de exemplares.
    char titulo[TAMANHO_TEXTO], autor[TAMANHO_TEXTO];  // Dados bibliográficos obrigatórios.
    char editora[TAMANHO_TEXTO], capa[TAMANHO_TEXTO];  // Editora e nome do arquivo da capa.
} Livro;

// Dados do leitor: o CPF não pode ser repetido.
typedef struct {
    int id;  // Identificador único do leitor.
    char nome[TAMANHO_TEXTO], cpf[24];  // Nome e CPF.
    char telefone[32], email[TAMANHO_TEXTO];  // Contatos.
} Usuario;

// Relaciona um livro a um leitor e registra a movimentação.
typedef struct {
    int id, livro, usuario, ativo;  // IDs relacionados e estado do empréstimo.
    char retirada[16], prevista[16], devolucao[16];  // Datas em texto (AAAA-MM-DD).
} Emprestimo;

// extern: declara variáveis que são definidas em biblioteca.c.
extern Livro *livros;  // Vetor dinâmico de livros.
extern Usuario *usuarios;  // Vetor dinâmico de leitores.
extern Emprestimo *emprestimos;  // Vetor dinâmico de empréstimos.
extern int quantidade_livros, quantidade_usuarios, quantidade_emprestimos;  // Contadores.

// Persistência e gerenciamento da memória.
void carregar(void);  // Lê arquivos binários na inicialização.
int salvar(void);  // Grava registros em arquivos binários.
void liberar(void);  // Libera os vetores dinâmicos.

// Operações de livros: cadastrar, editar, excluir e buscar pelo ID.
int cadastrar_livro(Livro livro);
int editar_livro(Livro livro);
int excluir_livro(int id);
Livro *buscar_livro(int id);

// Operações de leitores: cadastrar, editar, excluir e buscar pelo ID.
int cadastrar_usuario(Usuario usuario);
int editar_usuario(Usuario usuario);
int excluir_usuario(int id);
Usuario *buscar_usuario(int id);

// Regras de circulação do acervo.
int emprestar(int livro, int usuario, const char *retirada, const char *prevista);
int devolver(int id, const char *data);

#endif  // Fim da proteção contra inclusão repetida.
