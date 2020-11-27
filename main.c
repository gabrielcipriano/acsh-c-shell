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
    int pid[5];
    int filho = 0;
    for(int j=0; j < 5; j++){
        v[j] = (char*)malloc(sizeof(char)*50);
    }
    while (1) {
        printf("acsh> ");
        while (scanf("%s", v[i]) == 1) {
            printf("%d %s \n", i, v[i]);
            if (strcmp(v[i],"<3") == 0) {
                pid[filho] = fork();
                printf("%d\n", pid[filho]);
                if (pid[filho++] == 0) {
                    v[i] = NULL;
                    //v[i + 1] = NULL;
                    execvp(v[0], v);
                }
                i = -1;
            }
            if (v[i] == "%") {
            }
            if (v[i] == "cd") {
            }
            if (v[i] == "exit") {
            }
            if (getchar() == '\n') {
                /*
                pid[filho] = fork();
                printf("%d\n", pid[filho]);
                if (pid[filho++] == 0) {
                    v[i] = NULL;
                    v[i + 1] = NULL;
                    execvp(v[0], v);
                }
                i = -1; */
                break;
            }
            i++;
        }
        i = 0;
    }
    return 0;
}