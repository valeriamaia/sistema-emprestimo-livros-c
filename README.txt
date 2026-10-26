MINHA BIBLIOTECA - EMPRESTIMO DE LIVROS
==========================================
Inspiracao visual: catalogo e busca da plataforma MEC Livros (sem uso de marca ou codigo do MEC).
O projeto e independente, para gerenciar exemplares de uma biblioteca local; nao permite leitura digital de livros protegidos.

REQUISITOS: Windows 10/11 com GCC MSYS2 UCRT64 (MinGW-w64), ou Linux com GCC.
Windows: abra esta pasta no VS Code e execute .\compilar.bat no PowerShell.
Depois execute .\Biblioteca.exe e acesse http://localhost:8765 no navegador.
Linux: sh compilar_linux.sh; ./Biblioteca

FUNCIONALIDADES: painel, catalogo com capas, pesquisa, cadastro/edicao/exclusao de livros,
cadastro/edicao/exclusao de leitores, emprestimos, devolucoes e disponibilidade.
Capas: no formulario de cadastro ou edicao, clique em Escolher arquivo e selecione JPG, PNG ou BMP (ate 5 MB). O programa salva automaticamente em capas/ e associa a imagem ao livro.
Dados locais em dados/*.dat. Nao reutilize dados de outro projeto sem backup.
Para acessar de um celular na mesma rede, use http://IP-DO-PC:8765 com o servidor aberto.
Nao exponha este servidor a internet: nao possui autenticacao nem HTTPS.

ESTRUTURA:
 src/main.c       - interface web e servidor HTTP escritos em C
 src/biblioteca.c - regras de negocio e persistencia em C
 include/biblioteca.h - structs e prototipos
 testes/teste_regras.c - testes basicos do nucleo

NOTA TECNICA: A logica e o servidor sao em C; HTML e CSS sao enviados como texto pelo programa C.
A interface nao e escrita apenas em C no sentido estrito, pois navegadores interpretam HTML/CSS.
As operacoes de alteracao de dados devem ser usadas apenas em rede local confiavel.

RELATORIO: usar o documento academico fornecido pela equipe; preencher evidencias reais apos testar no Windows.

ATUALIZACAO: formulario de livros com envio direto de capas pelo navegador.
