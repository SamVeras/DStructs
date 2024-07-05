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

    DoublyLinkedNode<T>* get_node(size_t index) const;

   public:
    template <typename... Args>
    DoublyLinkedList(Args&&... args);
    ~DoublyLinkedList();

    size_t size() const;
    T      front() const;
    T      back() const;

    template <typename... Args>
    void push_back(Args&&... args);
    void push_back(const T& val);
    template <typename... Args>
    void push_front(Args&&... args);
    void push_front(const T& val);

    T pop(size_t index);
    T pop_front();
    T pop_back();

    template <typename O>
    friend std::ostream& operator<<(std::ostream&              os,
                                    const DoublyLinkedList<O>& list);

    T& operator[](size_t index) const;
};

#include "DoublyLinkedList.tpp"