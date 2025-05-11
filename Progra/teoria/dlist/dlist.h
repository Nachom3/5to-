//Esto pregunta si está definida la librería, en caso de no
//estarlo la define
#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef void (*FuncionVisitante) (int dato);

typedef struct _DNodo {
  int dato;
  struct _DNodo *sig;
  struct _DNodo *ant;
} DNodo;

typedef struct {
  DNodo *primero;
  DNodo *ultimo;
} DList;

/**
 * Devuelve una lista vacía.
 */
DList* dlist_crear();

/**
 * Destruccion de la lista.
 */
void dlist_destruir_dnodo(DNodo *lista);

/**
 * Destruccion de la lista.
 */
void dlist_destruir(DList *lista);

/**
 * Determina si la lista es vacía.
 */
int dlist_vacia(DList *lista);

/**
 * Agrega un elemento al final de la lista.
 */
DList* dlist_agregar_final(DList* lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
DList* dlist_agregar_inicio(DList *lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void dlist_recorrer_hacia_adelante(DList *lista, FuncionVisitante visit);

/**
 * Recorrido de la lista en orden inverso, utilizando la funcion pasada.
 */
void dlist_recorrer_hacia_atras(DList *lista, FuncionVisitante visit);

#endif /* __SLIST_H__ */
