#include <stdio.h>
#include <stdlib.h>

void mostrarPermisos(unsigned int numero);

int main (){
    unsigned int numero;

    printf("Ingrese el permiso: ");
    scanf("%d", &numero);

    while(numero < 64){
        printf("Permisos incorrectos, ingrese uno válido");
        scanf("%d", &numero);
    }

    mostrarPermisos(numero);

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
    int mask,año=1;
    mask = 1;
    while(año <= 6){
        if(mask && numero){
            printf(", de %d ano", año);
        }
        año ++;
        mask = 0;
        mask = 1 << año;
    }

}