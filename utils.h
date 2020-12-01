#if !defined(UTIL_H)
#define UTIL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 25    //24 maximum possible words + 1 reserved (Explained in execBackgroundCommands() )
#define SZSTR 50  //word max size

#define PRMPT "acsh> "

//diretorio atual
char cwd[100];

//Termina execução de maneira segura.
void exitSafe(int, char**);

//Recebe uma linha do input e alimenta o vetor v com as words dessa linha
int getLine(char** v);

// Armazena o espaço dinamicamente para o vetor de entrada
int alocaVetor(char** v, size_t size);

//Libera o vetor de entrada
int liberaVetor(char** v, size_t size);

//Faz o fork e checa se ele deu certo
pid_t forkAndCheck();

//Analisa se duas strings são iguais(strcmp == 0)
int streq(char* s1, char* s2);

//Executa o comando "cd" para o diretorio dir
int changeDir(char* dir);

#endif /*UTIL_H*/