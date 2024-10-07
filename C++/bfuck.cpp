#include "BTree.hpp"

namespace BT {  // pra não poluir o namespace padrão
/* ------------------------------------------------------------------------ */

void Node::traverse() {
    int i;
    for (i = 0; i < key_count; i++) {
        if (is_leaf == false) {       // Se não for folha...
            children[i]->traverse();  // Chamada recursiva pros filhos
        }
        std::cout << keys[i] << " ";
    }
    if (is_leaf == false) {       // Finalmente, se não for folha...
        children[i]->traverse();  // Chamada recursiva para o último filho
                                  // (após imprimir todas as chaves)
    }
}
/* ------------------------------------------------------------------------ */

bool Node::search(int key) {
    int i = 0;
    while (i < key_count && key > keys[i])
        i++;  // avança até achar um maior ou igual

    if (i < key_count && keys[i] == key)  // Se achou retorna true
        return true;

    if (is_leaf)  // Se é folha, e não achou, a busca acabou
        return false;

    return children[i]->search(key);  // Caso contrário, continua a busca
}
/* ------------------------------------------------------------------------ */

void Tree::insert(int key) {
    if (root == nullptr) {
        // Cria uma raíz se a árvore está vazia
        root            = std::make_shared<Node>(true);
        root->keys[0]   = key;
        root->key_count = 1;
        return;
    }

    if (root->key_count == MAX_KEYS) {
        // Cria uma nova raiz e divide se a raíz estiver cheia
        auto s         = std::make_shared<Node>(false);
        s->children[0] = root;
        s->split(0, root);  // Divisão
        int i = (s->keys[0] < key) ? 1 : 0;
        s->children[i]->insert(key);
        root = s;
    } else {  // se não está cheia...
        root->insert(key);
    }
}
/* ------------------------------------------------------------------------ */

void Node::insert(int key) {
    int i = key_count - 1;
    if (is_leaf) {
        // insere a chave se é folha
        while (i >= 0 && keys[i] > key)
            keys[i + 1] = keys[i--];  // deslocar chaves e subtrair i após isso
        keys[i + 1] = key;
        key_count++;
        return;
    }
    while (i >= 0 && keys[i] > key)  // encontrar o filho certo pra inserir
        i--;

    if (children[i + 1]->key_count == MAX_KEYS) {
        split(i + 1, children[i + 1]);
        if (keys[i + 1] < key) {
            i++;
        }
    }

    children[i + 1]->insert(key);  // chamada recursiva
}
/* ------------------------------------------------------------------------ */

void Node::split(int i, std::shared_ptr<Node> y) {
    auto z       = std::make_shared<Node>(y->is_leaf);
    z->key_count = MIN_KEYS;

    for (int j = 0; j < MIN_KEYS; j++) {
        z->keys[j] = y->keys[j + MIN_KEYS + 1];
    }

    if (!y->is_leaf) {
        for (int j = 0; j <= MIN_KEYS; j++) {
            z->children[j] = y->children[j + MIN_KEYS + 1];
        }
    }

    y->key_count = MIN_KEYS;

    for (int j = key_count; j >= i + 1; --j) {
        children[j + 1] = children[j];
    }

    children[i + 1] = z;

    for (int j = key_count - 1; j >= i; --j) {
        keys[j + 1] = keys[j];
    }

    // insere a chave do meio no meio
    keys[i] = y->keys[MIN_KEYS];
    key_count++;
}
/* ------------------------------------------------------------------------ */
}  // namespace BT
