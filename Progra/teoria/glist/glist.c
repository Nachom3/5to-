#include "glist.h"
#include <assert.h>
#include <stdlib.h>

GList glist_crear() { return NULL; }

void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

int glist_vacia(GList list) { return (list == NULL); }

GList glist_agregar_inicio(GList list, void *data) {
  GNode *newNode = malloc(sizeof(GNode));
  newNode->next = list;
  newNode->data = data;
  return newNode;
}

void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}
