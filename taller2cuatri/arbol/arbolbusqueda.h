#include "arbol.h"
#ifndef __ARBOL_BINARIO_DE_BUSQUEDA__
#define __ARBOL_BINARIO_DE_BUSQUEDA__

typedef struct _ABBNodo {
  int dato;
  struct _ABNodo *izq, *der;
} ABBNodo;

typedef ABBNodo* ArbolBinarioBusqueda;

/**
 * crear_arbol_binario_busqueda: crea un árbol vacío y lo retorna.
 */
ArbolBinarioBusqueda crear_arbol_binario_busqueda();

/**
 * agregar_arbol_binario_busqueda: agrega un nuevo dato al árbol binario manteniendo la invariante ABB
 */
ArbolBinarioBusqueda agregar_arbol_binario_busqueda(ArbolBinarioBusqueda a, int dato);

/**
 * recorrer_arbol_binario_busqueda: recorre el árbol en preorden
 */
void recorrer_arbol_binario_busqueda(ArbolBinarioBusqueda a); 

/**
 * buscar_arbol_binario_busqueda: devuelve un puntero al nodo que contiene el dato. En caso que no exista retorna NULL.
 */
ABNodo *buscar_arbol_binario_busqueda(ArbolBinarioBusqueda a, int dato);

/**
 * eliminar_arbol_binario_busqueda: retorna un nuevo árbol sin el elemento que se desea eliminar.
 */
ArbolBinarioBusqueda eliminar_arbol_binario_busqueda(ArbolBinarioBusqueda a, int dato);

/**
 * es_vacio_arbol_binario_busqueda: retorna 1 si el árbol está vacío
 */
int es_vacio_arbol_binario_busqueda(ArbolBinarioBusqueda a);

/**
 * altura_arbol_binario_busqueda: retorna la altura del árbol
 */
int altura_arbol_binario_busqueda(ArbolBinarioBusqueda a);

/**
 * destruir_arbol_binario_busqueda: libera toda la memoria pedida para el árbol
 */
int destruir_arbol_binario_busqueda(ArbolBinario a);

#endif