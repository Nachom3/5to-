//Una función que devuelva el numero positivo mas grande que se pueda almacenar en long long, que tiene un tamaño de 8 bytes


#include <stdio.h>
#include <stdlib.h>
long long maxlong();

int potImparesDos(unsigned int numero);

int main() {
    long long numero;

    numero = maxlong(numero);
    printf("%lld\n", numero);

    unsigned int numero2;
    printf("Ingrese un numero a analizar\n");
    scanf("%d", &numero2);
    int contador = potImparesDos(numero2);

    printf("El numero %d tiene %d impares potencia de dos bits en 1", numero2, contador);

    return 0;
}

long long maxlong(){
    long long mask = ~(1LL  << 63);
    return mask;
}

int potImparesDos(unsigned int numero){
    int unsigned mask = 1;
    int contador=0;
    for (int i = 0; i<32; i++)
    {
        if((mask & numero) && (i % 2 == 0) && (i!=0)){
            contador ++;
        }
        mask = mask << 1;
    }
    
    return contador;
}