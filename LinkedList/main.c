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
} LinkedList;

// Inicializar item sem valor.
LinkedItem* linked_item_init() {
    LinkedItem* node = malloc(sizeof(LinkedItem));
    if (node == NULL)
        perror("Erro em malloc() linked_item_init()"), exit(1);
    node->next = NULL;
    return node;
};

// Cria uma lista vazia.
LinkedList* linked_list_init() {
    LinkedList* list = malloc(sizeof(LinkedList));
    if (list == NULL)
        perror("Erro em malloc() linked_list_init()"), exit(1);

    list->head = NULL;
    return list;
};

// Retorna o endereço do último item da lista.
LinkedItem* linked_list_get_last(LinkedList* list) {
    if (list->head == NULL)
        return NULL;

    LinkedItem* current = list->head;

    while (current->next != NULL)
        current = current->next;

    return current;
};

// Poderíamos considerar modificar o struct LinkedList para adicionar um pointer
// para o fim da lista, atualizando sempre que inserimos um novo item. No caso
// de uma singly-linked list, isso só será útil para agilizar o processo de
// conseguir o endereço do fim da lista, mas para doubly-linked, talvez tenha
// melhores usos.

// Insere um valor em um node novo, no fim da lista.
void linked_list_append(LinkedList* list, int value) {
    LinkedItem* new_item = linked_item_init();
    new_item->data = value;

    if (list->head == NULL)  // Lista está vazia
        list->head = new_item;
    else
        linked_list_get_last(list)->next = new_item;
};

// Insere um valor em um node novo, no início da lista.
void linked_list_prepend(LinkedList* list, int value) {
    LinkedItem* new_item = linked_item_init();
    new_item->data = value;

    if (list->head == NULL)  // Lista está vazia
        list->head = new_item;
    else {
        new_item->next = list->head;
        list->head = new_item;
    }
}

// Printa todos os itens, endereços, etc..
void linked_list_show(LinkedList* list) {
    LinkedItem* current = list->head;
    int c = 0;
    printf("----------------\n");
    while (current != NULL) {
        printf("Item # %d\n", c++);
        printf("Endereço: %d / %p\n", current);
        printf("Valor:\t  %d\n", current->data);
        printf("Next:\t  %d\n\n", current->next);
        current = current->next;
    };
    printf("----------------\n");
};

// Destrói lista e todos os itens.
void linked_list_destroy(LinkedList* rip) {
    LinkedItem* current = rip->head;
    while (current != NULL) {
        LinkedItem* marked = current->next;
        free(current);
        current = marked;
    };
    free(rip);
};

// Remove e retorna o último item da lista.
int linked_list_remove_last(LinkedList* list) {
    if (list->head)
        perror("Erro em linked_list_remove_last() lista vazia"), exit(1);

    LinkedItem* current = list->head;
    LinkedItem* next = current->next;

    if (next == NULL) {  // Lista com apenas 1 item
        int value = current->data;
        list->head = NULL;
        free(current);
        return value;
    };

    while (next->next != NULL) {  // Basicamente, queremos ter acesso
        current = next;           // ao último e penúltimo itens
        next = current->next;
    };

    int value = next->data;
    current->next = NULL;
    free(next);
    return value;
};

// Remove e retorna o primeiro item da lista.
int linked_list_remove_first(LinkedList* list) {
    if (list->head == NULL)
        perror("Erro em linked_list_remove_first() lista vazia"), exit(1);

    LinkedItem* head = list->head;
    int value = head->data;
    list->head = head->next;
    free(head);
    return value;
};

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
    };
    return result;
};

// Retorna o endereço do primeiro item com o valor da busca.
LinkedItem* linked_list_find(LinkedList* list, int query) {
    LinkedItem* current = list->head;
    while (current != NULL) {
        if (current->data == query)
            return current;
        current = current->next;
    }
    perror("Erro em linked_list_find() resultado não encontrado"), exit(1);
};

// Remove todos os itens da lista.
void linked_list_empty(LinkedList* list) {
    if (list->head == NULL)
        return;
    while (list->head != NULL) {
        linked_list_remove_first(list);
    }
};

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
};

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
    };

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
        if (current->data < min->data)
            min = current;
    };

    return min;
}

int linked_list_count(LinkedList* list, int query) {
    LinkedItem* current = list->head;
    int count = 0;
    while (current != NULL) {
        if (current->data == query)
            count++;
        current = current->next;
    };
    return count;
}

int main() {
    LinkedList* n = linked_list_init();
    linked_list_insert(n, 31);
    linked_list_insert(n, 3457);
    linked_list_insert(n, 2334894);
    linked_list_show(n);
    printf("%d\n", linked_list_remove_first(n));
    linked_list_insert(n, 23487);
    linked_list_insert(n, 22);
    linked_list_insert(n, 31);
    linked_list_show(n);
    linked_list_empty(n);
    linked_list_insert(n, 1);
    linked_list_show(n);
    linked_list_destroy(n);
    return 0;
};
