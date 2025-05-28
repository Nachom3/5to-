#include <stdio.h>

int main(){
    FILE* archivo = fopen("leeme.txt", "r");

    if (archivo == NULL){
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    char nombre[25];
    char profesion[30]; 
    int edad;

    for (; fscanf(archivo, "%[^,],%d,%[^\n]\n", nombre, &edad, profesion) == 3;){
        printf("Nombre: %s, Edad: %d, Profesion: %s\n", nombre, edad, profesion);
    }

    fclose(archivo);
    return 0;
}