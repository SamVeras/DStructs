// TO-DO: funções adicionais e declarar e implementar funções pra limpeza de
// memória.

/* Referência:
 Introduction to Algorithms 4th edition, Cormen, Leiserson, Rivest, Stein*/

/* Propriedades:
1. Every node is either red or black.
2. The root is black.
3. Every leaf (NIL) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to descendant leaves contain
the same number of black nodes. */

#include <stdbool.h>

typedef enum RBT_Color {
    BLACK,    // 0
    RED       // 1
} RBT_Color;  // era isso ou usar bool ou sla
/* ------------------------------------------------------------------------ */

/* Nó (node) da árvore rubro-negra
data: valor associado ao nó
left, right = nós filhos da esquerda e direita, respectivamente
parent: ponteiro para o nó pai
color: cor do nó (RED ou BLACK) */
typedef struct RBT_Node {
    int              data;
    struct RBT_Node *left, *right, *parent;
    RBT_Color        color;
} RBT_Node;
/* ------------------------------------------------------------------------ */

/* Árvore rubro-negra.
root: ponteiro para nó raíz da árvore.*/
typedef struct RBT_Tree {
    RBT_Node* root;
} RBT_Tree;
/* ------------------------------------------------------------------------ */

/* Inicialização de node.
data: valor a ser associado ao nó.
Retorno: ponteiro para o novo nó. */
RBT_Node* RBT_node_init(int data);
/* ------------------------------------------------------------------------ */

/* Inicialização de tree.
Retorna ponteiro para a arvore rubro-negra inicializada. */
RBT_Tree* RBT_tree_init();
/* ------------------------------------------------------------------------ */

/* Inserção de dados na árvore.
tree: arvore que receberá o novo nó.
data: valor a ser inserido.
Sem retorno. */
void RBT_tree_insert(RBT_Tree* tree, int data);
/* ------------------------------------------------------------------------ */

/* Percorrer a árvore em ordem e exibir seus dados.
tree: arvore a ser percorrida.
Sem retorno. */
void RBT_tree_in_order(RBT_Tree* tree);
/* ------------------------------------------------------------------------ */

/* Contagem de cores da árvore.
tree: arvore a ser percorrida.
red_count, black_count: contadores de cores, passados por referência.
Sem retorno. */
void RBT_tree_color_count(RBT_Tree* tree, int* red_count, int* black_count);
/* ------------------------------------------------------------------------ */

/* Calcular a altura da árvore, a percorrendo.
tree: arvore a ser percorrida.
Retorno: altura da árvore */
int RBT_tree_height(RBT_Tree* tree);
/* ------------------------------------------------------------------------ */

/* Solução da prova, formatada de maneira adequada:
tree: arvore a ser percorrida.
Sem retorn.*/
void solution(RBT_Tree* tree);
/* ------------------------------------------------------------------------ */

/* Correção da árvore
tree: arvore a ser corrigida.
z: nó a ser corrigido.
Sem retorno.
*/
void RBT_tree_insert_fixup(RBT_Tree* tree, RBT_Node* z);
/* ------------------------------------------------------------------------ */

/* Rotação à esquerda
tree: arvore a ser percorrida.
x: nó a ser corrigido.
Sem retorno.
*/
void RBT_tree_left_rotation(RBT_Tree* tree, RBT_Node* x);
/* ------------------------------------------------------------------------ */

/* Rotação à direita
tree: arvore a ser percorrida.
x: nó a ser corrigido.
Sem retorno.
*/
void RBT_tree_right_rotation(RBT_Tree* tree, RBT_Node* x);
/* ------------------------------------------------------------------------ */

/* -------------------------- Funções auxiliares -------------------------- */

/* Função auxiliar para percorrer a árvore em ordem.
node: nó a partir do qual a função vai percorrer.
Sem retorno.*/
void RBT_tree_in_order_helper(RBT_Node* node);
/* ------------------------------------------------------------------------ */

// bool is_red(RBT_Node* node);
// bool is_black(RBT_Node* node);
/* ------------------------------------------------------------------------ */

/* Verificar se nó é filho da esquerda.
node: nó a ser verificado.
Retorno: true se o nó for filho da esquerda, false caso contrário. */
bool RBT_is_left_child(RBT_Node* node);
/* ------------------------------------------------------------------------ */

/* Verificar se nó é filho da direita.
node: nó a ser verificado.
Retorno: true se o nó for filho da direita, false caso contrário. */
bool RBT_is_right_child(RBT_Node* node);
/* ------------------------------------------------------------------------ */

/* Função auxiliar para contagem de cores.
node: nó a partir do qual a função vai percorrer.
red_count, black_count: contadores de cores, passados por referência.
Sem retorno. */
void RBT_tree_color_count_helper(RBT_Node* node,
                                 int*      red_count,
                                 int*      black_count);
/* ------------------------------------------------------------------------ */

/* Função auxiliar para calcular a altura da árvore.
node: nó a partir do qual a função vai percorrer.
Retorno: altura da árvore neste ponto. */
int RBT_tree_height_helper(RBT_Node* node);
/* ------------------------------------------------------------------------ */

/* Destruir a árvore
tree: arvore a ser destruída.
Sem retorno. */
void RBT_tree_destroy(RBT_Tree* tree);
/* ------------------------------------------------------------------------ */

/* Destruir o nó
node: nó a ser destruído.
Sem retorno. */
void RBT_node_destroy(RBT_Node* node);
/* ------------------------------------------------------------------------ */