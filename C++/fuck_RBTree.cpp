#include "memory"

template <typename T>
using u_ptr = std::unique_ptr<T>;
template <typename T>
using sptr = std::shared_ptr<T>;
template <typename T>
using w_ptr = std::weak_ptr<T>;
using std::make_unique, std::move;

enum class Color : bool { Black, Red };

class Node {
   private:
    int   data;
    Color color;
    u_ptr<Node> left, right;  // um nó é dono de seus filhos por isso uso u_ptr
    Node* parent;  // o tempo de vida do pai é maior que de seus filhos

   public:
    Node() : data(0), color(Color::Red), parent(nullptr) {}
    Node(int val) : data(val), color(Color::Red), parent(nullptr) {}

    // getters
    int get_data() const { return data; }
    // Color get_color() const { return color; }

    bool is_red() const { return color == Color::Red; }
    bool is_black() const { return color == Color::Black; }

    Node* get_left() const { return left.get(); }
    Node* get_right() const { return right.get(); }
    Node* get_parent() const { return parent; }

    // setters
    void set_data(int new_data) { data = new_data; }
    void set_red() { color = Color::Red; }
    void set_black() { color = Color::Black; }
    void set_parent(Node* new_parent) { parent = new_parent; }
    void set_left_child(u_ptr<Node> child) { left = move(child); }
    void set_right_child(u_ptr<Node> child) { right = move(child); }

    void flip_color() {
        color = (color == Color::Red) ? Color::Black : Color::Red;
    }
};

class RedBlackTree {
   private:
    // raiz privada
    u_ptr<Node> root;

   public:
    // métodos públicos
    Node* search(int query) { return recursive_search(root.get(), query); }

    void insert(int val) {
        u_ptr<Node> new_node = make_unique<Node>(val);
        insert_node(std::move(new_node));
    }

    void remove(int query) {
        Node* to_delete = search(query);
        remove_node(to_delete);
    }

   private:
    Node* recursive_search(Node* node, int query) {
        if (node == nullptr || node->get_data() == query)
            return node;  // encontramos o que queriamos - ou
                          // não tem mais o que procurar

        // busca
        if (query < node->get_data())
            return recursive_search(node->get_left(), query);
        return recursive_search(node->get_right(), query);
    }

    void insert_node(u_ptr<Node> new_node) {
        Node* parent  = nullptr;
        Node* current = root.get();

        // loop roda até termos a posição correta, onde o nó parent é anterior a
        // uma folha (null)
        while (current != nullptr) {
            parent = current;
            if (new_node->get_data() < current->get_data())
                current = current->get_left();  // placeholder
            else
                current = current->get_right();
        }

        new_node->set_parent(parent);

        if (parent == nullptr)  // árvore vazia
            root = move(new_node);
        else if (new_node->get_data() < parent->get_data())
            parent->set_left_child(move(new_node));
        else /* if (new_node->get_data() > parent->get_data()) */
            parent->set_right_child(move(new_node));

        insert_fix(move(new_node));  // sem certza se é assim
    }

    void insert_fix(u_ptr<Node>&& new_node) {
        Node* parent = new_node->get_parent();
        while (parent !-nullptr && new_node->get_parent()->is_red()) {
            Node* grandpa = parent->get_parent();
            if (parent == grandpa->get_left()) {
                Node* uncle = grandpa->get_right();  // pai é L, tio é R
                if (uncle && uncle->is_red()) {
                    parent->set_black();
                    uncle->set_black();
                    grandpa->set_red();
                    parent = grandpa->get_parent();
                } else {
                    if (new_node.get() == parent->get_right()) {
                        rotate_left(move(parent));
                    }
                }
            }
        }

        // RB-Insert-fixup(T,z)
        // while color[p[z]] = RED {
        //     if p[z] == left[p[p[z]]] {
        //         y = right[p[p[z]]]
        //         if color[y] = RED {
        //             color[p[z]] = BLACK
        //             color[y] = BLACK
        //             color[p[p[z]]] = RED
        //             z = p[p[z]]
        //         }
        //         else {
        //             if z = right[p[z]] {
        //                 z = p[z]
        //                 LEFT-Rotate(T,z)
        //             }
        //             color[p[z]] = BLACK
        //             color[p[p[z]]] = RED
        //             RIGHT-Rotate(T,p[p[z]])
        //         }
        //     }
        //     else {
        //         y = left[p[p[z]]]
        //         if color[y] = RED {
        //             color[p[z]] = BLACK
        //             color[y] = BLACK
        //             color[p[p[z]]] = RED
        //             z = p[p[z]]
        //         }
        //         else
        //             {
        //             if z = left[p[z]] {
        //                 z = p[z]
        //                 RIGHT-Rotate(T,z)
        //             }
        //             color[p[z]] = BLACK
        //             color[p[p[z]]] = RED
        //             LEFT-Rotate(T,p[p[z]])
        //         }
        //     }
        //     color[root[T]] = BLACK
        // }
    }

    void rotate_left(u_ptr<Node>&& node) {}
    void rotate_right(u_ptr<Node>&& node) {}

    void remove_fix(Node* node) {}
    void remove_node(Node* node) {}
};