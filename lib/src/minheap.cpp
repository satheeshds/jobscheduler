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
    Node *left = node->left_child();
    Node *right = node->right_child();
    Node *smallest = node;

    if (left != nullptr && left < node)
    {
        smallest = left;
    }

    if (right != nullptr && right < smallest)
    {
        smallest = right;
    }

    if (smallest != node)
    {
        swapJobs(node, smallest);
        heapify_down(smallest);
    }
}


auto MinHeap::empty() -> bool { return root == nullptr; }

void MinHeap::push(Node *node)
{
    if (root == nullptr)
    {
        root = node;
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

auto MinHeap::top() -> Node *
{
    if (empty())
    {
        throw std::out_of_range("Heap is empty");
    }

    return root;
}

// template <typename Predicate>
auto MinHeap::extract(const std::function<bool(Node *)> &pred) -> Node *
{   
    if(empty())
    {
        throw std::out_of_range("Heap is empty");
    }

    Node *node = nullptr;
    std::queue<Node *> queue;
    queue.push(root);
    while (!queue.empty())
    {
        Node *current = queue.front();
        queue.pop();
        if (current == nullptr)
        {
            continue;
        }
        if (pred(current))
        {
            node = current;
            break;
        }
        queue.push(current->left_child());
        queue.push(current->right_child());
    }

    if (node == nullptr)
    {
        throw std::out_of_range("Element not found");
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
    node->set_job(lastNode->get_job());
    heapify_down(node);

    return node;
}

void MinHeap::print()
{
    std::queue<Node *> queue;
    queue.push(root);
    while (!queue.empty())
    {
        Node *current = queue.front();
        queue.pop();
        if (current == nullptr)
        {
            continue;
        }
        std::cout << current->get_job() << '\n';
        queue.push(current->left_child());
        queue.push(current->right_child());
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

        if(current == nullptr)
        {
            continue;
        }

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


