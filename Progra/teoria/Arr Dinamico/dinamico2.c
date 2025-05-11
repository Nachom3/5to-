#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LARGO_PALABRA 30

int main(){
    char **palabras;
    char buffer[MAX_LARGO_PALABRA];
    int cant_palabras;

    printf("Ingrese la cantidad de palabras\n");
    scanf("%d", &cant_palabras);

    palabras = malloc(sizeof(char*) *cant_palabras);

    for(int i = 0; i < cant_palabras; i++) {
        scanf("%s", buffer);
        palabras[i] = malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(palabras[i], buffer);
    }

    for(int i = 0; i < cant_palabras; i++)
        printf("%s\n", palabras[i]);

    for(int i = 0; i < cant_palabras; i++)
        free(palabras[i]);

    free(palabras);
    return 0;
}