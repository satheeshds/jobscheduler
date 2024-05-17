// minheap.h
#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <functional>
#include "job.h"
#include <cstdint> // for uint64_t

// template <typename T>
class MinHeap
{
private:
    std::vector<Job> heap;

    void heapify_up(size_t index);
    void heapify_down(size_t index);
    static size_t parent(size_t index);
    static size_t left_child(size_t index);
    static size_t right_child(size_t index);
    size_t size();

public:
    void push(const Job &key);
    void pop();
    Job top();
    bool empty();
    void print();
    // template <typename Predicate>
    Job extract(const std::function<bool(Job)> &pred);
};

#endif // MINHEAP_H
