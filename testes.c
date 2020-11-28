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

#define MAX 25    //Maximum of strings in a imput
#define SZSTR 50  //String max size

int getLine(char** v, int i) {
    i = 0;
    while (scanf("%s", v[i]) == 1) {
        i++;
        if (getchar() == '\n') {
            break;
        }
    }
    return i;
}

int runFgProcess(char** v, int size) {
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        printf("não foi possivel criar filho! \n %s\n", strerror(errno));
        exit(1);
    }
    if (pid == 0) {
        v[size - 1] = NULL;
        execvp(v[0], v);
        printf("Algo deu errado \n");
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
    return 0;
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

int maisDeUmProcesso(char** v, int size) {
    for (int i = 0; i < size; i++) {
        if (streq(v[i], "<3")) {
            return 1;
        }
    }
    return 0;
}

//diretorio atual
char cwd[100];

int changeDir(char* dir) {
    if (chdir(dir) == -1) {
        printf("Diretorio não encontrado.\n");
    }
    printf("Diretorio Atual: %s \n", getcwd(cwd, 100));
}

void createProcess(char** v, int bgn, int lst) {
    pid_t pid = fork();
    if (pid == -1) {
        printf("não foi possivel criar filho! \n %s\n", strerror(errno));
        exit(1);
    }
    if (pid == 0) {
        //filho
        v[lst] = NULL;
        char** argv = v + bgn;
        execvp(argv[0], argv);
        printf("Algo deu errado com o comando de PID %d. \n ERRO: %s\n", pid, strerror(errno));
        liberaVetor(v, MAX);
        exit(1);
    } else {
        //pai
    }
}

int main(int argc, char* argv[]) {
    getcwd(cwd, 100);
    int i;
    char* v[SZSTR];
    alocaVetor(v, MAX);

    while (1) {
        printf("acsh> ");
        i = getLine(v, i);
        char* last = v[i - 1];
        if (streq(last, "%")) {
            runFgProcess(v, i);
            continue;
        }
        if (streq(v[0], "cd")) {
            if (i != 2) {
                printf("quantidade errada de argumentos. Tente 'cd /nome/do/diretorio'\n");
            } else {
                changeDir(last);
            }
            continue;
        }
        if (streq(last, "exit") && i == 1) {
            return liberaVetor(v, MAX);
        }
        if (maisDeUmProcesso(v, i)) {
            //Mais de um processo
            int pid = fork();
            if (pid == -1) {
                printf("não foi possivel criar filho! \n %s\n", strerror(errno));
                exit(1);
            }
            if (pid == 0) {
                //pai dos filhos
                setsid();
                int j;
                int bgn = 0;
                v[i] = "<3";
                for (j = 0; j <= i; j++) {
                    if (streq(v[j], "<3")) {
                        createProcess(v, bgn, j);
                        bgn = j + 1;
                    }
                }
                // TODO: SINAIS
                liberaVetor(v, MAX);
                exit(1);
            }
        } else {
            //Processo unico
            int pid = fork();
            if (pid == 0) {
                signal(SIGUSR1, SIG_IGN);
                v[i] = NULL;
                execvp(v[0], v);
                printf("Algo deu errado com o comando de PID %d. \n ERRO: %s\n", pid, strerror(errno));
                liberaVetor(v, MAX);
                exit(1);
            } else {
                //Processo pai
                sleep(1);
                printf("PID: %d \n", pid);
            }
        }
    }
}
