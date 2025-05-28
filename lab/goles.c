#include <stdio.h>
#include <string.h>

int main() {
    char linea[1024];
    char equipo1[100], equipo2[100];
    int gol1, gol2;

    int total_goles = 0;
    char equipo_max[100];
    int max_goles = -1;

    FILE *entrada = fopen("resultados.txt", "r");
    if (entrada == NULL) {
        printf("No se pudo abrir el archivo de entrada.\n");
        return 1;
    }


    while (fscanf(entrada, "%[^,],%d,%[^,],%d\n", equipo1, &gol1, equipo2, &gol2) == 4){
        total_goles += gol1 + gol2;
        if(max_goles < gol1){
            max_goles = gol1;
            strcpy(equipo_max, equipo1);
        }
        if(max_goles < gol2){
            max_goles = gol2;
            strcpy(equipo_max, equipo2);
        }

    }

    fclose(entrada);

    printf("Goles totales: %d\n", total_goles);
    printf("Equipo mas goleador: %s con %d goles\n", equipo_max, max_goles);

    return 0;
}
