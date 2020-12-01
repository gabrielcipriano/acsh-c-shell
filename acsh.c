#include <stdio.h>

#include "process.h"
#include "utils.h"
#include "utilsSignal.h"

// Lidando com comando foreground
int isForegroundCommand(char** v, int len) {
    return streq(v[len - 1], "%");
}
void doForegroundCommand(char** v, int len) {
    setSignalsIgnore();
    execForegroundCommand(v, len);
    setSignalsVacinado();
}

//Lidando com a operação interna cd
int isCdOperation(char** v, int len) {
    return (streq(v[0], "cd"));
}
void doCdOperation(char** v, int len) {
    if (len != 2) {
        printf("quantidade errada de argumentos. Tente 'cd /nome/do/diretorio'\n");
    } else {
        changeDir(v[1]);
    }
}

// Lidando com a operação interna exit
int isExitOperation(char** v, int len) {
    return (streq(v[0], "exit") && len == 1);
}

// Lidando com o um ou mais processos background
void dealWithBackgroundCommands(char** v, int len) {
    int quantidadeComandosBg = qtdComandosBackground(v, len);
    switch (quantidadeComandosBg) {
        case -1:  //error code
            printf("ERRO: Quantidade de comandos maior que o esperado.\n");
            printf("      Maximo: 5 comandos.\n");
            break;
        case 1:
            execBackgroundCommand(v, len);
            break;
        default:
            execBackgroundCommands(v, len);
            break;
    }
}

int main(int argc, char* argv[]) {
    setSignalsVacinado();
    getcwd(cwd, 100);  //armazena diretório atual

    int len;  //quantidade de words numa linha
    char* v[SZSTR];
    alocaVetor(v, MAX);

    while (1) {
        printf("%s", PRMPT);
        //Recebe um linha de input e armazena em v
        len = getLine(v);

        if (isForegroundCommand(v, len)) {
            doForegroundCommand(v, len);
            continue;
        }
        if (isCdOperation(v, len)) {
            doCdOperation(v, len);
            continue;
        }
        if (isExitOperation(v, len)) {
            exitSafe(0, v);
        }
        dealWithBackgroundCommands(v, len);
        //sleep(1);  //Deixar comando de print instantâneo ganhar a corrida pelo stdout
    }
}
