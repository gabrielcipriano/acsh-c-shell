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

void handlerSIGUSR1(int signal) {
    printf("SIGNAL: %d PID: %d\n", signal, getpid());
    exit(signal);
}

int getLine(char** v, int i) {
    i = 0;
    while (scanf("%s", v[i]) == 1) {
        i++;
        if (getchar() == '\n') {
            break;
        }
        if (i == MAX - 1) {  //Limite de input atingido
            printf("Quantidade maxima de words atingida, tente novamente.");
        }
    }
    return i;
}

pid_t forkAndCheck() {
    pid_t pid = fork();
    if (pid == -1) {
        printf("não foi possivel criar filho! \n %s\n", strerror(errno));
        exit(1);
    }
    return pid;
}

int runFgProcess(char** v, int size) {
    pid_t pid = forkAndCheck();

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

int qtdComandosBackground(char** v, int size) {
    //Possui ao menos 1 potencial comando
    int count = 1;
    // Cada "<3" encontrado significa que tem mais um comando.
    for (int i = 0; i < size; i++) {
        if (streq(v[i], "<3")) {
            count++;
        }
    }
    //Caso o usuario passou mais de 5 comandos, retorna -1 como erro
    if (count > 5) {
        return -1;
    }
    return count;
}

void execSliceOfVargs(char** v, int bgn, int lst) {
    if (lst - bgn > 4) {  //Checa se tem mais de 3 argumentos num comando.
        printf("ERRO: Numero de argumentos maior que o esperado. Maximo 3 args.\n");
        printf("      Comando %s ignorado.\n", v[bgn]);
    } else {
        v[lst] = NULL;
        char** argv = v + bgn;
        execvp(argv[0], argv);
        printf("Algo deu errado com o comando %s. \n ERRO: %s\n", argv[0], strerror(errno));
    }
    liberaVetor(v, MAX);
    exit(1);
}

void execBackgroundComands(char** v, int sz) {
    int parentPid = forkAndCheck();
    if (parentPid == 0) {
        //pai dos processos/filhos
        setsid();
        pid_t pid;
        int bgn = 0;  //Auxiliar para definir o começo de um comando

        //A ultima posição tambem recebe um "<3" para generalizar o loop
        v[sz] = "<3";

        //Percorre pelo vetor de comandos
        for (int j = 0; j <= sz; j++) {
            if (streq(v[j], "<3")) {
                pid = forkAndCheck();
                if (pid == 0) {
                    //FILHO
                    signal(SIGUSR1, handlerSIGUSR1);
                    printf("Comando: %s PID: %d\n", v[bgn], getpid());
                    execSliceOfVargs(v, bgn, j);
                }
                bgn = j + 1;  // Passa para o proximo comando
            }
        }

        // Lidando com os filhos
        // int status;
        // while (wait(&status) > 0) {
        //     if (WEXITSTATUS(status) == SIGUSR1) {
        //         printf("MEU FILHO MORREU DE COVID!!\n");
        //         kill(-getpid(), SIGKILL);
        //     }
        // }
        liberaVetor(v, MAX);
        exit(1);
    }
}

//Executa um comando isolado
void execBackgroundComand(char** v, int lst) {
    int pid = forkAndCheck();
    if (pid == 0) {
        signal(SIGUSR1, SIG_IGN);
        execSliceOfVargs(v, 0, lst);
    }
}

//diretorio atual
char cwd[100];

int changeDir(char* dir) {
    if (chdir(dir) == -1) {
        printf("Diretorio não encontrado.\n");
    }
    printf("Diretorio Atual: %s \n", getcwd(cwd, 100));
}

int main(int argc, char* argv[]) {
    getcwd(cwd, 100);
    int i;
    char* v[SZSTR];

    alocaVetor(v, MAX);

    while (1) {
        printf("acsh> ");

        //Recebe um linha de input
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

        int qtdComandosBg;
        if ((qtdComandosBg = qtdComandosBackground(v, i)) == -1) {
            printf("ERRO: Quantidade de comandos maior que o esperado.\n");
            printf("      Maximo: 5 comandos.\n");
            continue;
        }
        if (qtdComandosBg > 1) {
            execBackgroundComands(v, i);
        } else {
            //qtdComandosBackground() == 1;
            execBackgroundComand(v, i);
        }
    }
}
