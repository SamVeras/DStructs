/* Usei como referência:
https://www.andrew.cmu.edu/user/mm6/95-771/examples/RedBlackTreeProject/
que usa o livro do cormen como base
*/

#include <iostream>

enum class Color : bool { Black, Red };

class Node {
   private:
    int   data;  // poderia fazer com template, mas só precisamos de int
    Color color;
    Node *left, *right, *parent;
    // ia fazer com smart pointers mas to sem tempo

   public:
    Node(int val)
        : data(val),
          color(Color::Red),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
    Node() : Node(0) {}

    // usei getters e setters pq prefiro controlar essas coisas com métodos ao
    // invés de acesso direto

    // getters
    int   get_data() const { return data; }
    Node* get_left() const { return left; }
    Node* get_right() const { return right; }
    Node* get_parent() const { return parent; }

    // Color get_color() const { return color; }
    // desnecessário, só pode ser Red ou Black mesmo

    bool is_red() const { return color == Color::Red; }
    bool is_black() const { return color == Color::Black; }

    bool is_left_child() const {
        return (parent == nullptr) && parent->get_left() == this;
    }
    bool is_right_child() const {
        return (parent == nullptr) && parent->get_right() == this;
    }

    // setters
    void set_data(int new_data) { data = new_data; }
    void set_red() { color = Color::Red; }
    void set_black() { color = Color::Black; }
    void set_parent(Node* new_parent) { parent = new_parent; }
    void set_left_child(Node* child) { left = child; }
    void set_right_child(Node* child) { right = child; }

    void flip_color() {  // nem sei se vou usar isso
        color = (color == Color::Red) ? Color::Black : Color::Red;
    }
};

class RedBlackTree {
   private:
    // raiz privada
    Node* root;

    // método pra preservar as propriedades da árvore RB pós-inserção
    void insert_fix(Node* node) {
        Node* parent = node->get_parent();
        while (parent != nullptr && parent->is_red()) {
            Node* grandpa = parent->get_parent();
            if (parent->is_left_child()) {
                Node* unc = parent->get_parent()->get_right();
                if (unc != nullptr && unc->is_red()) {
                    parent->set_black();
                    unc->set_black();
                    grandpa->set_red();
                    node = grandpa;
                } else {
                    if (node->is_right_child()) {
                        node = parent;
                        rotate_left(node);
                    }
                    parent->set_black();
                    grandpa->set_red();
                    rotate_right(grandpa);
                }
            } else {
                Node* unc = parent->get_parent()->get_left();
                if (unc != nullptr && unc->is_red()) {
                    parent->set_black();
                    unc->set_black();
                    grandpa->set_red();
                    node = grandpa;
                } else {
                    if (node->is_left_child()) {
                        node = parent;
                        rotate_right(node);
                    }
                    parent->set_black();
                    grandpa->set_red();
                    rotate_left(grandpa);
                }
            }
            std::cout << "insert_fix: " << node->get_data() << "\n";
        }
        root->set_black();  // raiz sempre preta
    }

    void rotate_left(Node* node) {
        Node* temp = node->get_right();
        if (temp == nullptr)
            return;

        node->set_right_child(temp->get_left());
        if (temp->get_left() != nullptr)
            temp->get_left()->set_parent(node);
        temp->set_parent(node->get_parent());

        if (node->get_parent() == nullptr)
            root = temp;  // se for raiz, atualiza a raiz
        else if (node->is_left_child())
            node->get_parent()->set_left_child(temp);
        else
            node->get_parent()->set_right_child(temp);

        temp->set_left_child(node);
        node->set_parent(temp);

        std::cout << "rotate_left: " << node->get_data() << "\n";
    }

    void rotate_right(Node* node) {
        Node* temp = node->get_left();
        if (temp == nullptr)
            return;

        node->set_left_child(temp->get_right());
        if (temp->get_right() != nullptr)
            temp->get_right()->set_parent(node);
        temp->set_parent(node->get_parent());

        if (node->get_parent() == nullptr)
            root = temp;
        else if (node->is_right_child())
            node->get_parent()->set_right_child(temp);
        else
            node->get_parent()->set_left_child(temp);

        temp->set_right_child(node);
        node->set_parent(temp);

        std::cout << "rotate_right: " << node->get_data() << "\n";
    }

    // indo pra esquerda antes de ir pra direita iremos
    // mostrar a árvore em ordem, a partir da raiz
    void show(Node* node) {
        if (node == nullptr)
            return;

        show(node->get_left());
        std::cout << node->get_data() << " ";
        show(node->get_right());
    }

    void resposta_helper(Node* node, int& r, int& b) {
        // função recursiva pra me dar as coisas da resposta como eu quero
        if (node == nullptr)
            return;  // chegamos numa das folhas pretas nulas

        if (node->is_red())
            r++;
        else
            b++;

        resposta_helper(node->get_left(), r, b);
        std::cout << node->get_data() << " ";
        resposta_helper(node->get_right(), r, b);
    }

    int height(Node* node) {
        if (node == nullptr)
            return -1;  // tava retornando 0 antes mas isso dava 1 a mais

        int left_h  = height(node->get_left());
        int right_h = height(node->get_right());
        // calcular a altura recursivamente, usando o maior tamanho de cada lado
        return left_h > right_h ? left_h + 1 : right_h + 1;
    }

    void debug(Node* node, int c = 0) {
        if (node == nullptr)
            return;

        debug(node->get_left(), c + 1);

        std::cout << node->is_red() << " [" << node->get_data() << "]\t@ " << c;
        std::cout << "\n";

        debug(node->get_right(), c + 1);
    }

   public:
    RedBlackTree() : root(nullptr) {}

    // métodos públicos
    void insert(int val) {
        Node* new_node = new Node(val);
        Node* parent   = nullptr;
        Node* current  = root;

        while (current != nullptr) {
            parent = current;  // números menores vão pra esquerda, etc.
            if (new_node->get_data() < current->get_data())
                current = current->get_left();
            else
                current = current->get_right();
        }

        new_node->set_parent(parent);

        if (parent == nullptr) {
            root = new_node;
            new_node->set_black();
        } else if (new_node->get_data() < parent->get_data())
            parent->set_left_child(new_node);
        else /* if (val >= parent->get_data()) */
            parent->set_right_child(new_node);

        insert_fix(new_node);
    }

    bool contains(int val) {
        Node* current = root;

        while (current != nullptr) {
            if (val == current->get_data())
                return true;
            if (val < current->get_data())
                current = current->get_left();
            else
                current = current->get_right();
        }

        return false;
    }

    void show() {
        if (root == nullptr)
            return;
        show(root);
    }

    void resposta_formatada() {
        int reds = 0, blacks = 0;

        int raiz   = root->get_data();
        int altura = height(root);

        std::cout << "Percurso em ordem: ";

        resposta_helper(root, reds, blacks);

        std::cout << "\nRaiz: " << raiz << "\n";
        std::cout << "Altura: " << altura << "\n";
        std::cout << "Quantidade de nós vermelhos: " << reds << "\n";
        std::cout << "Quantidade de nós pretos: " << blacks << std::endl;
    }

    void debug() {
        if (root == nullptr)
            return;

        debug(root);
    }
};

int main() {
    RedBlackTree tree;

    int val;
    while (std::cin >> val) {
        tree.insert(val);
    }

    tree.debug();
    tree.resposta_formatada();
    return 0;
}
