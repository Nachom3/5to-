#include <stdio.h>

#define CANT_PALABRAS 4
#define MAX_LARGO_PALABRA 30

int main(){
    char palabras[CANT_PALABRAS][MAX_LARGO_PALABRA];

    for(int i = 0; i < CANT_PALABRAS; i++)
        scanf("%s", palabras[i]);

    for(int i = 0; i < CANT_PALABRAS; i++)
        printf("%s\n", palabras[i]);

    return 0;
}