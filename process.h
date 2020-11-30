#if !defined(PROCESS_H)
#define PROCESS_H

//Executa um comando em Foreground
int runFgProcess(char** v, int size);

//Executa um grupo de comandos em Background
void execBackgroundComands(char** v, int sz);

//Executa um comando unico em Background
void execBackgroundComand(char** v, int lst);

//Retorna a quantidade de comandos em background passados pelo usuário
int qtdComandosBackground(char** v, int size);

//Executa um comando passado em um vetor de comandos
void execSliceOfVargs(char** v, int bgn, int lst);

#endif /*PROCESS_H*/