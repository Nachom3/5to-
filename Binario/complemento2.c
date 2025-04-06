// Complemento a 2
//escribir un programa en C que muestre en pantalla la representación binaria del complemento a dos del entero ingresado por el usuario.
#include <stdio.h>
#include <stdlib.h>

int main(){
    unsigned mask = 1 << 31;

    int num;
    printf("Ingrese un numero entero: ");
    scanf("%d", &num);

    while(mask > 0){
        if(num & mask){
            printf("1");
        }else{
            printf("0");
        }
        mask = mask >> 1;
    }
    return 0;
}