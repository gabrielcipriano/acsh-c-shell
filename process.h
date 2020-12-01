#if !defined(PROCESS_H)
#define PROCESS_H

// #include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "utils.h"
#include "utilsSignal.h"

//Separador de comandos
#define CMD_SEP "<3"

//Executa um comando em Foreground
int execForegroundCommand(char** v, int size);

//Executa um grupo de comandos em Background
void execBackgroundCommands(char** v, int sz);

//Executa um comando unico em Background
void execBackgroundCommand(char** v, int lst);

//Retorna a quantidade de comandos em background passados pelo usuário
int qtdComandosBackground(char** v, int size);

//Executa um comando passado em um vetor de comandos
void execSliceOfVargs(char** v, int bgn, int lst);

#endif /*PROCESS_H*/