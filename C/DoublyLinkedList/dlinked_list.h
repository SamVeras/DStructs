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

size_t list_size(const LinkedList* list);

void list_show(const LinkedList* list);
void list_detailed(const LinkedList* list);

LinkedNode* list_get_node_at(const LinkedList* list, size_t index);

void list_push_back(LinkedList* list, int val);
void list_push_front(LinkedList* list, int val);

int list_pop_back(LinkedList* list);
int list_pop_front(LinkedList* list);

int list_get(const LinkedList* list, size_t index);
int list_set(LinkedList* list, size_t index, int val);

int list_remove_node(LinkedList* list, LinkedNode* node);
int list_remove(LinkedList* list, size_t index);