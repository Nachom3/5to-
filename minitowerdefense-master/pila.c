#include "pila.h"
#include "nivel.h"


Pila *pila_crear(){
	Pila *nueva = malloc(sizeof(Pila));
	nueva->ultimo = -1;
	return nueva;
}
int pila_es_vacia(Pila* pila){
	if (pila->ultimo == -1){
	return 1;
	}
	return 0;
}

Coordenada pila_tope(Pila* pila){
    if(pila->ultimo != -1){
        return pila->datos[pila->ultimo];
    }
    Coordenada invalida = { -1, -1 };
    return invalida;
}
void pila_apilar(Pila* pila, Coordenada num){
	if(pila->ultimo >= MAX_PILA-1){
		printf("error\n");
	}else{
		pila->datos[pila->ultimo+1] = num;
		pila->ultimo++;
	}
}
void pila_desapilar(Pila * pila){
	pila->ultimo -=1;
}

void pila_imprimir(Pila * pila){
	for(int i = 0; i<=pila->ultimo; i++){
		printf("%i\n", pila->datos[i].x);
		printf("%i\n", pila->datos[i].y);
	}
}

void pila_destruir(Pila * pila){
	free(pila);
}