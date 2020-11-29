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

//UTILSIGNAL
void setSignalsIgnore() {
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

//UTILSIGNAL
void handlerVACINADO(int sig) {
    setSignalsIgnore();
    char c;
    switch (sig) {
        case SIGINT:
            c = 'C';
            break;
        case SIGQUIT:
            c = '\\';
            break;
        case SIGTSTP:
            c = 'Z';
            break;
        default:  //Never gonna happen
            c = '.';
            break;
    }
    printf("Não adianta me enviar o sinal por Ctrl-%c. Estou vacinado!!\n", c);
    setSignalsVacinado();
}

//UTILSIGNAL
void setSignalsVacinado() {
    signal(SIGINT, handlerVACINADO);
    signal(SIGQUIT, handlerVACINADO);
    signal(SIGTSTP, handlerVACINADO);
}

//UTILSIGNAL
void handlerSIGUSR1(int signal) {
    printf("SIGNAL: %d PID: %d\n", signal, getpid());
    exit(signal);
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

void execSliceOfVargs(char** v, int bgn, int lst) {
    if (lst - bgn > 4) {  //Checa se tem mais de 3 argumentos num comando.
        printf("ERRO: Numero de argumentos maior que o esperado. Maximo 3 args.\n");
        printf("      Comando %s ignorado.\n", v[bgn]);
    } else {
        v[lst + 1] = NULL;
        char** argv = v + bgn;
        execvp(argv[0], argv);
        printf("Algo deu errado com o comando %s. \n ERRO: %s\n", argv[0], strerror(errno));
    }
    liberaVetor(v, MAX);
    exit(1);
}

int runFgProcess(char** v, int len) {
    pid_t pid = forkAndCheck();

    if (pid == 0) {
        execSliceOfVargs(v, 0, len - 2);
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

//UTILSIGNAL
void handler_MORTEDOACSH(int sig) {
    printf("**FILHO: Acsh morreu, vou morrer tbm\n");
    kill(-1 * getpid(), SIGKILL);  //matando filhos
    exit(1);
}

//UTILSIGNAL
void setPaiSignals() {
    signal(SIGUSR1, SIG_IGN);
    signal(SIGUSR2, handler_MORTEDOACSH);
    prctl(PR_SET_PDEATHSIG, SIGUSR2);  //Recebe SIGUSR2 se o acsh morrer
}

void execBackgroundComands(char** v, int len) {
    int parentPid = forkAndCheck();
    if (parentPid == 0) {
        //pai dos processos/filhos
        setsid();
        setPaiSignals();

        printf("SESSION ID: %d\n", getpid());  //DEBUG
        pid_t pid;
        int bgn = 0;  //Auxiliar para definir o começo de um comando

        //A posição seguinte da ultima tambem recebe um "<3" para generalizar o loop
        strcpy(v[len], "<3");

        //Percorre pelo vetor de comandos
        for (int j = 0; j <= len; j++) {
            if (streq(v[j], "<3")) {
                pid = forkAndCheck();
                if (pid == 0) {
                    // printf("Comando: %s PID: %d\n", v[bgn], getpid()); //Debug
                    execSliceOfVargs(v, bgn, j - 1);
                }
                bgn = j + 1;  // Passa para o proximo comando
            }
        }
        // Lidando com os filhos
        int status;
        while (wait(&status) > 0) {
            if (status == SIGUSR1) {
                kill(-getpid(), SIGKILL);  //Mata todos os filhos
            }
        }
        exitSafe(0, v);  //Todos filhos finalizaram
    }
}

//Executa um comando isolado
void execBackgroundComand(char** v, int len) {
    int paiPid = forkAndCheck();
    if (paiPid == 0) {
        //pai do processo que executará o comando
        setsid();
        setPaiSignals();
        printf("SESSION ID: %d\n", getpid());  //DEBUG

        pid_t pid = forkAndCheck();

        if (pid == 0) {
            //Comando
            execSliceOfVargs(v, 0, len - 1);
        }
        int status;
        wait(&status);
        exitSafe(0, v);
    }
}

int changeDir(char* dir) {
    if (chdir(dir) == -1) {
        printf("Diretorio não encontrado.\n");
    }
    printf("Diretorio Atual: %s \n", getcwd(cwd, 100));
}