#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie_tree.h"

int main() {
    TT_Tree* tree = TT_tree_init();

    FILE* arq = fopen("rockyou-menor.txt", "r");
    if (arq == NULL) {
        printf("Cadê o arquivo?\n");
        exit(1);
    }

    char linha[256];
    while (fgets(linha, 256, arq)) {
        linha[strlen(linha) - 1] = '\0';  // remove o \n
        TT_tree_insert(tree, linha);
    }

    fclose(arq);

    char prefix[256];
    while (scanf("%s", prefix) == 1) {
        TT_tree_search_prefix(tree, prefix);
    }

    TT_tree_destroy(tree);  // limpar

    return 0;
}