#include <stdio.h>
#include "red_black.h"

int main() {
    RBT_Tree* tree = RBT_tree_init();

    int input;
    while (scanf("%d", &input) == 1)
        RBT_tree_insert(tree, input);

    solution(tree);

    RBT_tree_destroy(tree);
    return 0;
}