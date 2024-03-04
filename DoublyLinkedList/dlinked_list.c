#include "dlinked_list.h"
#include <stdio.h>

LinkedNode* node_init() {
  LinkedNode* node = malloc(sizeof(LinkedNode));

  if (node == NULL)
    error_handler(ERROR_ALLOC_FAIL, "node_init");

  node->next = NULL;
  node->prev = NULL;
  return node;
}

LinkedList* list_init() {
  LinkedList* list = malloc(sizeof(LinkedList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void list_destroy(LinkedList* list) {
  LinkedNode* current = list->head;
  while (current != NULL) {
    LinkedNode* next = current->next;
    free(current);
    current = next;
  }
  free(list);
}

void list_show(LinkedList* list) {
  LinkedNode* current = list->head;

  printf("[");
  while (current->next != NULL) {
    printf("%d, ", current->data);
    current = current->next;
  }
  printf("%d", current->data);
  printf("]\n");
}

void list_detailed(LinkedList* list) {
  printf("List head: @%p\n", list->head);
  printf("List tail: @%p\n", list->tail);
  printf("List size: %zu\n", list->size);

  LinkedNode* current = list->head;
  while (current != NULL) {
    printf("@%p <- %d @%p -> @%p\n", current->prev, current->data, current,
           current->next);
    current = current->next;
  }
}

void list_push_back(LinkedList* list, int val) {
  LinkedNode* new_item = node_init();
  new_item->data = val;

  if (list->head == NULL)  // Lista vazia
    list->head = new_item;
  else {
    new_item->prev = list->tail;
    list->tail->next = new_item;
  }

  list->tail = new_item;
  list->size++;
}

void list_push_front(LinkedList* list, int val) {
  LinkedNode* new_item = node_init();
  new_item->data = val;

  if (list->tail == NULL)  // List vazia
    list->tail = new_item;
  else {
    new_item->next = list->head;
    list->head->prev = new_item;
  }

  list->head = new_item;
  list->size++;
}