#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

std::mt19937 gen(std::random_device{}());

enum class Color { Red, Black };

template <typename T>
struct Node {
    T                        key;
    Color                    color;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;
    Node<T>*                 parent;

    Node(const T& key) : key{key}, parent{nullptr}, color{Color::Red} {}
};

template <typename T>
struct RBTree {
   public:
    std::unique_ptr<Node<T>> root;

   private:
    void LeftRotate(std::unique_ptr<Node<T>>&& x) {
        auto y   = std::move(x->right);
        x->right = std::move(y->left);
        if (x->right) {
            x->right->parent = x.get();
        }
        y->parent = x->parent;
        auto xp   = x->parent;
        if (!xp) {
            auto px            = x.release();
            root               = std::move(y);
            root->left         = std::unique_ptr<Node<T>>(px);
            root->left->parent = root.get();
        } else if (x == xp->left) {
            auto px                = x.release();
            xp->left               = std::move(y);
            xp->left->left         = std::unique_ptr<Node<T>>(px);
            xp->left->left->parent = xp->left.get();
        } else {
            auto px                 = x.release();
            xp->right               = std::move(y);
            xp->right->left         = std::unique_ptr<Node<T>>(px);
            xp->right->left->parent = xp->right.get();
        }
    }

    void RightRotate(std::unique_ptr<Node<T>>&& x) {
        auto y  = std::move(x->left);
        x->left = std::move(y->right);
        if (x->left) {
            x->left->parent = x.get();
        }
        y->parent = x->parent;
        auto xp   = x->parent;
        if (!xp) {
            auto px             = x.release();
            root                = std::move(y);
            root->right         = std::unique_ptr<Node<T>>(px);
            root->right->parent = root.get();
        } else if (x == xp->left) {
            auto px                 = x.release();
            xp->left                = std::move(y);
            xp->left->right         = std::unique_ptr<Node<T>>(px);
            xp->left->right->parent = xp->left.get();
        } else {
            auto px                  = x.release();
            xp->right                = std::move(y);
            xp->right->right         = std::unique_ptr<Node<T>>(px);
            xp->right->right->parent = xp->right.get();
        }
    }

   public:
    Node<T>* Search(const T& key) { return Search(root.get(), key); }

    void Insert(const T& key) {
        auto z = std::make_unique<Node<T>>(key);
        Insert(std::move(z));
    }

    void Delete(const T& key) {
        auto z = Search(key);
        Delete(z);
    }

   private:
    Node<T>* Search(Node<T>* x, const T& key) {
        if (!x || x->key == key) {
            return x;
        }
        if (key < x->key) {
            return Search(x->left.get(), key);
        } else {
            return Search(x->right.get(), key);
        }
    }

    void Insert(std::unique_ptr<Node<T>> z) {
        Node<T>* parrent = nullptr;
        Node<T>* current = root.get();
        while (current) {
            parrent = current;
            if (z->key < current->key) {
                current = current->left.get();
            } else {
                current = current->right.get();
            }
        }
        z->parent = parrent;
        if (!parrent) {
            root = std::move(z);
            InsertFixup(std::move(root));
        } else if (z->key < parrent->key) {
            parrent->left = std::move(z);
            InsertFixup(std::move(parrent->left));
        } else {
            parrent->right = std::move(z);
            InsertFixup(std::move(parrent->right));
        }
    }

    void InsertFixup(std::unique_ptr<Node<T>>&& new_node) {
        auto parent = new_node->parent;
        while (parent && parent->color == Color::Red) {
            auto grandparent = parent->parent;
            if (parent == grandparent->left.get()) {
                auto unc = grandparent->right.get();
                if (unc && unc->color == Color::Red) {
                    parent->color      = Color::Black;
                    unc->color         = Color::Black;
                    grandparent->color = Color::Red;
                    parent             = grandparent->parent;
                } else {
                    if (new_node == parent->right) {
                        LeftRotate(std::move(grandparent->left));
                        parent = grandparent->left.get();
                    }
                    parent->color         = Color::Black;
                    grandparent->color    = Color::Red;
                    auto greatgrandparent = grandparent->parent;
                    if (!greatgrandparent) {
                        RightRotate(std::move(root));
                    } else if (grandparent == greatgrandparent->left.get()) {
                        RightRotate(std::move(greatgrandparent->left));
                    } else {
                        RightRotate(std::move(greatgrandparent->right));
                    }
                }
            } else {
                auto unc = grandparent->left.get();
                if (unc && unc->color == Color::Red) {
                    parent->color      = Color::Black;
                    unc->color         = Color::Black;
                    grandparent->color = Color::Red;
                    parent             = grandparent->parent;
                } else {
                    if (new_node == parent->left) {
                        RightRotate(std::move(grandparent->right));
                        parent = grandparent->right.get();
                    }
                    parent->color         = Color::Black;
                    grandparent->color    = Color::Red;
                    auto greatgrandparent = grandparent->parent;
                    if (!greatgrandparent) {
                        LeftRotate(std::move(root));
                    } else if (grandparent == greatgrandparent->left.get()) {
                        LeftRotate(std::move(greatgrandparent->left));
                    } else {
                        LeftRotate(std::move(greatgrandparent->right));
                    }
                }
            }
        }
        root->color = Color::Black;
    }

    Node<T>* Transplant(Node<T>* u, std::unique_ptr<Node<T>>&& v) {
        if (v) {
            v->parent = u->parent;
        }
        Node<T>* w = nullptr;
        if (!u->parent) {
            w    = root.release();
            root = std::move(v);
        } else if (u == u->parent->left.get()) {
            w               = u->parent->left.release();
            u->parent->left = std::move(v);
        } else {
            w                = u->parent->right.release();
            u->parent->right = std::move(v);
        }
        return w;
    }

    Node<T>* Minimum(Node<T>* x) {
        if (!x) {
            return x;
        }
        while (x->left) {
            x = x->left.get();
        }
        return x;
    }

    void Delete(Node<T>* z) {
        if (!z) {
            return;
        }
        Color    orig_color = z->color;
        Node<T>* x          = nullptr;
        Node<T>* xp         = nullptr;
        if (!z->left) {
            x        = z->right.get();
            xp       = z->parent;
            auto pz  = Transplant(z, std::move(z->right));
            auto upz = std::unique_ptr<Node<T>>(pz);
        } else if (!z->right) {
            x        = z->left.get();
            xp       = z->parent;
            auto pz  = Transplant(z, std::move(z->left));
            auto upz = std::unique_ptr<Node<T>>(pz);
        } else {
            auto y     = Minimum(z->right.get());
            orig_color = y->color;
            x          = y->right.get();
            xp         = y;
            if (y->parent == z) {
                if (x) {
                    x->parent = y;
                }
                auto pz         = Transplant(z, std::move(z->right));
                y->left         = std::move(pz->left);
                y->left->parent = y;
                y->color        = pz->color;
                auto upz        = std::unique_ptr<Node<T>>(pz);
            } else {
                xp                = y->parent;
                auto py           = Transplant(y, std::move(y->right));
                py->right         = std::move(z->right);
                py->right->parent = py;
                auto upy          = std::unique_ptr<Node<T>>(py);
                auto pz           = Transplant(z, std::move(upy));
                py->left          = std::move(pz->left);
                py->left->parent  = py;
                py->color         = pz->color;
                auto upz          = std::unique_ptr<Node<T>>(pz);
            }
        }
        if (orig_color == Color::Black) {
            DeleteFixup(x, xp);
        }
    }

    void DeleteFixup(Node<T>* x, Node<T>* xp) {
        while (x != root.get() && (!x || x->color == Color::Black)) {
            if (x == xp->left.get()) {
                Node<T>* w = xp->right.get();
                if (w && w->color == Color::Red) {
                    w->color  = Color::Black;
                    xp->color = Color::Red;
                    auto xpp  = xp->parent;
                    if (!xpp) {
                        LeftRotate(std::move(root));
                    } else if (xp == xpp->left.get()) {
                        LeftRotate(std::move(xpp->left));
                    } else {
                        LeftRotate(std::move(xpp->right));
                    }
                    w = xp->right.get();
                }
                if (w && (!w->left || w->left->color == Color::Black) &&
                    (!w->right || w->right->color == Color::Black)) {
                    w->color = Color::Red;
                    x        = xp;
                    xp       = xp->parent;
                } else if (w) {
                    if (!w->right || w->right->color == Color::Black) {
                        w->left->color = Color::Black;
                        w->color       = Color::Red;
                        auto wp        = w->parent;
                        if (!wp) {
                            RightRotate(std::move(root));
                        } else if (w == wp->left.get()) {
                            RightRotate(std::move(wp->left));
                        } else {
                            RightRotate(std::move(wp->right));
                        }
                        w = xp->right.get();
                    }
                    w->color        = xp->color;
                    xp->color       = Color::Black;
                    w->right->color = Color::Black;
                    auto xpp        = xp->parent;
                    if (!xpp) {
                        LeftRotate(std::move(root));
                    } else if (xp == xpp->left.get()) {
                        LeftRotate(std::move(xpp->left));
                    } else {
                        LeftRotate(std::move(xpp->right));
                    }
                    x = root.get();
                } else {
                    x = root.get();
                }
            } else {
                Node<T>* w = xp->left.get();
                if (w && w->color == Color::Red) {
                    w->color  = Color::Black;
                    xp->color = Color::Red;
                    auto xpp  = xp->parent;
                    if (!xpp) {
                        RightRotate(std::move(root));
                    } else if (xp == xpp->left.get()) {
                        RightRotate(std::move(xpp->left));
                    } else {
                        RightRotate(std::move(xpp->right));
                    }
                    w = xp->left.get();
                }
                if (w && (!w->left || w->left->color == Color::Black) &&
                    (!w->right || w->right->color == Color::Black)) {
                    w->color = Color::Red;
                    x        = xp;
                    xp       = xp->parent;
                } else if (w) {
                    if (!w->left || w->left->color == Color::Black) {
                        w->right->color = Color::Black;
                        w->color        = Color::Red;
                        auto wp         = w->parent;
                        if (!wp) {
                            LeftRotate(std::move(root));
                        } else if (w == wp->left.get()) {
                            LeftRotate(std::move(wp->left));
                        } else {
                            LeftRotate(std::move(wp->right));
                        }
                        w = xp->left.get();
                    }
                    w->color       = xp->color;
                    xp->color      = Color::Black;
                    w->left->color = Color::Black;
                    auto xpp       = xp->parent;
                    if (!xpp) {
                        RightRotate(std::move(root));
                    } else if (xp == xpp->left.get()) {
                        RightRotate(std::move(xpp->left));
                    } else {
                        RightRotate(std::move(xpp->right));
                    }
                    x = root.get();
                } else {
                    x = root.get();
                }
            }
        }
        if (x) {
            x->color = Color::Black;
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Node<T>* node) {
    if (node) {
        os << node->left.get();
        os << node->key;
        if (node->color == Color::Black) {
            os << "● ";
        } else {
            os << "○ ";
        }
        os << node->right.get();
    }
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const RBTree<T>& tree) {
    os << tree.root.get();
    return os;
}

int main() {
    constexpr size_t SIZE = 100;
    std::vector<int> v(SIZE);
    std::iota(v.begin(), v.end(), 1);
    std::shuffle(v.begin(), v.end(), gen);
    RBTree<int> rbtree;
    for (auto n : v) {
        rbtree.Insert(n);
    }
    std::cout << '\n';
    std::cout << rbtree << '\n';
    std::shuffle(v.begin(), v.end(), gen);
    for (auto n : v) {
        rbtree.Delete(n);
        std::cout << rbtree << '\n';
    }
}
