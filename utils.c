#include "utils.h"

#include <stdio.h>
#include <string.h>

void exitSafe(int status, char** v) {
    liberaVetor(v, MAX);
    exit(status);
}

void cleanBuffer() {
    while ((getchar()) != '\n') {
        //cleaning
    };
}

int getLine(char** v) {
    int len = 0;
    while (scanf("%s", v[len]) == 1) {
        len++;
        if (getchar() == '\n') {
            break;
        }
        if (len == MAX - 1) {  //Limite de input atingido
            printf("Quantidade maxima de words atingida, tente novamente.\n%s", PRMPT);
            cleanBuffer();
            len = 0;
        }
    }
    return len;
}

pid_t forkAndCheck() {
    pid_t pid = fork();
    if (pid == -1) {
        printf("não foi possivel criar filho! \n %s\n", strerror(errno));
        exit(1);
    }
    return pid;
}

int alocaVetor(char** v, size_t size) {
    for (int j = 0; j < size; j++)
        v[j] = (char*)malloc(sizeof(char) * SZSTR);
    return 0;
}
int liberaVetor(char** v, size_t size) {
    for (int j = 0; j < MAX; j++)
        free(v[j]);
    return 0;
}
int streq(char* s1, char* s2) {
    return strcmp(s1, s2) == 0;
}

int changeDir(char* dir) {
    if (chdir(dir) == -1) {
        printf("Diretorio não encontrado.\n");
    }
    printf("Diretorio Atual: %s \n", getcwd(cwd, 100));
}