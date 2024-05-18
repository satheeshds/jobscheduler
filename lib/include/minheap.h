// minheap.h
#ifndef MINHEAP_H
#define MINHEAP_H

#include <cstddef>
#include <functional>
#include "node.h"

// template <typename T>
class MinHeap
{
private:
    Node *root{nullptr};
    Node *tail{nullptr};

    void heapify_up(Node *node);
    void heapify_down(Node *node);
    static auto parent(size_t index) -> size_t;
    static auto left_child(size_t index) -> size_t;
    static auto right_child(size_t index) -> size_t;
    auto size() -> size_t;
    auto last() -> Node *;

public:
    void push(Node *node);
    void pop();
    auto top() -> Node *;
    auto empty() -> bool;
    void print();
    // template <typename Predicate>
    auto extract(const std::function<bool(Node)> &pred) -> Node *;
};

#endif // MINHEAP_H
