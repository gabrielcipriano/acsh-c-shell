#include "process.h"

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

int execForegroundCommand(char** v, int len) {
    pid_t pid = forkAndCheck();

    if (pid == 0) {
        execSliceOfVargs(v, 0, len - 2);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
    return 0;
}

int qtdComandosBackground(char** v, int size) {
    //Possui ao menos 1 potencial comando
    int count = 1;
    // Cada CMD_SEP encontrado significa que tem mais um comando.
    for (int i = 0; i < size; i++) {
        if (streq(v[i], CMD_SEP)) {
            count++;
        }
    }
    //Caso o usuario passou mais de 5 comandos, retorna -1 como erro
    if (count > 5) {
        return -1;
    }
    return count;
}

void execBackgroundCommands(char** v, int len) {
    int parentPid = forkAndCheck();
    if (parentPid == 0) {
        //pai dos processos/filhos
        setsid();
        setPaiSignals();

        //printf("SESSION ID: %d\n", getpid());  //DEBUG
        pid_t pid;
        int bgn = 0;  //Auxiliar para definir o começo de um comando

        //A posição seguinte da ultima tambem recebe um CMD_SEP para generalizar o loop
        strcpy(v[len], CMD_SEP);

        //Percorre pelo vetor de comandos
        for (int j = 0; j <= len; j++) {
            if (streq(v[j], CMD_SEP)) {
                pid = forkAndCheck();
                if (pid == 0) {
                    // printf("Comando: %s PID: %d\n", v[bgn], getpid()); //Debug
                    execSliceOfVargs(v, bgn, j - 1);
                }
                bgn = j + 1;  // Passa para o proximo comando
            }
        }
        // Pai da sessão lidando com os filhos
        int status;
        while (wait(&status) > 0) {
            if (status == SIGUSR1) {
                kill(-getpid(), SIGKILL);  //Mata todos os filhos
            }
        }
        exitSafe(0, v);  //Todos filhos finalizaram, pai da sessão pode morrer.
    }
}

//Executa um comando isolado
void execBackgroundCommand(char** v, int len) {
    int paiPid = forkAndCheck();
    if (paiPid == 0) {
        //pai do processo que executará o comando
        setsid();
        signal(SIGUSR1, SIG_IGN);  //Ignorando o SIGUSR1
        setPaiSignals();
        // printf("SESSION ID: %d\n", getpid());  //DEBUG

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