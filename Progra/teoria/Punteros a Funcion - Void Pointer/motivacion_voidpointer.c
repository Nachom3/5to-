#include <stdio.h>

int main() {
  void *ptr;

  int a = 10;
  ptr = &a;
  // Error: printf("%d\n", *ptr);
  // "dereferencing ‘void *’ pointer"
  // Cómo sabe printf cuántos bytes de memoria leer?

  // Debemos castear siempre que lo querramos usar
  printf("%d\n", *(int *)ptr);

  char b = 'x';
  ptr = &b;

  printf("%c\n", *(char *)ptr);

  return 0;
}