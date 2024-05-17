#include <cstdint>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>
#include "minheap.h"
#include <functional>
#include "job.h"

void MinHeap::heapify_up(size_t index) // NOLINT
{
    if ((index != 0) && heap[parent(index)] > heap[index])
    {
        std::swap(heap[index], heap[parent(index)]);
        heapify_up(parent(index));
    }
}

void MinHeap::heapify_down(size_t index) // NOLINT
{
    size_t const left = left_child(index);
    size_t const right = right_child(index);
    size_t smallest = index;

    if (left < size() && heap[left] < heap[index])
    {
        smallest = left;
    }

    if (right < size() && heap[right] < heap[smallest])
    {
        smallest = right;
    }

    if (smallest != index)
    {
        std::swap(heap[index], heap[smallest]);
        heapify_down(smallest);
    }
}

auto MinHeap::parent(size_t index) -> size_t { return (index - 1) / 2; }
auto MinHeap::left_child(size_t index) -> size_t { return (2 * index + 1); }
auto MinHeap::right_child(size_t index) -> size_t { return (2 * index + 2); }

auto MinHeap::size() -> size_t
{
    return heap.size();
}
auto MinHeap::empty() -> bool { return size() == 0; }

void MinHeap::push(const Job &key)
{
    heap.push_back(key);
    uint64_t const index = size() - 1;
    heapify_up(index);
}

void MinHeap::pop()
{
    if (size() == 0)
    {
        throw std::out_of_range("Heap is empty");
    }

    heap[0] = heap.back();
    heap.pop_back();

    heapify_down(0);
}

auto MinHeap::top() -> Job
{
    if (size() == 0)
    {
        throw std::out_of_range("Heap is empty");
    }

    return heap.front();
}

// template <typename Predicate>
auto MinHeap::extract(const std::function<bool(Job)> &pred) -> Job
{
    auto iterator = std::find_if(heap.begin(), heap.end(), pred);
    if (iterator == heap.end())
    {
        throw std::out_of_range("Element not found");
    }

    std::swap(*iterator, heap.back());
    Job value = heap.back();
    heap.pop_back();
    if (heap.size() > 1 && iterator != heap.end())
    {
        heapify_down(iterator - heap.begin());
    }
    // T value = *it;
    // heap.erase(it);
    return value;
}

void MinHeap::print()
{
    for (auto item : heap)
    {
        std::cout << item << '\n';
    }
    std::cout << '\n';
}
