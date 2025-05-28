#include <stdio.h>

int main() {
    char nombreArchivo[256];
    FILE *archivo;
    char linea[512];

    printf("Ingrese el nombre del archivo: ");
    if (scanf("%255s", nombreArchivo) != 1) {
        printf("Error al leer el nombre del archivo.\n");
        return 1;
    }

    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo '%s'.\n", nombreArchivo);
        return 1;
    }

    for (; fgets(linea, sizeof(linea), archivo) != NULL; ) {
        printf("%s", linea);
    }

    fclose(archivo);
    return 0;
}