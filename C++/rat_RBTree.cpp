/* Usei como referência:
https://www.andrew.cmu.edu/user/mm6/95-771/examples/RedBlackTreeProject/
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
    Node()
        : data(0),
          color(Color::Red),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
    Node(int val)
        : data(val),
          color(Color::Red),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}

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
    bool is_left_child() const { return parent->get_left() == this; }
    bool is_right_child() const { return parent->get_right() == this; }

    // setters
    void set_data(int new_data) { data = new_data; }
    void set_red() { color = Color::Red; }
    void set_black() { color = Color::Black; }
    void set_parent(Node* new_parent) { parent = new_parent; }
    void set_left_child(Node* child) { left = child; }
    void set_right_child(Node* child) { right = child; }

    void flip_color() {
        color = (color == Color::Red) ? Color::Black : Color::Red;
    }
};

class RedBlackTree {
   private:
    // raiz privada
    Node* root;

   public:
    // métodos públicos
    Node* search(int query) { return recursive_search(root, query); }

    void insert(int val) {
        Node* new_node = new Node(val);
        insert_node(new_node);
    }

    void remove(int query) {
        Node* to_delete = search(query);
        remove_node(to_delete);
    }

   private:
    Node* recursive_search(Node* node, int query) {
        if (node == nullptr || node->get_data() == query)
            return node;  // encontramos o que queriamos
                          // - ou não tem mais o que procurar

        // busca
        if (query < node->get_data())
            return recursive_search(node->get_left(), query);
        return recursive_search(node->get_right(), query);
    }

    void insert_node(Node* new_node) {
        Node* parent  = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;
            if (new_node->get_data() < current->get_data())
                current = current->get_left();
            else
                current = current->get_right();
        }

        new_node->set_parent(parent);
        if (parent == nullptr)
            root = new_node;
        else if (new_node->get_data() < parent->get_data())
            parent->set_left_child(new_node);
        else /* if (new_node->get_data() >= parent->get_data() */
            parent->set_right_child(new_node);

        insert_fix(new_node);
    }

    void insert_fix(Node* node) {
        Node* parent = node->get_parent();
        while (parent != nullptr && parent->is_red()) {
            Node* grandparent = parent->get_parent();
            if (parent->is_left_child()) {
                Node* unc = grandparent->get_right();
                if (unc != nullptr && unc->is_red()) {
                    parent->set_black();
                    unc->set_black();
                    grandparent->set_red();
                }
            }
        }
    }
    void remove_node(Node* node) {}
};