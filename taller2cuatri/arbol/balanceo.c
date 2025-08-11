#include "arbol.h"
#include "arbolbusqueda.h"

Nodo *bstInsertar(Nodo *nodo, void *dato, CompararDatos bstCompararDatos) {
  if (NULL == nodo) {
    nodo = malloc(sizeof(Nodo));
    nodo->dato = crear_dato(dato);
    nodo->subIzq = nodo->subDer = NULL;
    return nodo;
  }

  if (bstCompararDatos(dato, nodo->dato) < 0) {
    nodo->subIzq = bstInsertar(nodo->subIzq, dato, bstCompararDatos);
    nodo = bstBalancear(nodo, dato, bstCompararDatos);
  } else {
    nodo->subDer = bstInsertar(nodo->subDer, dato, bstCompararDatos);
    nodo = bstBalancear(nodo, dato, bstCompararDatos);
  }

  return nodo;
}

Nodo *bstBalancear(Nodo *nodo, void *dato, bstCompararDatos bstCompararDatos) {
  // COMPLETAR
}

Nodo *rotacionBstDerecha(Nodo * nodo) {
  assert(NULL != nodo->subDer);
  Nodo *nodoAuxiliar = NULL;

  nodoAuxiliar = nodo->subDer;
  nodo->subDer = nodoAuxiliar->subIzq;
  nodoAuxiliar->subIzq = nodo;

  return nodoAuxiliar;
}

Nodo *rotacionBstIzquierda(Nodo * nodo) {
  assert(NULL != nodo->subIzq);
  Nodo *nodoAuxiliar = NULL;

  nodoAuxiliar = nodo->subIzq;
  nodo->subIzq = nodoAuxiliar->subDer;
  nodoAuxiliar->subDer = nodo;

  return nodoAuxiliar;
}

Nodo *rotacionBstDerechaDoble(Nodo * nodo) {

  nodo->subDer = rotacionBstIzquierda(nodo->subDer);
  return rotacionBstDerecha(nodo);
}

Nodo *rotacionBstIzquierdaDoble(Nodo * nodo) {

  nodo->subIzq = rotacionBstDerecha(nodo->subIzq);
  return rotacionBstIzquierda(nodo);
}