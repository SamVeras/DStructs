#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR_ALLOC_FAILURE -1
#define ERROR_INDEX_ERROR -2
#define ERROR_NONLETHAL -3

// Recebe um código (definido no header) e uma mensagem de erro
void error_manager(int error_code, char* message) {
  switch (error_code) {
    case ERROR_ALLOC_FAILURE:
      fprintf(stderr, "AllocFailure: %s\n", message);
      exit(1);

    case ERROR_INDEX_ERROR:
      fprintf(stderr, "IndexError: %s\n", message);
      exit(1);

    case ERROR_NONLETHAL:
      fprintf(stderr, "NonLethal: %s\n", message);

    default:
      fprintf(stderr, "UnknownError: %s (%d)\n", message, error_code);
      exit(1);
  }
}

// Inicializar item sem valor.
LinkedItem* linked_item_init() {
  LinkedItem* node = malloc(sizeof(LinkedItem));
  if (node == NULL)
    error_manager(ERROR_ALLOC_FAILURE, "item init failure");
  node->next = NULL;
  return node;
}

// Cria uma lista vazia.
LinkedList* linked_list_init() {
  LinkedList* list = malloc(sizeof(LinkedList));
  if (list == NULL)
    error_manager(ERROR_ALLOC_FAILURE, "list init failure");

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

// Destrói lista e todos os itens.
void linked_list_destroy(LinkedList* rip) {
  LinkedItem* current = rip->head;
  while (current != NULL) {
    LinkedItem* marked = current->next;
    free(current);
    current = marked;
  }
  free(rip);
}

// Printa todos os itens, endereços, etc..
void linked_list_show(const LinkedList* list) {
  LinkedItem* current = list->head;
  int c = 0;

  while (current != NULL) {
    printf("%d [%p]\n", c++, current);
    printf("Valor:\t %d\n", current->data);
    printf("Próximo: %p\n\n", current->next);
    current = current->next;
  }
}

// Insere um valor em um node novo, no fim da lista.
void linked_list_append(LinkedList* list, int value) {
  LinkedItem* new_item = linked_item_init();
  new_item->data = value;

  if (list->head == NULL)  // Lista está vazia
    list->head = new_item;
  else
    list->tail->next = new_item;

  list->tail = new_item;
  list->size++;
}

// Insere um valor em um node novo, no início da lista.
void linked_list_prepend(LinkedList* list, int value) {
  LinkedItem* new_item = linked_item_init();
  new_item->data = value;

  if (list->tail == NULL) {
    list->head = new_item;
    list->tail = new_item;
  } else {
    new_item->next = list->head;
    list->head = new_item;
  }

  list->size++;
}

// Remove e retorna o último item da lista.
int linked_list_remove_last(LinkedList* list) {
  if (list->head == NULL)
    error_manager(ERROR_INDEX_ERROR, "pop empty list");

  LinkedItem* current = list->head;
  LinkedItem* last = list->tail;

  // Caso tenha apenas 1 item:
  if (list->head == list->tail) {
    int value = list->head->data;
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return value;
  }

  // Para remover o último item precisamos do penúltimo.
  while (current->next != last) {
    current = current->next;
  };

  int value = last->data;
  free(last);
  current->next = NULL;
  list->tail = current;
  list->size--;
  return value;
}

// Remove e retorna o primeiro item da lista.
int linked_list_remove_first(LinkedList* list) {
  if (list->head == NULL)
    error_manager(ERROR_INDEX_ERROR, "remove first in empty list");

  LinkedItem* first = list->head;
  int value = first->data;
  list->head = first->next;
  if (list->head == NULL)
    list->tail = NULL;
  free(first);
  list->size--;
  return value;
}

// Retornar valor guardado no enésimo lugar da sequência.
int linked_list_get(const LinkedList* list, unsigned int n) {
  if (list->head == NULL)
    error_manager(ERROR_INDEX_ERROR, "get in empty list");

  LinkedItem* current = list->head;
  unsigned int c = 0;
  int result = 0;

  while (c <= n) {  // Se n = 0 retorna o primeiro, etc.
    if (current == NULL)
      error_manager(ERROR_INDEX_ERROR, "get out of range");

    result = current->data;
    current = current->next;
    c++;
  }
  return result;
}

// Retorna o endereço do primeiro item com o valor da busca.
LinkedItem* linked_list_find(const LinkedList* list, int query) {
  LinkedItem* current = list->head;
  while (current != NULL) {
    if (current->data == query)
      return current;
    current = current->next;
  }
  error_manager(ERROR_NONLETHAL, "query not found");
  return NULL;
}

// Remove todos os itens da lista.
void linked_list_empty(LinkedList* list) {
  if (list->head == NULL)
    return;
  while (list->head != NULL) {
    linked_list_remove_first(list);
  }
  list->size--;
}

// Retorna a quantidade de itens na lista.
int linked_list_size(const LinkedList* list) {
  return list->size;
}

// Retorna o endereço do menor item da lista.
LinkedItem* linked_list_min(const LinkedList* list) {
  LinkedItem* current = list->head;
  if (current == NULL)
    return NULL;

  LinkedItem* min = current;

  while (current->next != NULL) {
    current = current->next;
    if (current->data < min->data)
      min = current;
  }

  return min;
}

// Retorna o endereço do maior item da lista.
LinkedItem* linked_list_max(const LinkedList* list) {
  LinkedItem* current = list->head;
  if (current == NULL)
    return NULL;

  LinkedItem* min = current;

  while (current->next != NULL) {
    current = current->next;
    if (current->data > min->data)
      min = current;
  }

  return min;
}

// Retorna o número de ocorrências de um valor na lista.
int linked_list_count(const LinkedList* list, int query) {
  LinkedItem* current = list->head;
  unsigned int count = 0;
  while (current != NULL) {
    if (current->data == query)
      count++;
    current = current->next;
  }

  return count;
}

// Retorna ponteiro para uma cópia da lista.
LinkedList* linked_list_copy(const LinkedList* list) {
  LinkedList* new_list = linked_list_init();
  LinkedItem* current = list->head;

  while (current != NULL) {
    linked_list_append(new_list, current->data);
    current = current->next;
  }

  return new_list;
}