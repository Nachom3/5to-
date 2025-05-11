#include "dlist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int main() {

  DList *lista = dlist_crear();
  lista = dlist_agregar_inicio(lista, 4);
  lista = dlist_agregar_inicio(lista, 3);
  lista = dlist_agregar_final(lista, 5);

  dlist_recorrer_hacia_adelante(lista, imprimir_entero);
  puts("");

  lista = dlist_agregar_inicio(lista, 2);
  lista = dlist_agregar_inicio(lista, 1);
  lista = dlist_agregar_final(lista, 6);

  dlist_recorrer_hacia_atras(lista, imprimir_entero);
  puts("");

  dlist_destruir(lista);

  return 0;
}
