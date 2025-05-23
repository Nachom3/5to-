#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CANT_PALABRAS 4
#define MAX_LARGO_PALABRA 30

int main(){
    char *palabras[CANT_PALABRAS];
    char buffer[MAX_LARGO_PALABRA];
    int cant_palabras;

    for(int i = 0; i < CANT_PALABRAS; i++) {
        scanf("%s", buffer);
        palabras[i] = malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(palabras[i], buffer);
    }

    for(int i = 0; i < CANT_PALABRAS; i++)
        printf("%s\n", palabras[i]);

    for(int i = 0; i < CANT_PALABRAS; i++)
        free(palabras[i]);

    return 0;
}