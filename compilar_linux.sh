#!/bin/sh
cd "$(dirname "$0")" || exit 1
mkdir -p dados capas
gcc -std=c11 -Wall -Wextra -Iinclude src/main.c src/biblioteca.c -o Biblioteca
