//En una sala de máquinas se encuentran instaladas 8 bombas de agua que pueden funcionar en  16 caudales distintos de bombeo. El nivel 0 corresponde a cerrado y el 15 al máximo caudal. El tablero de comando automatizado recibe un entero en donde se codifica el valor para cada bomba.
//a) Escribir una función que dado el entero indique en pantalla a que nivel se encuentra funcionando cada bomba
//b) Escribir otra función que permita cambiar la configuración de una determinada bomba o de todas las bombas al mismo valor  

#include <stdio.h>
#include <stdlib.h>

unsigned int cambiar(unsigned int numero);

void checkLevels(unsigned int numero);

int main (){

    unsigned int numero;
    printf("Ingrese el entero que corresponde: \n");
    scanf("%u", &numero);
    unsigned int mask = 15;
    checkLevels(numero);
    numero = cambiar(numero);
    printf("-----------------------------------------------\n");
    checkLevels(numero);
    return 0;
}

unsigned int cambiar(unsigned int numero){
    int eleccion; 
    int valor;
    printf("Elija un numero entre 0 y 7, siendo este el numero de bomba, o ponga 100 si desea cambiar todas ");
    scanf("%d", &eleccion);

    printf("Elija el valor a cambiar la/las bombas(entre 0 y 15)");
    scanf("%d", &valor);

    if (eleccion == 100){
        numero = 0;
        for (int i = 0; i < 8; i++)
        {
            numero += valor << (i*4);
            printf("Bomba numero %d cambiada a %d valor \n", i,valor);
        }
    }else if(eleccion >= 0 && eleccion <= 7){
        unsigned int mask = ~(15 << eleccion*4);
        numero = numero & mask; //cambio a 0
        unsigned int valormask = valor << eleccion*4;
        numero = numero | valormask; // cambio al valor
        printf("Bomba numero %d cambiada a %d\n", eleccion, valor);
    }
    
    return numero;
}

void checkLevels(unsigned int numero){
    unsigned int mask = 15;
    for (int i = 0; i < 8; i++)
    {
        printf("La bomba numero %d se encuentra en el nivel: %u \n", i, mask & numero);
        numero = numero >> 4;
    }
    
}