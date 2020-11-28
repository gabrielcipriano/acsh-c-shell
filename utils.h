#if !defined(UTIL_H)
#define UTIL_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MAX 25    //24 maximum possible words + 1 reserved (Explained in execBackgroundComands() )
#define SZSTR 50  //word max size

//diretorio atual
char cwd[100];

//Encaminha o sinal SIGUSR1 recebido
void handlerSIGUSR1(int signal);

//Recebe um vetor de comandos e argumentos do usuario
int getLine(char** v, int i);

//Armazena o espaço dinamicamente para o vetor de entrada
int alocaVetor(char** v, size_t size);

//Libera(free) o vetor de entrada
int liberaVetor(char** v, size_t size);

//Faz o fork e checa se ele deu certo
pid_t forkAndCheck();

//Executa um comando em Foreground
int runFgProcess(char** v, int size);

//Executa um grupo de comandos em Background
void execBackgroundComands(char** v, int sz);

//Executa um comando unico em Background
void execBackgroundComand(char** v, int lst);

//Analisa se duas strings são iguais(strcmp == 0) 
int streq(char* s1, char* s2);

//Retorna a quantidade de comandos em background passados pelo usuário
int qtdComandosBackground(char** v, int size);

//Executa um comando passado em um vetor de comandos
void execSliceOfVargs(char** v, int bgn, int lst);

//semelhando ao comando "cd"
int changeDir(char* dir);

#endif /*UTIL_H*/