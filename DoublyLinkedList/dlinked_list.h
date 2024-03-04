#pragma once
#include <stdlib.h>
#include "error_handler.h"

typedef struct LinkedNode {
  int data;
  struct LinkedNode* next;
  struct LinkedNode* prev;
} LinkedNode;

typedef struct LinkedList {
  LinkedNode* head;
  LinkedNode* tail;
  size_t size;
} LinkedList;

LinkedNode* node_init();
LinkedList* list_init();
void list_destroy(LinkedList* list);

void list_show(LinkedList* list);
void list_detailed(LinkedList* list);

void list_push_back(LinkedList* list, int val);
void list_push_front(LinkedList* list, int val);

void list_pop_back(LinkedList* list);
void list_pop_front(LinkedList* list);

int list_get(LinkedList* list, size_t index);
void list_set(LinkedList* list, size_t index, int val);

size_t list_size(LinkedList* list);

// adicionar função para remover item de lista passando item como parametro