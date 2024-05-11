#include <stdio.h>
#include <stdlib.h>

struct BinTreeNode {
  int                 data;
  struct BinTreeNode *left, *right;
};
struct BinTreeLinked {
  struct BinTreeNode* root;
  size_t              size;
};

typedef struct BinTreeNode   Node;
typedef struct BinTreeLinked Tree;

Node* init_node(int x) {
  Node* n = malloc(sizeof(Node));
  n->data = x;
  n->left = n->right = NULL;
  return n;
}
Tree* init_tree(int x) {
  Tree* t = malloc(sizeof(Tree));
  t->root = init_node(x);
  return t;
}
void tree_insert(Tree* t, int x) {
  Node* current = t->root;
  while (1) {
    if (x >= current->data) {
      if (current->right == NULL) {
        current->right = init_node(x);
        break;
      }
      current = current->right;
      continue;
    }
    if (current->left == NULL) {
      current->left = init_node(x);
      break;
    }
    current = current->left;
  }
}
void node_print(Node* n) {
  if (n == NULL)
    return;
  node_print(n->left);

  printf("Data: %d\n", n->data);
  // printf(" @ [%p]\n", n);
  // printf("Left: [%p], Right: [%p]\n", n->left, n->right);

  node_print(n->right);
}

void tree_print(Tree* t) {
  node_print(t->root);
}

void free_tree(Tree* t) {}

int main() {
  Tree* T = init_tree(5);
  tree_insert(T, 8);
  tree_insert(T, 2);
  tree_insert(T, 1);
  free_tree(T);
  tree_print(T);

  return 0;
}