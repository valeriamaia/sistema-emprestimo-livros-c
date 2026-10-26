@echo off
cd /d "%~dp0"
if not exist dados mkdir dados
if not exist capas mkdir capas
gcc -std=c11 -Wall -Wextra -Iinclude src\main.c src\biblioteca.c -o Biblioteca.exe -lws2_32
if errorlevel 1 (
 echo ERRO NA COMPILACAO
 pause
 exit /b 1
)
echo COMPILACAO CONCLUIDA. Execute Biblioteca.exe
pause
