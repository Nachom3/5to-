#include <stdio.h>
#include <string.h>
#include <ctype.h>

void pasarpalabra(char linea[], int* i, char palabra[]);

int main() {
    char nombreArchivo[100];
    char palabraBuscada[100];

    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);

    printf("Ingrese la palabra a buscar: ");
    scanf("%s", palabraBuscada);

    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    char linea[1024];
    char palabra[100];
    int contador = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        int i = 0;
        while (linea[i] != '\0') {
            pasarpalabra(linea, &i, palabra);
            if (strcmp(palabra, palabraBuscada) == 0) {
                contador++;
            }
        }
    }

    fclose(archivo);

    printf("La palabra '%s' aparece %d veces.\n", palabraBuscada, contador);
    return 0;
}

void pasarpalabra(char linea[], int* i, char palabra[]) {
    int j = 0;

    while (linea[*i] != '\0' && isspace(linea[*i])) { // si estoy en un terminador o un espacio, lo salto.
        (*i)++;
    }
    while (linea[*i] != '\0' && !isspace(linea[*i])) { // copio los caracteros hasta encontrar un espacio o terminador
        palabra[j++] = linea[*i];
        (*i)++;
    }

    palabra[j] = '\0';
}
