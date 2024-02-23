#pragma once

// nó, node, elemento, sei la
typedef struct LinkedItem {
    int data;
    struct LinkedItem* next;
} LinkedItem;

// A lista sempre tem o endereço do primeiro item, ou NULL.
typedef struct LinkedList {
    LinkedItem* head;
    LinkedItem* tail;
    unsigned int size;
} LinkedList;

// LinkedItem* linked_item_init();
LinkedList* linked_list_init();
void linked_list_show(LinkedList* list);
void linked_list_append(LinkedList* list, int value);
void linked_list_prepend(LinkedList* list, int value);
void linked_list_destroy(LinkedList* rip);
int linked_list_remove_last(LinkedList* list);
int linked_list_remove_first(LinkedList* list);
int linked_list_item_at(LinkedList* list, unsigned int n);
LinkedItem* linked_list_find(LinkedList* list, int query);
void linked_list_empty(LinkedList* list);
int linked_list_size(LinkedList* list);
LinkedItem* linked_list_min(LinkedList* list);
LinkedItem* linked_list_max(LinkedList* list);
int linked_list_count(LinkedList* list, int query);
LinkedList* linked_list_copy(LinkedList* list);