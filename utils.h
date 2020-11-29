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

#define MAX 25    //24 maximum possible words + 1 reserved (Explained in execBackgroundComands() )
#define SZSTR 50  //word max size

#define PRMPT "acsh> "

//UTIL: diretorio atual
char cwd[100];

//Fica vacinado aos sinais recebidos pelo teclado
void setSignalsVacinado();

// Ignora os sinais recebidos pelo teclado
void setSignalsIgnore();

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

//Executa um comando em Foreground
int runFgProcess(char** v, int size);

//Executa um grupo de comandos em Background
void execBackgroundComands(char** v, int sz);

//Executa um comando unico em Background
void execBackgroundComand(char** v, int lst);

//UTIL: Analisa se duas strings são iguais(strcmp == 0)
int streq(char* s1, char* s2);

//Retorna a quantidade de comandos em background passados pelo usuário
int qtdComandosBackground(char** v, int size);

//Executa um comando passado em um vetor de comandos
void execSliceOfVargs(char** v, int bgn, int lst);

//UTIL: semelhando ao comando "cd"
int changeDir(char* dir);

#endif /*UTIL_H*/