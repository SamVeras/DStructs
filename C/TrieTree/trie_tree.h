#include <stdbool.h>

#define TT_MAX_CHARS 95  // Caractéres entre 32 e 126 [126 - 32 + 1 = 95]
/* ------------------------------------------------------------------------ */
/* Nó da árvore trie
children: array de N ponteiros para nós filhos
end: indica se o nó é o fim duma palavra */
typedef struct TT_Node {
    struct TT_Node* children[TT_MAX_CHARS];
    bool            end;
} TT_Node;
/* ------------------------------------------------------------------------ */
/* Árvore Trie
root: raiz da árvore */
typedef struct TT_Tree {
    struct TT_Node* root;
} TT_Tree;
/* ------------------------------------------------------------------------ */
/* Inicialização de um node
Sem parâmetros.
Retorno: ponteiro para o node inicializado */
TT_Node* TT_node_init();
/* ------------------------------------------------------------------------ */
/* Inicialiuzação da Arvore Trie
Sem parâmetros.
Retorno: ponteiro da árvore inicializada*/
TT_Tree* TT_tree_init();
/* ------------------------------------------------------------------------ */
/* Método de inserção na árvore
tree: arvore que receberá o novo nó.
word: palavra a ser inserida
Sem retorno. */
void TT_tree_insert(TT_Tree* tree, const char* word);
/* ------------------------------------------------------------------------ */
/* Método de busca e exibição de palavras com o prefixo especificado
tree: arvore a ser percorrida
prefix: prefixo buscado
Sem retorno. */
void TT_tree_search_prefix(TT_Tree* tree, const char* prefix);
/* ------------------------------------------------------------------------ */