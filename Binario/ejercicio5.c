#include <stdio.h>
#include <stdlib.h>

void mostrarPermisos(unsigned int numero);
int permisosalumno(char genero, int curso);

int main (){
    unsigned int numero;

    printf("Ingrese el permiso: ");
    scanf("%d", &numero);

    while(numero < 64){
        printf("Permisos incorrectos, ingrese uno válido");
        scanf("%d", &numero);
    }

    mostrarPermisos(numero);

    char genero;
    int cursoalumno;
    printf("\n");
    printf("Ingrese el genero y curso del alumno\n");
    printf("Genero: ");
    scanf(" %c", &genero);  
    printf("Curso: ");
    scanf("%d", &cursoalumno);

   unsigned int permiso = permisosalumno(genero, cursoalumno);

    mostrarPermisos(permiso);


    return 0;
}

void mostrarPermisos(int unsigned numero){
    if(numero & 128 && numero & 64){
        printf("Es para ambos generos ");
    }else if(numero & 128){
        printf("Es para hombres ");
    }else{
        printf("Es para mujeres ");
    }
    unsigned int mask = 1;
    int curso=1;
    while(curso <= 6){
        if(mask & numero){
            printf(", de %d curso", curso);
        }
        curso ++;
        mask = 1 << curso-1;
    }

}
int permisosalumno(char genero, int curso){
    unsigned int maskm,permisos,maskh;

    maskm = 64;
    maskh = 128;

    if(genero == 'm'){
        permisos = maskm;
    }else{
        permisos = maskh;
    }
    return permisos |= 1<<curso-1;
}