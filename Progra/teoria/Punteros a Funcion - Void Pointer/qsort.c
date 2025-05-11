#include <stdio.h>
#include <stdlib.h>

int comparar_enteros(const void *p, const void *q) {
  int x = *(int*)p;
  int y = *(int*)q;

  if (x < y)
    return -1;

  if (x > y)
    return 1;

  return 0;
}

int comparar_enteros_alt(const void *p, const void *q) {
  int x = *(int*)p;
  int y = *(int*)q;

  return (x > y) - (x < y);
}

int main() {
  int array[] = {88, 56, 100, 2, 25};
  int largo_array = 5;

  printf("Array sin ordenar\n");
  for (int i = 0; i < largo_array; i++)
    printf("%d ", array[i]);

  qsort(&array, largo_array, sizeof(int), comparar_enteros);

  printf("\nArray ordenado\n");
  for (int i = 0; i < largo_array; i++)
    printf("%d ", array[i]);

  puts("");
  return 0;
}
