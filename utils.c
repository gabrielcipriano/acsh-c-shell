#include "utils.h"

#include <stdio.h>
#include <string.h>

// Maneira mais segura de adquirir um imput do teclado
int getLine(char *mensagem, char *buff, size_t size) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (mensagem != NULL) {
        printf("%s \n", mensagem);
        fflush(stdout);
    }
    if (fgets(buff, size, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff) - 1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff) - 1] = '\0';
    return OK;
}

void imprimeArray(int *arr, int size) {
    printf("[");
    for (int i = 0; i < size - 1; i++)
        printf("%d, ", arr[i]);
    printf("%d]\n", arr[size - 1]);
}

int somaArray(int *array, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}