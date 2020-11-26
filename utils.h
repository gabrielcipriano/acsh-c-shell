#if !defined(UTIL_H)
#define UTIL_H

#include <stdlib.h>

enum statusCode {
    OK,
    NO_INPUT,
    TOO_LONG
};

int getLine(char *mensagem, char *buff, size_t size);
void imprimeArray(int *arr, int size);
int somaArray(int *array, int size);

#endif