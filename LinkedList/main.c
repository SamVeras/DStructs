#include <stdio.h>
#include <stdlib.h>

// nó, node, elemento, sei la
typedef struct LinkedItem {
    int data;
    struct LinkedItem* next;
} LinkedItem;

// A lista sempre tem o endereço do primeiro item, ou NULL.
typedef struct LinkedList {
    LinkedItem* head;
    LinkedItem* tail;
} LinkedList;

// Inicializar item sem valor.
LinkedItem* linked_item_init() {
    LinkedItem* node = malloc(sizeof(LinkedItem));
    if (node == NULL)
        perror("Erro em malloc() linked_item_init()"), exit(1);
    node->next = NULL;
    return node;
}

// Cria uma lista vazia.
LinkedList* linked_list_init() {
    LinkedList* list = malloc(sizeof(LinkedList));
    if (list == NULL)
        perror("Erro em malloc() linked_list_init()"), exit(1);

    list->head = NULL;
    list->tail = NULL;
    return list;
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
}

// Printa todos os itens, endereços, etc..
void linked_list_show(LinkedList* list) {
    LinkedItem* current = list->head;
    int c = 0;

    while (current != NULL) {
        printf("%d [%p]\n", c++, current);
        printf("Valor:\t %d\n", current->data);
        printf("Próximo: %p\n\n", current->next);
        current = current->next;
    }
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

// Remove e retorna o último item da lista.
int linked_list_remove_last(LinkedList* list) {
    if (list->head == NULL)
        perror("Erro em linked_list_remove_last() lista vazia"), exit(1);

    LinkedItem* current = list->head;
    LinkedItem* last = list->tail;

    // Caso tenha apenas 1 item:
    if (list->head == list->tail) {
        int value = list->head->data;
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
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
    return value;
}

// Remove e retorna o primeiro item da lista.
int linked_list_remove_first(LinkedList* list) {
    if (list->head == NULL)
        perror("Erro em linked_list_remove_first() lista vazia"), exit(1);

    LinkedItem* first = list->head;
    int value = first->data;
    list->head = first->next;
    if (list->head == NULL)
        list->tail = NULL;
    free(first);
    return value;
}

// Retornar valor guardado no enésimo lugar da sequência.
int linked_list_item_at(LinkedList* list, unsigned int n) {
    if (list->head == NULL)
        perror("Erro em linked_list_item_at() de lista vazia"), exit(1);

    LinkedItem* current = list->head;
    unsigned int c = 0;
    int result = 0;

    while (c <= n) {  // Se n = 0 retorna o primeiro, etc.
        if (current == NULL)
            perror("Erro em linked_list_item_at() fora de índice"), exit(1);

        result = current->data;
        current = current->next;
        c++;
    }
    return result;
}

// Retorna o endereço do primeiro item com o valor da busca.
LinkedItem* linked_list_find(LinkedList* list, int query) {
    LinkedItem* current = list->head;
    while (current != NULL) {
        if (current->data == query)
            return current;
        current = current->next;
    }
    perror("Erro em linked_list_find() resultado não encontrado"), exit(1);
}

// Remove todos os itens da lista.
void linked_list_empty(LinkedList* list) {
    if (list->head == NULL)
        return;
    while (list->head != NULL) {
        linked_list_remove_first(list);
    }
}

// Retorna a quantidade de itens na lista.
int linked_list_size(LinkedList* list) {
    LinkedItem* current = list->head;
    if (current->next == NULL)
        return 0;
    unsigned int counter = 1;
    while (current->next != NULL) {
        counter++;
        current = current->next;
    }
    return counter;
}

// Retorna o endereço do menor item da lista.
LinkedItem* linked_list_min(LinkedList* list) {
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
LinkedItem* linked_list_max(LinkedList* list) {
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
int linked_list_count(LinkedList* list, int query) {
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
LinkedList* linked_list_copy(LinkedList* list) {
    LinkedList* new_list = linked_list_init();
    LinkedItem* current = list->head;

    while (current != NULL) {
        linked_list_append(new_list, current->data);
        current = current->next;
    }

    return new_list;
}

int main() {
    LinkedList* n = linked_list_init();

    linked_list_append(n, 75);
    linked_list_append(n, 97);
    linked_list_append(n, 145);
    linked_list_append(n, -94);
    linked_list_append(n, 97);
    linked_list_prepend(n, 166);
    linked_list_prepend(n, -25);
    linked_list_show(n);
    printf("Number of items in list:\t%d\n", linked_list_size(n));
    printf("Smallest item in list:\t\t%d\n", linked_list_min(n)->data);
    printf("Largest item in list:\t\t%d\n", linked_list_max(n)->data);
    printf("Number of times 97 appears:\t%d\n", linked_list_count(n, 97));
    printf("Value 97 first appears at:\t%p\n", linked_list_find(n, 97));
    printf("Item at position 4:\t\t%d\n", linked_list_item_at(n, 4));
    printf("Removed first item in list:\t%d\n", linked_list_remove_first(n));
    printf("Removed last item in list:\t%d\n\n", linked_list_remove_last(n));
    linked_list_show(n);
    LinkedList* m = linked_list_copy(n);
    printf("Created a copy of the list.\n");
    linked_list_empty(n);
    printf("Original list is now empty.\n");
    linked_list_show(n);
    linked_list_destroy(n);
    printf("Original list destroyed.\n");
    printf("New list has %d items.\n", linked_list_size(m));
    linked_list_destroy(m);
    printf("New list destroyed.\n");

    return 0;
};
