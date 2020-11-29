#include <errno.h>
#include <stdio.h>

#include "utils.h"

int main(int argc, char* argv[]) {
    setSignalsVacinado();

    getcwd(cwd, 100);
    int len;
    char* v[SZSTR];

    alocaVetor(v, MAX);

    while (1) {
        printf("%s", PRMPT);

        //Recebe um linha de input
        len = getLine(v);

        char* lastWord = v[len - 1];

        if (streq(lastWord, "%")) {
            setSignalsIgnore();
            runFgProcess(v, len);
            setSignalsVacinado();
            continue;
        }
        if (streq(v[0], "cd")) {
            if (len != 2) {
                printf("quantidade errada de argumentos. Tente 'cd /nome/do/diretorio'\n");
            } else {
                changeDir(lastWord);
            }
            continue;
        }
        if (streq(lastWord, "exit") && len == 1) {
            exitSafe(0, v);
        }

        int qtdComandosBg;
        if ((qtdComandosBg = qtdComandosBackground(v, len)) == -1) {
            printf("ERRO: Quantidade de comandos maior que o esperado.\n");
            printf("      Maximo: 5 comandos.\n");
            continue;
        }
        if (qtdComandosBg > 1) {
            execBackgroundComands(v, len);
        } else {
            //qtdComandosBackground() == 1;
            execBackgroundComand(v, len);
        }
        //sleep(1);  //Deixar comando de print instantâneo ganhar a corrida pelo stdout
    }
}
