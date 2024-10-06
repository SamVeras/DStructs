#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

BT_Node* BT_node_init(bool leaf) {
    BT_Node* node = (BT_Node*)malloc(sizeof(BT_Node));
    node->count   = 0;
    node->is_leaf = leaf;          // E
    for (int i = 0; i < BT_ORDER; i++)
        node->children[i] = NULL;  // inicializar os filhos como nulos
    return node;
}

BT_Tree* BT_tree_init() {
    BT_Tree* tree = (BT_Tree*)malloc(sizeof(BT_Tree));
    tree->root    = NULL;  // começar com árvore vazia
    return tree;
}

void BT_tree_insert(BT_Tree* tree, int val) {
    BT_Node* r = tree->root;

    if (r == NULL) {  // a árvore é vazia
        r = tree->root = BT_node_init(true);
        r->key[0]      = val;
        r->count       = 1;
        return;
    }

    if (r->count == BT_MAX_CHAVES) {           // raiz cheia, precisamos dividir
        BT_Node* s     = BT_node_init(false);  // será a nova raiz
        s->children[0] = r;  // raiz antiga será filha da nova raiz

        BT_split(r, s);
        BT_tree_insert_nonfull(s, val);
    } else {
        BT_tree_insert_nonfull(r, val);
    }
}

void BT_split(BT_Node* x, BT_Node* y) {
    BT_Node* z = BT_node_init(x->is_leaf);

    // ponto de divisão, indice a ser "promovido"
    int mid = BT_MIN_FILHOS - 1;

    // botar mid na nova raiz e aumentar count APÓS
    y->key[y->count++] = x->key[mid];

    for (int i = 0; i < mid; i++)
        z->children[i] = x->children[i + mid + 1];  // copiar os filhos

    z->count = mid;                     // arrumar a contagem de chaves

    if (!x->is_leaf)                    // caso nao seja folha
        for (int i = 0; i <= mid; i++)  // mover filhos de x para z
            z->children[i] = x->children[i + mid + 1];  // copiar

    x->count = mid;
}

void BT_tree_insert_nonfull(BT_Node* x, int val) {
    int i = x->count - 1;
    if (x->is_leaf) {                     // folha?
        while (i >= 0 && val < x->key[i])
            x->key[i + 1] = x->key[i--];  // deslocar chaves e subtrair i APÓS
        x->key[i + 1] = val;              // inserir
        x->count++;
    } else {                              // não é folha
        while (i >= 0 && val < x->key[i])
            i--;

        // Verificação se o filho eh cheio
        if (x->children[i]->count == BT_MAX_CHAVES) {
            BT_split(x->children[i], x);

            // decidir qual filho usar pra recursão
            if (val > x->key[i])
                i++;  // próximo filho da mãe
        }

        BT_tree_insert_nonfull(x->children[i], val);
    }
}

bool BT_tree_search(BT_Tree* tree, int val) {
    BT_Node* x = tree->root;
    while (x != NULL) {
        // encontrar a posição do valor no nó
        int i = x->count - 1;
        while (i >= 0 && val > x->key[i])
            i--;

        if (val == x->key[i])  // encontrado
            return true;
        // ir pro próximo
        x = x->children[i + 1];
    }
    // não encontrado
    return false;
}

void BT_tree_print(BT_Tree* tree) {
    BT_Node* x = tree->root;
    if (x == NULL) {
        printf("Arvore vazia\n");
        return;
    }
    // printf("Arvore:\n");
    BT_tree_print_helper(x);
}

void BT_tree_print_helper(BT_Node* x) {
    if (x == NULL)
        return;

    for (int i = 0; i < x->count; i++) {
        // imprime filho da esquerda antes de continuar etc
        if (!x->is_leaf && x->children[i] != NULL)
            BT_tree_print_helper(x->children[i]);  // recursão pros filho

        printf("%d ", x->key[i]);  // imprimir chave do nó atual
    }

    // filho da direita
    if (!x->is_leaf && x->children[x->count] != NULL)
        BT_tree_print_helper(x->children[x->count]);
}