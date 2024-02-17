#include <stdio.h>
#include <stdlib.h>

// nó, node, elemento, sei la
typedef struct item {
    int dados;
    struct item* next;
} item;

// A lista sempre tem o endereço do primeiro item, ou NULL.
typedef struct lista {
    item* primeiro;
} lista;

// Inicializar item sem valor.
item* ItemInit() {
    item* node = malloc(sizeof(item));
    if (node == NULL) {
        perror("Erro criando node.");
        free(node);
        exit(1);
    }
    return node;
};

// Retorna o endereço do último item da lista.
item* GetLastItem(lista* list) {
    if (list->primeiro == NULL)
        return NULL;

    item* address = list->primeiro;

    while (address->next != NULL)
        address = address->next;

    return address;
};

// Cria uma lista vazia.
lista* ListaInit() {
    lista* lista = malloc(sizeof(lista));
    if (lista == NULL) {
        perror("Erro criando lista.");
        free(lista);
        exit(1);
    };
    lista->primeiro = NULL;
    return lista;
};

// Insere um valor em um node novo, no fim da lista.
void ListaInsert(lista* list, int valor) {
    item* novo = ItemInit();
    novo->next = NULL;
    novo->dados = valor;

    // Lista está vazia
    if (list->primeiro == NULL) {
        list->primeiro = novo;
    } else {
        item* ultimo = GetLastItem(list);
        ultimo->next = novo;
    };
};

// Printa todos os itens, endereços, etc..
void ListaPrint(lista* list) {
    item* address = list->primeiro;
    while (address != NULL) {
        printf("Valor: %d\n", address->dados);
        printf("Next:  %p\n\n", address->next);
        address = address->next;
    };
};

// Destrói lista e todos os itens.
void ListaDestruct(lista* rip) {
    item* atual = rip->primeiro;
    while (atual != NULL) {
        item* marked = atual->next;
        free(atual);
        atual = marked;
    };
    free(rip);
};

int main() {
    lista* n = ListaInit();
    ListaInsert(n, 25);
    ListaInsert(n, 15);
    ListaInsert(n, 35);
    ListaInsert(n, 2345);
    ListaPrint(n);
    ListaDestruct(n);
    return 0;
};
