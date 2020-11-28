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

pid_t pai = -1;

int nenhumPaiCriado() {
    return pai == -1;
}

int main(int argc, char* argv[]) {
    int i = 0;
    char* v[5];
    char* s = "string";
    for (int j = 0; j < 5; j++) {
        v[j] = (char*)malloc(sizeof(char) * 50);
        v[j] = strcpy(v[j], s);
    }
    v[3] = strcpy(v[3], "aff");
    char** vetor = v + 2;

    for (int i = 0; i < 3; i++) {
        printf("%s\n", vetor[i]);
    }
}
