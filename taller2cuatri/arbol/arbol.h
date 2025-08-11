#ifndef __ARBOL_BINARIO__
#define __ARBOL_BINARIO__

typedef enum {PREORDEN, INORDER, POSORDER} Orden;

typedef struct _ABNodo {
  int dato;
  struct _ABNodo *izq, *der;
} ABNodo;

typedef struct _Nodo {
  int *dato;
  struct _Nodo *subIzq, *subDer;
} Nodo;
typedef ABNodo* ArbolBinario;

/**
 * crear_arbol_binario: crea un árbol vacío y lo retorna.
 */
ArbolBinario crear_arbol_binario();

/**
 * combinar_arbol_binario: construye un arbol a partir de sus subárboles y la raíz
 */
ArbolBinario combinar_arbol_binario(ArbolBinario a, ArbolBinario b, int dato);

/**
 * recorrer_arbol_binario: recorre el árbol en profundidad según el orden que se le pasa
 */
void recorrer_arbol_binario(ArbolBinario a, Orden orden); 

/**
 * buscar_arbol_binario: devuelve un puntero al nodo que contiene el dato. En caso que no exista retorna NULL.
 */
ABNodo *buscar_arbol_binario(ArbolBinario a, int dato);

/**
 * eliminar_arbol_binario: retorna un nuevo árbol sin el elemento que se desea eliminar.
 */
ArbolBinario eliminar_arbol_binario(ArbolBinario a, int dato);

/**
 * es_vacio_arbol_binario: retorna 1 si el árbol está vacío
 */
int es_vacio_arbol_binario(ArbolBinario a);

/**
 * altura_arbol_binario: retorna la altura del árbol
 */
int altura_arbol_binario(ArbolBinario a);

/**
 * destruir_arbol_binario: libera toda la memoria pedida para el árbol
 */
int destruir_arbol_binario(ArbolBinario a);

#endif