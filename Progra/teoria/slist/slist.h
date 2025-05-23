//Esto pregunta si está definida la librería, en caso de no
//estarlo la define
#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

//Esto está definiendo un nuevo tipo de dato, así como con typedef
//y struct ponemos un alias a una estructura como hemos visto en clase.
//Ahora, lo que estamos haciendo es llamar con el identificador 
//FuncionVisitante a cualquier función que tome un entero y tenga tipo
//de retorno void
typedef void (*FuncionVisitante) (int dato);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

//Cuando usamos SList estamos representando un SNodo*
//es decir, usar SList sería lo mismo que usar: struct _SNodo *
typedef SNodo* SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Destruccion de la lista - versión recursiva
 */
void slist_destruir_R(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al final de la lista.
 */
void slist_agregar_final_alt(SNodo** lista, int dato);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final_R(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
void slist_agregar_inicio_alt(SNodo** lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

#endif /* __SLIST_H__ */
