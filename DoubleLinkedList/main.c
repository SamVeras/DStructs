#include <stdio.h>
#include <stdlib.h>

typedef struct DLinkedItem {
    struct DLinkedItem* prev;
    struct DLinkedItem* next;
    int data;
} DLinkedItem;

typedef struct DLinkedList {
    DLinkedItem* head;
    DLinkedItem* tail;
} DLinkedList;

DLinkedItem* dlinked_item_init() {
    DLinkedItem* node = malloc(sizeof(DLinkedItem));
    if (node == NULL)
        perror("Erro em malloc() dlinked_item_init()"), exit(1);
    return node;
}

DLinkedList* dlinked_list_init() {
    DLinkedList* list = malloc(sizeof(DLinkedList));
    if (list == NULL)
        perror("Erro em malloc() dlinked_list_init()"), exit(1);
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void dlinked_list_insert(DLinkedList* list, int value) {
    DLinkedItem* new_item = dlinked_item_init();
    new_item->data = value;
    new_item->next = NULL;
    new_item->prev = list->tail;  // Se a lista for vazia, isso será NULL

    if (list->tail == NULL)       // caso vazia
        list->head = list->tail = new_item;
    else {                        // 1 ou mais itens
        list->tail->next = new_item;
        list->tail = new_item;
    }
}

void dlinked_list_show(DLinkedList* list) {
    DLinkedItem* current = list->head;
    int c = 0;
    while (current != NULL) {
        printf("Item %d\t%p\n", c++, current);
        printf("Valor:\t%d\n", current->data);
        printf("Prev:\t%p\n", current->prev);
        printf("Next:\t%p\n\n", current->next);
        current = current->next;
    }
}

int main() {
    return 0;
}