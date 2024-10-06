#include "btree.h"

int main() {
    BT_Tree* tree = BT_tree_init();
    BT_tree_insert(tree, 1);
    BT_tree_insert(tree, 2);
    BT_tree_insert(tree, 3);
    BT_tree_insert(tree, 4);
    BT_tree_insert(tree, 5);
    BT_tree_insert(tree, 6);
    BT_tree_insert(tree, 7);
    BT_tree_insert(tree, 8);
    BT_tree_insert(tree, 9);
    BT_tree_insert(tree, 10);
    BT_tree_insert(tree, 11);
    BT_tree_insert(tree, 12);
    BT_tree_insert(tree, 13);
    BT_tree_insert(tree, 14);
    BT_tree_insert(tree, 15);
    BT_tree_insert(tree, 16);
    BT_tree_insert(tree, 17);
    BT_tree_insert(tree, 18);
    BT_tree_insert(tree, 19);
    BT_tree_print(tree);
    return 0;
}