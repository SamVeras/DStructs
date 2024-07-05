#include <stdio.h>
#include <stdlib.h>
#include "int_array.h"
#include "quicksort.h"

int main() {
  IntArray* a = int_array_init(4);

  int_array_push(a, 33);
  int_array_push(a, 3);
  int_array_push(a, 48);
  int_array_push(a, 80);

  int_array_status(a);

  int_array_push(a, 8);
  int_array_push(a, 39);
  int_array_push(a, 33);

  int_array_status(a);

  int_array_set(a, 2, 555);
  int_array_status(a);

  int_array_insert(a, 1, 999);
  int_array_insert(a, 8, 12341234);
  int_array_insert(a, 9, 33);

  int_array_status(a);

  int_array_trim(a);
  int_array_status(a);

  printf("%d ocorrências removidas\n", int_array_purge(a, 33));
  int_array_status(a);

  int_array_reverse(a);
  printf("a\n");
  int_array_status(a);

  IntArray* b = int_array_copy(a);
  printf("b\n");

  int_array_status(b);

  printf("%d\n", 11 / 2);

  int_array_destroy(a);
  int_array_destroy(b);

  return 0;
}