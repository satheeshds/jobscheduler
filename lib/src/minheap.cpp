#include <cstdint>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>
#include "minheap.h"
#include <functional>
#include <queue>
#include "job.h"

auto swapJobs(Node *first, Node *second) -> void;
void MinHeap::heapify_up(Node *node) // NOLINT
{
    if (node == nullptr)
    {
        return;
    }
    auto *parent = node->parent(root);
    if (parent == nullptr)
    {
        return;
    }

    if (parent > node)
    {
        swapJobs(parent, node);
        heapify_up(parent);
    }
}

void MinHeap::heapify_down(Node *node) // NOLINT
{
    Node const *left = node->left_child();
    size_t const *right = right_child(index);
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

void MinHeap::push(Node *node)
{
    if (root == nullptr)
    {
        root = node;
        tail = node;
        return;
    }

    last()->set_child(node);

    heapify_up(node);
}

void MinHeap::pop()
{
    if (root == nullptr)
    {
        return;
    }

    auto *lastNode = last();
    if (lastNode->left_child() != nullptr)
    {
        lastNode = lastNode->left_child();
    }
    else if (lastNode->right_child() != nullptr)
    {
        lastNode = lastNode->right_child();
    }

    lastNode->parent(root)->remove_child(lastNode);

    root->set_job(lastNode->get_job());

    heapify_down(root);
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

auto MinHeap::last() -> Node *
{
    if (root == nullptr)
    {
        return nullptr;
    }

    std::queue<Node *> queue;
    queue.push(root);
    Node *last = nullptr;
    while (!queue.empty())
    {
        Node *current = queue.front();
        queue.pop();

        if (current->left_child() == nullptr || current->right_child() == nullptr)
        {
            last = current;
            break;
        }

        queue.push(current->left_child());
        queue.push(current->right_child());
    }
    return last;
}

auto swapJobs(Node *first, Node *second) -> void
{
    Job *temp = first->get_job();
    first->set_job(second->get_job());
    second->set_job(temp);
}
