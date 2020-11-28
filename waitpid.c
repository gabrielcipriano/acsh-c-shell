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

void handlerSigusr1(int signal) {
    exit(signal);
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        //filho
        signal(SIGUSR1, handlerSigusr1);
        printf("A mimir 1 - meu pid: %d\n", -getpid());
        sleep(180);

        printf("morri de causas naturais\n");

    } else {
        //pai
        pid_t pid2 = fork();
        if (pid2 == 0) {
            signal(SIGUSR1, handlerSigusr1);
            printf("A mimir 2 - meu pid: %d\n", -getpid());
            sleep(180);

            return 0;
        }

        printf("child PID: %d\n", pid);
        int status;
        wait(&status);
        if (WEXITSTATUS(status) == SIGUSR1) {
            printf("MEU FILHO MORREU DE COVID!!\n");
            kill(-getpid(), SIGKILL);
        } else {
            printf("Meu filho morreu mas n foi de COVID\n");
        }
    }

    return 0;
}