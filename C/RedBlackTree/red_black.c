#include "red_black.h"
#include <stdio.h>
#include <stdlib.h>

// "sentinela" - nó vazio global para as folhas e pa
static RBT_Node NIL = {0, NULL, NULL, NULL, BLACK /* propriedade 3 */};

/* ----------------------------- Inicialização ---------------------------- */

RBT_Node* RBT_node_init(int data) {
    RBT_Node* new_node = malloc(sizeof(RBT_Node));

    if (new_node == NULL) {
        printf("Erro na inicialização do nó (malloc).\n");
        exit(1);
    }

    new_node->data   = data;
    new_node->left   = &NIL;  // refs para o nó vazio
    new_node->right  = &NIL;
    new_node->parent = &NIL;
    new_node->color  = RED;
    return new_node;
}

RBT_Tree* RBT_tree_init() {
    RBT_Tree* new_tree = malloc(sizeof(RBT_Tree));

    if (new_tree == NULL) {
        printf("Erro na inicialização da árvore (malloc).\n");
        exit(1);
    }

    new_tree->root = &NIL;
    return new_tree;
}

/* ------------------------------- Inserção ------------------------------- */

void RBT_tree_insert(RBT_Tree* tree, int data) {
    // x = root[T], y = nil[T], z = z[T]
    RBT_Node *x = tree->root, *y = &NIL, *z = RBT_node_init(data);

    while (x != &NIL) {
        y = x;  // vamos a esq. ou a dir. conforme a chave for menor ou maior
        if (z->data < x->data)  // key[z] < key[x]
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == &NIL)  // caso árvore vazia
        tree->root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    z->left  = &NIL;                 // folhas são NIL
    z->right = &NIL;
    z->color = RED;                  // nó começa vermelho
    RBT_tree_insert_fixup(tree, z);  // manter as propriedades da árvore
}

void RBT_tree_insert_fixup(RBT_Tree* tree, RBT_Node* z) {
    RBT_Node* y = &NIL;  // tio de z
    while (z->parent->color == RED) {
        if (RBT_is_left_child(z->parent)) {
            y = z->parent->parent->right;  // tio da direita
            if (y->color == RED) {         // CASO 1: tio de z, y é vermelho
                z->parent->color         = BLACK;
                y->color                 = BLACK;
                z->parent->parent->color = RED;
                z                        = z->parent->parent;
            } else {
                // CASO 2: tio de z, y é preto e z é direita
                if (RBT_is_right_child(z)) {
                    z = z->parent;
                    RBT_tree_left_rotation(tree, z);
                }
                // CASO 3: tio de z, y é preto e z é esquerda
                z->parent->color         = BLACK;
                z->parent->parent->color = RED;
                RBT_tree_right_rotation(tree, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;  // tio da esquerda
            if (y->color == RED) {
                z->parent->color         = BLACK;
                y->color                 = BLACK;
                z->parent->parent->color = RED;
                z                        = z->parent->parent;
            } else {
                if (RBT_is_left_child(z)) {
                    z = z->parent;
                    RBT_tree_right_rotation(tree, z);
                }
                z->parent->color         = BLACK;
                z->parent->parent->color = RED;
                RBT_tree_left_rotation(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;  // propriedade 2, raiz sempre preta
}

/* ------------------------------- Rotações ------------------------------- */

void RBT_tree_left_rotation(RBT_Tree* tree, RBT_Node* x) {
    RBT_Node* y = x->right;
    x->right    = y->left;  // subárvore de y substitui a subárvore de x
    if (y->left != &NIL)    // subárvore não vazia
        y->left->parent = x;
    y->parent = x->parent;  // ponteiro pai de y passa a ser o pai de x
    if (x->parent == &NIL)
        tree->root = y;
    else if (RBT_is_left_child(x))
        x->parent->left = y;
    else  // RBT_is_right_child(x)
        x->parent->right = y;
    y->left   = x;
    x->parent = y;
}

void RBT_tree_right_rotation(RBT_Tree* tree, RBT_Node* x) {
    RBT_Node* y = x->left;
    x->left     = y->right;
    if (y->right != &NIL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == &NIL)
        tree->root = y;
    else if (RBT_is_left_child(x))
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right  = x;
    x->parent = y;
}

/* ------------------------------------------------------------------------ */

void RBT_tree_in_order(RBT_Tree* tree) {
    RBT_tree_in_order_helper(tree->root);
}

void RBT_tree_in_order_helper(RBT_Node* node) {
    if (node == &NIL)
        return;
    RBT_tree_in_order_helper(node->left);
    printf("%d ", node->data);
    RBT_tree_in_order_helper(node->right);
}

/* ------------------------------------------------------------------------ */

// código fica mais legível SEM essas funções e sim node->color == RED, etc.
// bool is_red(RBT_Node* node) {
//     return node->color == RED;
// }
// bool is_black(RBT_Node* node) {
//     return node->color == BLACK;
// }

/* ------------------------------------------------------------------------ */

bool RBT_is_left_child(RBT_Node* node) {
    return node == node->parent->left;
}
bool RBT_is_right_child(RBT_Node* node) {
    return node == node->parent->right;
}

/* ------------------------------------------------------------------------ */

void RBT_tree_color_count(RBT_Tree* tree, int* red_count, int* black_count) {
    *red_count   = 0;
    *black_count = 0;
    RBT_tree_color_count_helper(tree->root, red_count, black_count);
}

void RBT_tree_color_count_helper(RBT_Node* node,
                                 int*      red_count,
                                 int*      black_count) {
    if (node == &NIL)
        return;

    if (node->color == RED)
        (*red_count)++;
    else
        (*black_count)++;
    RBT_tree_color_count_helper(node->left, red_count, black_count);
    RBT_tree_color_count_helper(node->right, red_count, black_count);
}

/* ------------------------------------------------------------------------ */

void solution(RBT_Tree* tree) {
    printf("Percurso em ordem: ");
    RBT_tree_in_order(tree);
    printf("\n");

    int raiz   = tree->root->data;
    int altura = RBT_tree_height(tree);
    int qtd_preto, qtd_vermelho;
    RBT_tree_color_count(tree, &qtd_vermelho, &qtd_preto);

    printf("Raiz: %d\n", tree->root->data);
    printf("Altura: %d\n", altura);
    printf("Quantidade de nós vermelhos: %d\n", qtd_vermelho);
    printf("Quantidade de nós pretos: %d\n", qtd_preto);
}

/* ------------------------------------------------------------------------ */

int RBT_tree_height(RBT_Tree* tree) {
    return RBT_tree_height_helper(tree->root);
}

int RBT_tree_height_helper(RBT_Node* node) {
    if (node == &NIL)
        return -1;  // tava retornando 0 antes mas isso dava 1 a mais
    int left_h  = RBT_tree_height_helper(node->left);
    int right_h = RBT_tree_height_helper(node->right);
    // calcular a altura recursivamente, usando o maior tamanho de cada lado
    return left_h > right_h ? left_h + 1 : right_h + 1;
}