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
int main(int argc, char* argv[]) {
    printf("A mimir\n");
    sleep(120);
    printf("A cordei\n");
    return 0;
}