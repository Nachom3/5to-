//9. Escribi un programa que defina una funcion ordenar que reciba un array de cadenas de caracteres y las ordene en orden alfabetico ascendente. Encontra la forma de definirla de manera de no desplazar las cadenas de caracteres en memoria.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LARGO 30

void ordenar(char **palabras, int);

int main(){
    char **palabras;
    int cantidad_palabras;
    char buffer[MAX_LARGO];
    
    scanf("%d", &cantidad_palabras);

    palabras = malloc(sizeof(char*) * cantidad_palabras);
    
    for(int i=0; i<cantidad_palabras ; i++){
        scanf("\n%s", buffer);
        palabras[i] = malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(palabras[i], buffer);
    }
    
    ordenar(palabras, cantidad_palabras);
    
    for(int i = 0; i < cantidad_palabras; i++)
        printf("%s\n", palabras[i]);

    for(int i = 0; i < cantidad_palabras; i++)
        free(palabras[i]);

    free(palabras);

    return 0;
}

void ordenar(char **palabras, int cant_palabras){
    char *aux;
    for(int i = 0; i < cant_palabras - 1; i++) {
            if(strcmp(palabras[i], palabras[i+1]) > 0){
                aux = palabras[i];
                palabras[i] = palabras[i+1];
                palabras[i+1] = aux;
            }
    }
}