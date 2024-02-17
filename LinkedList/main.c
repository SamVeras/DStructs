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
        exit(1);
    }
    return node;
};

// Retorna o endereço do último item da lista.
item* GetLastItem(lista* lista) {
    if (lista->primeiro == NULL)
        return NULL;

    item* atual = lista->primeiro;

    while (atual->next != NULL)
        atual = atual->next;

    return atual;
};

// Cria uma lista vazia.
lista* ListaInit() {
    lista* lista = malloc(sizeof(lista));
    if (lista == NULL) {
        perror("Erro criando lista.");
        exit(1);
    };
    lista->primeiro = NULL;
    return lista;
};

// Insere um valor em um node novo, no fim da lista.
void ListaInsert(lista* lista, int valor) {
    item* novo = ItemInit();
    novo->next = NULL;
    novo->dados = valor;

    // Lista está vazia
    if (lista->primeiro == NULL) {
        lista->primeiro = novo;
    } else {
        item* ultimo = GetLastItem(lista);
        ultimo->next = novo;
    };
};

// Printa todos os itens, endereços, etc..
void ListaPrint(lista* lista) {
    item* atual = lista->primeiro;
    while (atual != NULL) {
        printf("Valor: %d\n", atual->dados);
        printf("Next:  %p\n\n", atual->next);
        atual = atual->next;
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

// Retorna e remove o último item da lista.
int ListaPop(lista* lista){

};

int main() {
    lista* n = ListaInit();
    ListaInsert(n, 31);
    ListaInsert(n, 41);
    ListaInsert(n, 59);
    ListaInsert(n, 26);
    ListaPrint(n);
    ListaDestruct(n);
    return 0;
};
