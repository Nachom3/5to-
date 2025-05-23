#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PILA 5

typedef struct _Pila{
	int datos[MAX_PILA];
	int ultimo;
}Pila;

Pila *pila_crear();
int pila_es_vacia(Pila* pila);
int pila_tope(Pila* pila);
void pila_apilar(Pila* pila, int num);
void pila_desapilar(Pila * pila);
void pila_imprimir(Pila * pila);
void pila_destruir(Pila* pila);

#endif
 