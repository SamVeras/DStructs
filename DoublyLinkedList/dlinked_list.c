#include "dlinked_list.h"
#include <stdio.h>

// Cria um novo node
LinkedNode* node_init() {
  LinkedNode* node = malloc(sizeof(LinkedNode));

  if (node == NULL)
    error_handler(ERROR_ALLOC_FAIL, "node_init");

  node->next = NULL;
  node->prev = NULL;
  return node;
}

// Inicializa a lista
LinkedList* list_init() {
  LinkedList* list = malloc(sizeof(LinkedList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

// Destroi a lista e seus nodes
void list_destroy(LinkedList* list) {
  LinkedNode* current = list->head;
  while (current != NULL) {
    LinkedNode* next = current->next;
    free(current);
    current = next;
  }
  free(list);
}

// Retorna o tamanho da lista
size_t list_size(const LinkedList* list) {
  return list->size;
}

// Imprime apenas os valores da lista
void list_show(const LinkedList* list) {
  LinkedNode* current = list->head;

  printf("[");
  while (current->next != NULL) {
    printf("%d, ", current->data);
    current = current->next;
  }
  printf("%d", current->data);
  printf("]\n");
}

// Imprime informações detalhadas
void list_detailed(const LinkedList* list) {
  printf("List: %p\n", list);
  printf("Head: %p\n", list->head);
  printf("Tail: %p\n", list->tail);
  printf("Size: %zu\n\n", list->size);

  LinkedNode* current = list->head;
  size_t c = 0;

  while (current != NULL) {
    printf("===[%p]===\n", current);
    printf("Item:   %zu\n", c++);
    printf("Valor:  %d\n", current->data);
    printf("Prev:   %p\n", current->prev);
    printf("Next:   %p\n\n", current->next);
    current = current->next;
  }
}

// Retorna um ponteiro para o node correspondente ao index especificado
LinkedNode* list_get_node_at(const LinkedList* list, size_t index) {
  if (list->head == NULL)
    error_handler(ERROR_INDEX_ERROR, "get_node in empty list");

  if (index >= list->size)
    error_handler(ERROR_INDEX_ERROR, "get_node out of list bounds");

  LinkedNode* current = list->size / 2 > index ? list->head : list->tail;

  if (index < list->size / 2)
    for (size_t i = 0; i < index; i++)
      current = current->next;
  else
    for (size_t i = list->size - 1; i > index; i--)
      current = current->prev;

  return current;
}

// Insere no fim da lista
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

// Insere no início da lista
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

// Retorna e remove o último item
int list_pop_back(LinkedList* list) {
  if (list->head == NULL)
    error_handler(ERROR_INDEX_ERROR, "pop empty list");

  int t = list->tail->data;

  if (list->tail == list->head) {
    free(list->tail);
    list->tail = NULL;
    list->head = NULL;
  } else {
    list->tail = list->tail->prev;
    free(list->tail->next);
    list->tail->next = NULL;
  }

  list->size--;
  return t;
}

// Retorna e remove o primeiro item
int list_pop_front(LinkedList* list) {
  if (list->tail == NULL)
    error_handler(ERROR_INDEX_ERROR, "pop empty list");

  int t = list->head->data;

  if (list->tail == list->head) {
    free(list->head);
    list->tail = NULL;
    list->head = NULL;
  } else {
    list->head = list->head->next;
    free(list->head->prev);
    list->head->prev = NULL;
  }

  list->size--;
  return t;
}

// Retorna o valor do item na posição especificada
int list_get(const LinkedList* list, size_t index) {
  if (list->head == NULL)
    error_handler(ERROR_INDEX_ERROR, "list_get in empty list");

  if (index >= list->size)
    error_handler(ERROR_INDEX_ERROR, "list_get out of list bounds");

  LinkedNode* current = list_get_node_at(list, index);

  return current->data;
}

// Muda o valor do item e retorna o valor antigo
int list_set(LinkedList* list, size_t index, int val) {
  if (list->head == NULL)
    error_handler(ERROR_INDEX_ERROR, "list_set in empty list");

  if (index >= list->size)
    error_handler(ERROR_INDEX_ERROR, "list_set out of list bounds");

  LinkedNode* current = list_get_node_at(list, index);
  int temp = current->data;
  current->data = val;

  return temp;
}

// Remove um node da lista e libera o espaco de memória
int list_remove_node(LinkedList* list, LinkedNode* node) {
  if (list->head == NULL)
    error_handler(ERROR_INDEX_ERROR, "list_remove_node in empty list");

  int temp = node->data;

  node->prev->next = node->next;
  node->next->prev = node->prev;
  free(node);

  list->size--;

  return temp;
}

// Remove o item na posição especificada
int list_remove(LinkedList* list, size_t index) {
  if (list->head == NULL)
    error_handler(ERROR_INDEX_ERROR, "list_remove in empty list");

  if (index >= list->size)
    error_handler(ERROR_INDEX_ERROR, "list_remove out of list bounds");

  LinkedNode* current = list_get_node_at(list, index);
  return list_remove_node(list, current);
}