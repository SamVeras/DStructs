/* Referência:
 Introduction to Algorithms 4th edition, Cormen, Leiserson, Rivest, Stein
 The Art of Computer Programming, Knuth */

/* Propriedades:
1. Every node has at most m children.
2. Every node, except for the root and the leaves, has at least ⌈m/2⌉ children.
3. The root node has at least two children unless it is a leaf.
4. All leaves appear on the same level.
5. A non-leaf node with k children contains k−1 keys. */

#include <stdbool.h>
#define BT_ORDER 4                          // m
#define BT_MAX_CHAVES (BT_ORDER - 1)        // m-1
#define BT_MIN_FILHOS ((BT_ORDER + 1) / 2)  // ⌈m/2⌉, +1 é pra arredondar certo

typedef struct BT_Node {
    int             key[BT_MAX_CHAVES];
    int             count;
    struct BT_Node* children[BT_ORDER];
    bool            is_leaf;
} BT_Node;

typedef struct BT_Tree {
    BT_Node* root;
} BT_Tree;

BT_Node* BT_node_init(bool leaf);
BT_Tree* BT_tree_init();
void     BT_tree_insert(BT_Tree* tree, int val);
void     BT_split(BT_Node* x, BT_Node* y);
void     BT_tree_insert_nonfull(BT_Node* x, int val);
bool     BT_tree_search(BT_Tree* tree, int val);
void     BT_tree_print(BT_Tree* tree);
void     BT_tree_print_helper(BT_Node* x);
