#include <initializer_list>
#include <stdexcept>
#include "DoublyLinkedList.hpp"

template <typename T>
DoublyLinkedNode<T>::DoublyLinkedNode(const T& val)
    : data(val), prev(nullptr), next(nullptr) {}

template <typename T>
template <typename... Args>
DoublyLinkedList<T>::DoublyLinkedList(Args&&... args)
    : head(nullptr), tail(nullptr), node_count(0) {
    push_back(args...);
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    DoublyLinkedNode<T>* current = head;
    DoublyLinkedNode<T>* next    = nullptr;

    while (current != nullptr) {
        next = current->next;
        delete (current);
        current = next;
    }
}

/* ------------------------------------------------------------------------ */

template <typename T>
DoublyLinkedNode<T>* DoublyLinkedList<T>::get_node(size_t index) const {
    if (index > size() - 1)
        throw std::out_of_range("Index out of range");

    if (index >= size() / 2) {  // If index is in the second half of the list
        DoublyLinkedNode<T>* current = tail;

        while (index-- > 0)
            current = current->prev;

        return current;
    }

    DoublyLinkedNode<T>* current = head;

    while (index-- > 0)
        current = current->next;

    return current;
}

template <typename T>
size_t DoublyLinkedList<T>::size() const {
    return node_count;
}

template <typename T>
T& DoublyLinkedList<T>::operator[](size_t index) const {
    if (index > size() - 1)
        throw std::out_of_range("Index out of range");

    DoublyLinkedNode<T>* current = head;

    while (index-- > 0)
        current = current->next;

    return current->data;
}

template <typename T>
T& DoublyLinkedList<T>::front() const {
    return head->data;
}

template <typename T>
T& DoublyLinkedList<T>::back() const {
    return tail->data;
}

template <typename T>
template <typename... Args>
void DoublyLinkedList<T>::push_back(Args&&... args) {
    for (const T& val : {args...})
        push_back(val);
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T& val) {
    DoublyLinkedNode<T>* new_node = new DoublyLinkedNode<T>(val);

    if (head == nullptr)
        head = tail = new_node;
    else {
        tail->next     = new_node;
        new_node->prev = tail;
        tail           = new_node;
    }

    node_count++;
}

template <typename T>
template <typename... Args>
void DoublyLinkedList<T>::push_front(Args&&... args) {
    for (const T& val : {args...})
        push_front(val);
}

template <typename T>
void DoublyLinkedList<T>::push_front(const T& val) {
    DoublyLinkedNode<T>* new_node = new DoublyLinkedNode<T>(val);

    if (head == nullptr)
        head = tail = new_node;
    else {
        head->prev     = new_node;
        new_node->next = head;
        head           = new_node;
    }

    node_count++;
}

template <typename T>
T DoublyLinkedList<T>::pop(size_t index) {
    DoublyLinkedNode<T>* node = get_node(index);
    DoublyLinkedNode<T>* temp = nullptr;
    T                    data = node->data;

    temp             = node->prev;
    node->next->prev = temp;
    temp->next       = node->next;

    delete (node);
    return data;
}

template <typename T>
T DoublyLinkedList<T>::pop_front() {
    if (tail == nullptr)
        throw std::out_of_range("Empty list");

    T head_data = head->data;

    if (tail == head) {
        delete (head);
        tail = nullptr;
        head = nullptr;
    } else {
        head = head->next;
        delete (head->prev);
        head->prev = nullptr;
    }

    node_count--;
    return head_data;
}

// Delete and return value at start of list
template <typename T>
T DoublyLinkedList<T>::pop_back() {
    if (head == nullptr)
        throw std::out_of_range("Empty list");

    T tail_data = tail->data;

    if (tail == head) {
        delete (tail);
        tail = nullptr;
        head = nullptr;
    } else {
        tail = tail->prev;
        delete (tail->next);
        tail->next = nullptr;
    }

    node_count--;
    return tail_data;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& list) {
    DoublyLinkedNode<T>* current = list.head;

    os << "[";
    while (current != nullptr) {
        os << current->data;

        if (current->next != nullptr)
            os << ", ";

        current = current->next;
    }
    os << "]";
    return os;
}

/* ------------------------------------------------------------------------ */
