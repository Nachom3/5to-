#ifndef __PILA_H__
#define __PILA_H__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nivel.h"
#define MAX_PILA 100

typedef struct _Pila{
	Coordenada datos[MAX_PILA];
	int ultimo;
}Pila;

Pila *pila_crear();
int pila_es_vacia(Pila* pila);
Coordenada pila_tope(Pila* pila);
void pila_apilar(Pila* pila, Coordenada num);
void pila_desapilar(Pila * pila);
void pila_imprimir(Pila * pila);
void pila_destruir(Pila* pila);
void copiar_coordenada(Coordenada *primera, Coordenada *segunda);
#endif
 
