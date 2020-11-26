#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int i = 0;
    char v[5][50];
    while (1) {
        printf("acsh> ");
        while (scanf("%s", v[i]) == 1) {
            printf("%d %s \n", i, v[i]);
            i++;
            if (getchar() == '\n') {
                break;
            }
        }
        i = 0;
    }
    return 0;
}
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