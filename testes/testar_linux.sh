#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
mkdir -p dados
cc -std=c11 -Wall -Wextra -Iinclude testes/teste_regras.c src/biblioteca.c -o testes/teste_regras
./testes/teste_regras
