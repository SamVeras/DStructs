#include <algorithm>
#include <array>
#include <iostream>
#include <memory>

namespace BT {

constexpr int MAX_KIDS{4};  // m = 4
constexpr int MIN_KIDS{2};  // ⌈m/2⌉
constexpr int MIN_KEYS{1};
constexpr int MAX_KEYS{3};  // m-1

struct Node {
    int                       key_count;  // quantidade de chaves
    std::array<int, MAX_KEYS> keys;       // array de chaves
    std::array<std::shared_ptr<Node>, MAX_KEYS + 1> children;  // arr de filhos
    bool                                            is_leaf;   // folha?

    /* ----------------------------- Construtores ------------------------- */

    Node() : key_count(0), is_leaf(true) {}
    Node(bool leaf) : key_count(0), is_leaf(leaf) {}
    /* -------------------------------------------------------------------- */

    /* Método para inserir uma nova chave em um nó não cheio
    key: valor da nova chave.
    Sem retorno. */
    void insert(int key);
    /* -------------------------------------------------------------------- */

    /* Divide o filho y de um nó
    i: indice do nó no qual o filho y está.
    y: o filho a ser dividido.
    Sem retorno. */
    void split(int i, std::shared_ptr<Node> y);
    /* -------------------------------------------------------------------- */

    /* Método para percorrer o nó em ordem
    Sem retorno. */
    void traverse();
    /* -------------------------------------------------------------------- */

    // Function to search for a key in the subtree rooted at this node
    /* Método para buscar uma chave na subárvore
    key: valor a ser buscado.
    Retorna true se a chave for encontrada, false caso contrário. */
    bool search(int key);
    /* -------------------------------------------------------------------- */
};

struct Tree {
    std::shared_ptr<Node> root;

    Tree() : root(nullptr) {}

    void traverse() {
        if (root != nullptr)
            root->traverse();
    }

    bool search(int key) {
        if (root == nullptr)
            return false;
        return root->search(key);
    }
    /* -------------------------------------------------------------------- */

    /* Método para inserir uma nova chave na árvore
    key: valor da nova chave.
    Sem retorno. */
    void insert(int key);
};
}  // namespace BT