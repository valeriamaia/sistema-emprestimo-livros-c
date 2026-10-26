#include "../include/biblioteca.h"  // Importa declarações, funções ou tipos da biblioteca indicada.
#include <assert.h>  // Importa declarações, funções ou tipos da biblioteca indicada.
#include <stdio.h>  // Importa declarações, funções ou tipos da biblioteca indicada.
#include <string.h>  // Importa declarações, funções ou tipos da biblioteca indicada.
// Executa verificações automáticas das regras de cadastro, empréstimo e devolução.
int main(void){
 Livro l={0};strcpy(l.titulo,"Dom Casmurro");strcpy(l.autor,"Machado de Assis");l.total=1;l.ano=1899;
 assert(cadastrar_livro(l));assert(quantidade_livros==1);assert(livros[0].disponivel==1);
 Usuario u={0};strcpy(u.nome,"Pessoa de teste");strcpy(u.cpf,"12345678901");assert(cadastrar_usuario(u));assert(!cadastrar_usuario(u));
 assert(emprestar(livros[0].id,usuarios[0].id,"2026-10-15","2026-10-20"));assert(livros[0].disponivel==0);
 assert(!emprestar(livros[0].id,usuarios[0].id,"2026-10-15","2026-10-20"));
 assert(!excluir_livro(livros[0].id));assert(!excluir_usuario(usuarios[0].id));
 assert(devolver(emprestimos[0].id,"2026-10-18"));assert(!devolver(emprestimos[0].id,"2026-10-18"));assert(livros[0].disponivel==1);
 int lid=livros[0].id;liberar();carregar();assert(buscar_livro(lid)!=NULL);assert(quantidade_livros==1&&quantidade_usuarios==1&&quantidade_emprestimos==1);
 puts("TESTES BASICOS: OK");liberar();return 0;
}
