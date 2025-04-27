//Una función que devuelva el numero positivo mas grande que se pueda almacenar en long long, que tiene un tamaño de 8 bytes


#include <stdio.h>
#include <stdlib.h>

long long devolverlong();

int potenciasimpares(unsigned int numero);

int main(){
    long long numero = devolverlong();
    
    printf("%lld\n", numero);

    unsigned int numero2;
    
    printf("Ingrese el entero: \n");
    scanf("%d", &numero2);

    int cont = potenciasimpares(numero2);
    
    printf("Tiene %d", cont);
    
    return 0;
}

long long devolverlong(){
    return ~(1LL<<63);
}

int potenciasimpares(unsigned int numero){
    unsigned int mask = 1;
    int cont = 0;
    while(mask >0){
        if(numero & mask){
            cont ++;
        }
        mask = mask << 2;
    }

    return cont;
}