#pragma once

template <typename T>
class DoublyLinkedNode {
   public:
    T                 data;
    DoublyLinkedNode *prev, *next;

    ~DoublyLinkedNode() = default;
    DoublyLinkedNode(const T& val);
};

template <typename T>
class DoublyLinkedList {
   private:
    DoublyLinkedNode<T>* head;
    DoublyLinkedNode<T>* tail;
    size_t               node_count;

    // Return pointer to the node at the given index
    DoublyLinkedNode<T>* get_node(size_t index) const;

   public:
    template <typename... Args>
    DoublyLinkedList(Args&&... args);
    ~DoublyLinkedList();

    // Return number of nodes in list
    size_t size() const;

    // Access value of node at given index
    T& operator[](size_t index) const;
    // Access value at start of list
    T& front() const;
    // Access value at end of list
    T& back() const;
    // Prepend to start of list
    template <typename... Args>
    void push_back(Args&&... args);
    void push_back(const T& val);
    // Append to end of list
    template <typename... Args>
    void push_front(Args&&... args);
    void push_front(const T& val);
    // Remove and return value at given index
    T pop(size_t index);
    // Remove and return value at start of list
    T pop_front();
    // Remove and return value at end of list
    T pop_back();
    // Ostream operator overload
    template <typename O>
    friend std::ostream& operator<<(std::ostream&              os,
                                    const DoublyLinkedList<O>& list);
};

#include "DoublyLinkedList.tpp"