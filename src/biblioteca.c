#include "../include/biblioteca.h"  // Importa declarações, funções ou tipos da biblioteca indicada.
#include <stdio.h>  // Importa declarações, funções ou tipos da biblioteca indicada.
#include <stdlib.h>  // Importa declarações, funções ou tipos da biblioteca indicada.
#include <string.h>  // Importa declarações, funções ou tipos da biblioteca indicada.
Livro *livros=NULL; Usuario *usuarios=NULL; Emprestimo *emprestimos=NULL;int quantidade_livros=0,quantidade_usuarios=0,quantidade_emprestimos=0;
static int proximo_id_livro=1,proximo_id_usuario=1,proximo_id_emprestimo=1;
Livro *buscar_livro(int id){for(int i=0;i<quantidade_livros;i++)if(livros[i].id==id)return &livros[i];return NULL;}
Usuario *buscar_usuario(int id){for(int i=0;i<quantidade_usuarios;i++)if(usuarios[i].id==id)return &usuarios[i];return NULL;}
// realloc aumenta o vetor; verifica falha antes de gravar o novo livro.
static int anexar_livro(Livro x){Livro *p=realloc(livros,(quantidade_livros+1)*sizeof *p);if(!p)return 0;livros=p;livros[quantidade_livros++]=x;return 1;}
// Amplia dinamicamente o vetor de usuários e adiciona um registro.
static int anexar_usuario(Usuario x){Usuario *p=realloc(usuarios,(quantidade_usuarios+1)*sizeof *p);if(!p)return 0;usuarios=p;usuarios[quantidade_usuarios++]=x;return 1;}
// Reserva espaço para mais uma movimentação e atualiza o contador.
static int anexar_emprestimo(Emprestimo x){Emprestimo *p=realloc(emprestimos,(quantidade_emprestimos+1)*sizeof *p);if(!p)return 0;emprestimos=p;emprestimos[quantidade_emprestimos++]=x;return 1;}
// Conta empréstimos não devolvidos vinculados ao livro.
static int emprestimos_ativos_livro(int id){int n=0;for(int i=0;i<quantidade_emprestimos;i++)if(emprestimos[i].ativo&&emprestimos[i].livro==id)n++;return n;}
// Verifica se o leitor possui ao menos um empréstimo ativo.
static int emprestimos_ativos_usuario(int id){for(int i=0;i<quantidade_emprestimos;i++)if(emprestimos[i].ativo&&emprestimos[i].usuario==id)return 1;return 0;}
// Valida os campos, gera ID único, define a disponibilidade e salva.
int cadastrar_livro(Livro x){if(!x.titulo[0]||!x.autor[0]||x.total<1||x.ano<0)return 0;if(x.id&&buscar_livro(x.id))return 0;if(!x.id)x.id=proximo_id_livro++;if(x.id>=proximo_id_livro)proximo_id_livro=x.id+1;x.disponivel=x.total;return anexar_livro(x)&&salvar();}
// Impede reduzir o total abaixo dos exemplares emprestados.
int editar_livro(Livro x){Livro *p=buscar_livro(x.id);if(!p||!x.titulo[0]||!x.autor[0]||x.total<emprestimos_ativos_livro(x.id)||x.total<1)return 0;x.disponivel=x.total-emprestimos_ativos_livro(x.id);*p=x;return salvar();}
// Impede exclusão com empréstimo ativo; memmove reorganiza o vetor.
int excluir_livro(int id){if(emprestimos_ativos_livro(id))return 0;for(int i=0;i<quantidade_livros;i++)if(livros[i].id==id){memmove(livros+i,livros+i+1,(quantidade_livros-i-1)*sizeof *livros);quantidade_livros--;return salvar();}return 0;}
// Impede CPF repetido, exceto o registro sendo editado.
static int cpf_ja_cadastrado(const char *cpf,int except){for(int i=0;i<quantidade_usuarios;i++)if(usuarios[i].id!=except&&!strcmp(usuarios[i].cpf,cpf))return 1;return 0;}
// Valida nome/CPF, cria ID único, adiciona e salva.
int cadastrar_usuario(Usuario x){if(!x.nome[0]||!x.cpf[0]||cpf_ja_cadastrado(x.cpf,0)||(x.id&&buscar_usuario(x.id)))return 0;if(!x.id)x.id=proximo_id_usuario++;if(x.id>=proximo_id_usuario)proximo_id_usuario=x.id+1;return anexar_usuario(x)&&salvar();}
// Atualiza dados após validar o CPF e o ID.
int editar_usuario(Usuario x){Usuario *p=buscar_usuario(x.id);if(!p||!x.nome[0]||!x.cpf[0]||cpf_ja_cadastrado(x.cpf,x.id))return 0;*p=x;return salvar();}
// Recusa exclusão com empréstimos ativos e compacta o vetor.
int excluir_usuario(int id){if(emprestimos_ativos_usuario(id))return 0;for(int i=0;i<quantidade_usuarios;i++)if(usuarios[i].id==id){memmove(usuarios+i,usuarios+i+1,(quantidade_usuarios-i-1)*sizeof *usuarios);quantidade_usuarios--;return salvar();}return 0;}
// Confere livro, leitor, estoque e datas; registra retirada e diminui disponibilidade.
int emprestar(int id,int uid,const char *ret,const char *prev){Livro *l=buscar_livro(id);if(!l||!buscar_usuario(uid)||l->disponivel<1||strlen(ret)!=10||strlen(prev)!=10||strcmp(prev,ret)<0)return 0;Emprestimo e={0};e.id=proximo_id_emprestimo++;e.livro=id;e.usuario=uid;e.ativo=1;snprintf(e.retirada,sizeof e.retirada,"%s",ret);snprintf(e.prevista,sizeof e.prevista,"%s",prev);if(!anexar_emprestimo(e))return 0;l->disponivel--;return salvar();}
// Só aceita empréstimo ativo e data válida; devolve um exemplar ao estoque.
int devolver(int id,const char *data){for(int i=0;i<quantidade_emprestimos;i++)if(emprestimos[i].id==id&&emprestimos[i].ativo&&strlen(data)==10&&strcmp(data,emprestimos[i].retirada)>=0){Livro *l=buscar_livro(emprestimos[i].livro);if(!l)return 0;emprestimos[i].ativo=0;snprintf(emprestimos[i].devolucao,sizeof emprestimos[i].devolucao,"%s",data);l->disponivel++;return salvar();}return 0;}
// Grava os três conjuntos de registros em arquivos binários locais.
int salvar(void){FILE *f=fopen("dados/livros.dat.tmp","wb");if(!f)return 0;fwrite(&quantidade_livros,sizeof quantidade_livros,1,f);fwrite(livros,sizeof *livros,quantidade_livros,f);if(fclose(f))return 0;remove("dados/livros.dat");if(rename("dados/livros.dat.tmp","dados/livros.dat"))return 0;
f=fopen("dados/usuarios.dat.tmp","wb");if(!f)return 0;fwrite(&quantidade_usuarios,sizeof quantidade_usuarios,1,f);fwrite(usuarios,sizeof *usuarios,quantidade_usuarios,f);if(fclose(f))return 0;remove("dados/usuarios.dat");if(rename("dados/usuarios.dat.tmp","dados/usuarios.dat"))return 0;
f=fopen("dados/emprestimos.dat.tmp","wb");if(!f)return 0;fwrite(&quantidade_emprestimos,sizeof quantidade_emprestimos,1,f);fwrite(emprestimos,sizeof *emprestimos,quantidade_emprestimos,f);if(fclose(f))return 0;remove("dados/emprestimos.dat");return rename("dados/emprestimos.dat.tmp","dados/emprestimos.dat")==0;}
// Lê os arquivos existentes e reconstrói os vetores e próximos IDs.
void carregar(void){FILE *f;int n;f=fopen("dados/livros.dat","rb");if(f){if(fread(&n,sizeof n,1,f)==1&&n>=0&&n<100000){Livro x;for(int i=0;i<n&&fread(&x,sizeof x,1,f)==1;i++){anexar_livro(x);if(x.id>=proximo_id_livro)proximo_id_livro=x.id+1;}}fclose(f);}f=fopen("dados/usuarios.dat","rb");if(f){if(fread(&n,sizeof n,1,f)==1&&n>=0&&n<100000){Usuario x;for(int i=0;i<n&&fread(&x,sizeof x,1,f)==1;i++){anexar_usuario(x);if(x.id>=proximo_id_usuario)proximo_id_usuario=x.id+1;}}fclose(f);}f=fopen("dados/emprestimos.dat","rb");if(f){if(fread(&n,sizeof n,1,f)==1&&n>=0&&n<100000){Emprestimo x;for(int i=0;i<n&&fread(&x,sizeof x,1,f)==1;i++){anexar_emprestimo(x);if(x.id>=proximo_id_emprestimo)proximo_id_emprestimo=x.id+1;}}fclose(f);}}
// free libera memória alocada e zera os ponteiros e contadores.
void liberar(void){free(livros);free(usuarios);free(emprestimos);livros=NULL;usuarios=NULL;emprestimos=NULL;quantidade_livros=quantidade_usuarios=quantidade_emprestimos=0;}
