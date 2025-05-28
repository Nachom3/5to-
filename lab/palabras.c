#include <stdio.h>
#include <string.h>

int main() {
    char nombreArchivo[100];
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);

    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    char linea[1024];
    int total_palabras = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        int i = 0;
        int en_palabra = 0;

        while (linea[i] != '\0') {
            if (linea[i] != ' ' && linea[i] != '\n' && linea[i] != '\t') {
                if (!en_palabra) {
                    total_palabras++;
                    en_palabra = 1;
                }
            } else {
                en_palabra = 0;
            }
            i++;
        }
    }

    fclose(archivo);
    printf("Cantidad de palabras: %d\n", total_palabras);
    return 0;
}
