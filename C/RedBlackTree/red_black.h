/* Referência:
 Introduction to Algorithms 4th edition, Cormen, Leiserson, Rivest, Stein*/

/* Propriedades:
1. Every node is either red or black.
2. The root is black.
3. Every leaf (NIL) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to descendant leaves contain
the same number of black nodes. */

#include "stdbool.h"

typedef enum Color { RED, BLACK } Color;  // era isso ou usar bool ou sla
/* ------------------------------------------------------------------------ */
/* Nó (node) da árvore rubro-negra
data: valor associado ao nó
left, right = nós filhos da esquerda e direita, respectivamente
parent: ponteiro para o nó pai
color: cor do nó (RED ou BLACK) */
typedef struct RBNode {
    int            data;
    struct RBNode *left, *right, *parent;
    Color          color;
} RBNode;
/* ------------------------------------------------------------------------ */
/* Árvore rubro-negra.
root: ponteiro para nó raíz da árvore.*/
typedef struct RBTree {
    RBNode* root;
} RBTree;
/* ------------------------------------------------------------------------ */
/* Inicialização de node.
data: valor a ser associado ao nó.
Retorno: ponteiro para o novo nó. */
RBNode* RBT_node_init(int data);
/* ------------------------------------------------------------------------ */
/* Inicialização de tree.
Retorna ponteiro para a arvore rubro-negra inicializada. */
RBTree* RBT_tree_init();
/* ------------------------------------------------------------------------ */
/* Inserção de dados na árvore.
tree: arvore que receberá o novo nó.
data: valor a ser inserido.
Sem retorno. */
void RBT_tree_insert(RBTree* tree, int data);
/* ------------------------------------------------------------------------ */
/* Percorrer a árvore em ordem e exibir seus dados.
tree: arvore a ser percorrida. */
void RBT_tree_in_order(RBTree* tree);
/* ------------------------------------------------------------------------ */
/* Contagem de cores da árvore.
tree: arvore a ser percorrida.
red_count, black_count: contadores de cores, passados por referência.
Sem retorno. */
void RBT_tree_color_count(RBTree* tree, int* red_count, int* black_count);
/* ------------------------------------------------------------------------ */
/* Calcular a altura da árvore, a percorrendo.
tree: arvore a ser percorrida.
Retorno: altura da árvore */
int RBT_tree_height(RBTree* tree);
/* ------------------------------------------------------------------------ */
/* Solução da prova, formatada de maneira adequada:
tree: arvore a ser percorrida.
Sem retorn.*/
void solution(RBTree* tree);
/* ------------------------------------------------------------------------ */
/* Correção da árvore
tree: arvore a ser corrigida.
z: nó a ser corrigido.
Sem retorno.
*/
void RBT_tree_insert_fixup(RBTree* tree, RBNode* z);
/* ------------------------------------------------------------------------ */
/* Rotação à esquerda
tree: arvore a ser percorrida.
x: nó a ser corrigido.
Sem retorno.
*/
void RBT_tree_left_rotation(RBTree* tree, RBNode* x);
/* ------------------------------------------------------------------------ */
/* Rotação à direita
tree: arvore a ser percorrida.
x: nó a ser corrigido.
Sem retorno.
*/
void RBT_tree_right_rotation(RBTree* tree, RBNode* x);
/* ------------------------------------------------------------------------ */
/* -------------------------- Funções auxiliares -------------------------- */

/* Função auxiliar para percorrer a árvore em ordem.
node: nó a partir do qual a função vai percorrer.
Sem retorno.*/
void RBT_tree_in_order_helper(RBNode* node);
/* ------------------------------------------------------------------------ */
// bool is_red(RBNode* node);
// bool is_black(RBNode* node);
/* ------------------------------------------------------------------------ */
/* Verificar se nó é filho da esquerda.
node: nó a ser verificado.
Retorno: true se o nó for filho da esquerda, false caso contrário. */
bool RBT_is_left_child(RBNode* node);
/* ------------------------------------------------------------------------ */
/* Verificar se nó é filho da direita.
node: nó a ser verificado.
Retorno: true se o nó for filho da direita, false caso contrário. */
bool RBT_is_right_child(RBNode* node);
/* ------------------------------------------------------------------------ */
/* Função auxiliar para contagem de cores.
node: nó a partir do qual a função vai percorrer.
red_count, black_count: contadores de cores, passados por referência.
Sem retorno. */
void RBT_tree_color_count_helper(RBNode* node,
                                 int*    red_count,
                                 int*    black_count);
/* ------------------------------------------------------------------------ */
/* Função auxiliar para calcular a altura da árvore.
node: nó a partir do qual a função vai percorrer.
Retorno: altura da árvore neste ponto. */
int RBT_tree_height_helper(RBNode* node);
/* ------------------------------------------------------------------------ */