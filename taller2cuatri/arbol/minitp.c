#include <stdlib.h>

typedef struct _Nodo {
  int *dato;
  struct _Nodo *subIzq, *subDer;
} Nodo;


//a->campo == (*a).campo

Nodo *buscar_abb(Nodo *nodo, int dato) {
    if (nodo == NULL) {
    return NULL;
    }
    if (nodo->dato == dato) 
        return nodo;
    
    if (nodo->dato < dato) {
        return buscar_ab(nodo->subDer, dato);
    } else {
        return buscar_ab(nodo->subIzq, dato);
    }
}

    
Nodo *buscar_ab(Nodo *nodo, int dato) {
    if (nodo == NULL) {
        return NULL;
    }   
    if (nodo->dato == dato) {
        return nodo;
    }
    Nodo *encontrado = buscar_ab(nodo->subDer, dato);
    if (encontrado != NULL) {
        return encontrado;
    }
    return buscar_ab(nodo->subIzq, dato);
}
Nodo *buscar_avl(Nodo *nodo, int dato) {
  if (nodo == NULL) {
    return NULL;
    }
    if (nodo->dato == dato) 
        return nodo;
    
    if (nodo->dato < dato) {
        return buscar_avl(nodo->subDer, dato);
    } else {
        return buscar_avl(nodo->subIzq, dato);
    }
}

//Arbol binario. En el peor de los casos la busqueda es N, siendo N numero de nodos del arbol. El dato tendria que estar en el subarbol izquierdo lo mas a la izquierda posible. (ojala se haya entedido la explicacion)

//Arbol binario de busqueda. En el peor de los casos la busqueda es N, ya que si el dato a buscar es el mas mayor o el mas menor, y solo hay nodos en el subarbol izquierdo(caso del mas menor) o en el subarbol derecho(caso del mas mayor

//Arbol AVL. En el peor de los casos el costo es Logaritmo en base dos de N. Ya que la altura en los arboles AVL es siempre "minima" ya que al insertar los nodos lo hacemos de forma balanceada, de tal manera que la diferencia entre una raiz y la altura de su subárbol izquierdo y la altura de su subárbol derecho debe ser como máximo 1.