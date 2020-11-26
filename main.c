#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int i = 0;
    char* v[5];
    int pid[4];
    int filhos = 0;
    while (1) {
        printf("acsh> ");
        char tmp[50];
        while (scanf("%s", tmp)) {
            strcpy(v[i], tmp);
            printf("%d %s \n", i, v[i++]);
            // if (v[i] == "<3") {
            //     pid[filhos] = fork();
            //     printf("%d", pid[filhos]);
            //     if (pid[filhos++] == 0) {
            //         v[i + 1] = NULL;
            //         execvp(v[0], v);
            //     }
            //     i = -1;
            // }
            // if (v[i] == "%") {
            // }
            // if (v[i] == "cd") {
            // }
            // if (v[i] == "exit") {
            // }
            // i++;
        }
        printf("teste\n");
    }
    return 0;
}