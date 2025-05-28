#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char nombreArchivo[100];
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);

    FILE *entrada = fopen(nombreArchivo, "r");
    if (entrada == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    int conteo[26] = {0};
    char linea[1024];

    while (fgets(linea, sizeof(linea), entrada) != NULL) {
        for (int i = 0; linea[i] != '\0'; i++) {
            char c = tolower(linea[i]);
            if (c >= 'a' && c <= 'z') {
                conteo[c - 'a']++;
            }
        }
    }

    fclose(entrada);//cierro la archivo no me importa, ya que conte las letras en conteo[]

    char nombreSalida[80] = "resultado.";
    strcat(nombreSalida, nombreArchivo);

    FILE *salida = fopen(nombreSalida, "w");
    if (salida == NULL) {
        printf("No se pudo crear el archivo de salida.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++) {
        fprintf(salida, "La letra %c aparece %d veces.\n", 'a' + i, conteo[i]);
    }

    fclose(salida);
    printf("Conteo guardado en %s\n", nombreSalida);

    return 0;
}
