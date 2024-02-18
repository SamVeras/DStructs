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
        perror("Erro em malloc() ItemInit()");
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
        perror("Erro em malloc() ListaInit()");
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

    if (lista->primeiro == NULL)  // Lista está vazia
        lista->primeiro = novo;
    else
        GetLastItem(lista)->next = novo;
};

// Printa todos os itens, endereços, etc..
void ListaPrint(lista* lista) {
    item* atual = lista->primeiro;
    int c = 0;
    printf("----------------\n");
    while (atual != NULL) {
        printf("Item # %d\n", c++);
        printf("Endereço: %p\n", atual);
        printf("Valor:\t  %d\n", atual->dados);
        printf("Next:\t  %p\n\n", atual->next);
        atual = atual->next;
    };
    printf("----------------\n");
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
int ListaPop(lista* lista) {
    if (lista->primeiro) {
        perror("Erro em ListaPop() lista vazia");
        exit(1);
    };

    item* atual = lista->primeiro;
    item* proximo = atual->next;

    if (proximo == NULL) {  // Lista com apenas 1 item
        int value = atual->dados;
        lista->primeiro = NULL;
        free(atual);
        return value;
    };

    while (proximo->next != NULL) {  // Basicamente, queremos ter acesso
        atual = proximo;             // ao último e penúltimo itens
        proximo = atual->next;
    };

    int value = proximo->dados;
    atual->next = NULL;
    free(proximo);
    return value;
};

// Retornar valor guardado no enésimo lugar da sequência.
int ListaGet(lista* lista, unsigned int n) {
    item* atual = lista->primeiro;

    if (atual == NULL) {
        perror("Erro em ListGet() de lista vazia");
        exit(1);
    }

    unsigned int c = 0;
    int result = 0;

    // Se n = 0 retorna o primeiro, etc.
    while (c <= n) {
        if (atual == NULL) {
            perror("Erro em ListaGet() fora de índice");
            exit(1);
        };
        result = atual->dados;
        atual = atual->next;
        c++;
    };
    return result;
};

// Retorna o endereço do primeiro item com o valor da busca.
item* ListaBusca(lista* lista, int query) {
    item* atual = lista->primeiro;
    while (atual != NULL) {
        if (atual->dados == query)
            return atual;
        atual = atual->next;
    };
    perror("Erro em ListaBusca() resultado não encontrado");
    exit(1);
};

int main() {
    lista* n = ListaInit();
    ListaInsert(n, 31);
    ListaInsert(n, 41);
    ListaInsert(n, 59);
    ListaInsert(n, 26);
    ListaPrint(n);
    int x = ListaGet(n, 2);
    printf("%d\n", x);
    ListaDestruct(n);
    return 0;
};
