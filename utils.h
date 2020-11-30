#if !defined(UTIL_H)
#define UTIL_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "process.h"
#include "utilsSignal.h"

#define MAX 25    //24 maximum possible words + 1 reserved (Explained in execBackgroundComands() )
#define SZSTR 50  //word max size

#define PRMPT "acsh> "

//UTIL: diretorio atual
char cwd[100];

//UTIL: Termina execução de maneira segura.
void exitSafe(int, char**);

//UTIL: Recebe um vetor de comandos e argumentos do usuario
int getLine(char** v);

//UTIL: Armazena o espaço dinamicamente para o vetor de entrada
int alocaVetor(char** v, size_t size);

//UTIL: Libera(free) o vetor de entrada
int liberaVetor(char** v, size_t size);

//UTIL: Faz o fork e checa se ele deu certo
pid_t forkAndCheck();

//UTIL: Analisa se duas strings são iguais(strcmp == 0)
int streq(char* s1, char* s2);

//UTIL: semelhando ao comando "cd"
int changeDir(char* dir);

#endif /*UTIL_H*/