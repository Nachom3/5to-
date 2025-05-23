#include "slist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int main() {

  SList lista = slist_crear();

  lista = slist_agregar_final_R(lista, 4);
  lista = slist_agregar_final_R(lista, 3);
  lista = slist_agregar_final_R(lista, 2);
  lista = slist_agregar_final_R(lista, 1);

  slist_recorrer(lista, imprimir_entero);
  puts("");

  slist_destruir_R(lista);

  return 0;
}
