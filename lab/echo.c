#include <stdio.h>
#include <string.h>

int main() {
    char nombreArchivo[100];
    char linea[256];

    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);

    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    getchar();

    while (1) {
        fgets(linea, sizeof(linea), stdin);
        if (strcmp(linea, ":q\n") == 0) {
            break;
        }
        fputs(linea, archivo);
    }

    fclose(archivo);
    return 0;
}
