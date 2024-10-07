#include "trie_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------ */

TT_Node* TT_node_init() {
    TT_Node* node = malloc(sizeof(TT_Node));

    if (node == NULL) {
        printf("Erro na inicialização do nó (malloc).\n");
        exit(1);
    }

    for (int i = 0; i < TT_MAX_CHARS; i++)
        node->children[i] = NULL;

    node->end = false;
    return node;
}
/* ------------------------------------------------------------------------ */

TT_Tree* TT_tree_init() {
    TT_Tree* tree = malloc(sizeof(TT_Tree));

    if (tree == NULL) {
        printf("Erro na inicialização da árvore (malloc).\n");
        exit(1);
    }

    tree->root = TT_node_init();
    return tree;
}
/* ------------------------------------------------------------------------ */

void TT_tree_insert(TT_Tree* tree, const char* word) {
    TT_Node* x = tree->root;
    for (int i = 0; word[i] != '\0'; i++) {  // iterar até o fim da palavra
        char c = word[i];
        if (c < 32 || c > 126)               // ignorar letras fora do range
            continue;
        int i = c - 32;
        if (x->children[i] == NULL)
            x->children[i] = TT_node_init();
        x = x->children[i];
    }
    x->end = true;  // chegamos ao final da palavra
}
/* ------------------------------------------------------------------------ */

void TT_tree_search_prefix(TT_Tree* tree, const char* prefix) {
    TT_Node* x = tree->root;

    for (int i = 0; prefix[i] != '\0'; i++) {
        char c = prefix[i];
        if (c < 32 || c > 126) {  // caractére invalido
            printf("Nenhuma senha encontrada com esse prefixo.\n");
            return;
        }

        int j = c - 32;

        if (x->children[j] == NULL) {  // fim da busca sem encontrar
            printf("Nenhuma senha encontrada com esse prefixo.\n");
            return;
        }

        x = x->children[j];
    }

    char b[256];
    strcpy(b, prefix);
    int d = strlen(prefix);

    if (x != NULL) {
        if (x->end) {
            b[d] = '\0';  // fim da str
            printf("%s\n", b);
        }

        for (int i = 0; i < TT_MAX_CHARS; i++) {
            if (x->children[i] != NULL) {
                b[d] = i + 32, b[d + 1] = '\0';
                TT_tree_search_prefix(tree, b);
            }
        }
    }
}
/* ------------------------------------------------------------------------ */

void TT_tree_destroy(TT_Tree* tree) {
    TT_node_destroy(tree->root);
    free(tree);
}
/* ------------------------------------------------------------------------ */

void TT_node_destroy(TT_Node* node) {
    for (int i = 0; i < TT_MAX_CHARS; i++)
        if (node->children[i] != NULL)
            TT_node_destroy(node->children[i]);
    free(node);
}
/* ------------------------------------------------------------------------ */