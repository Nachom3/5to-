//Se tiene la lectura de un instrumento que informa de la medición de temperatura, humedad y presión atmosférica. La información viene codificada en un entero. Los 8 bits de menor peso contienen la lectura de temperatura en grados centígrados en complemento a 2, los siguientes 7 bits contienen la medición de humedad relativa (porcentaje), los siguientes 11 bits contienen la lectura de presión en Hectopascales.  

//a) Mostrar en pantalla las 3 lecturas en decimal por separado.

//b) Sabiendo que en la cima del monte Everest (mínimos posibles para una lectura) la temperatura extrema en invierno es de -70 oC y la presión atmosférica es de 382 Hectopascales, filtrar las mediciones que no sirven antes de hacer la conversión, es decir, descartar los binarios que contengan valores inferiores a los indicados y mostrar el cartel de ERROR de LECTURA

//c) El instrumento devuelve además en los 3 bits de más peso un 1 si alguno de los instrumentos está fallando (temperatura, humedad y presión de menor a mayor peso). En caso de falla mostrar el cartel FALLA en vez del valor leído

#include <stdio.h>
#include <stdlib.h>

void mostrarmediciones(unsigned int numero);

int errordelectura(unsigned int numero);

int main(){
    unsigned int numero;
    
    printf("Ingrese el numero entero con la informacion");
    scanf("%u", &numero);   
    
    

    mostrarmediciones(numero);



    return 0;
}

void mostrarmediciones(unsigned int numero){
    unsigned temperatura = 0xFF;
    unsigned humedad = 0x7F;
    unsigned presion = 0x7FF;
    printf("La temperatura es de: %u \n", numero & temperatura);
    
    numero = numero >> 8;

    printf("La humedad es de: %u \n", (numero & humedad));

    numero = numero >> 7;

    printf("La presion es de: %u \n ", numero & presion);

}


int errordelectura(unsigned int numero){
    

}