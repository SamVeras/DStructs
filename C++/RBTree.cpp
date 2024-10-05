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
    RedBlackTree() : root(nullptr) {}

    // métodos públicos
    void insert(int val) {
        Node* new_node = new Node(val);
        Node* parent   = nullptr;
        Node* current  = root;

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
        else if (val < parent->get_data())
            parent->set_left_child(new_node);
        else /* if (val >= parent->get_data()) */
            parent->set_right_child(new_node);

        insert_fix(new_node);
    }
};