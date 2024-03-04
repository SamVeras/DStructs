#include "dlinked_list.h"

int main() {
  LinkedList* a = list_init();
  list_push_back(a, 23);
  list_push_back(a, 49);
  list_push_back(a, 75);
  list_push_back(a, 11);

  list_detailed(a);

  return 0;
}