// minheap.h
#ifndef MINHEAP_H
#define MINHEAP_H

#include <cstddef>
#include <vector>
#include <functional>
#include "job.h"

// template <typename T>
class MinHeap
{
private:
    std::vector<Job> heap;

    void heapify_up(size_t index);
    void heapify_down(size_t index);
    static auto parent(size_t index) -> size_t;
    static auto left_child(size_t index) -> size_t;
    static auto right_child(size_t index) -> size_t;
    auto size() -> size_t;

public:
    void push(const Job &key);
    void pop();
    auto top() -> Job;
    auto empty() -> bool;
    void print();
    // template <typename Predicate>
    auto extract(const std::function<bool(Job)> &pred) -> Job;
};

#endif // MINHEAP_H
