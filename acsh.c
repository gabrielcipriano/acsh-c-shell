#include "utils.h"

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
