#ifndef NODE_H
#define NODE_H

#include "job.h"

class Node
{
private:
    /* data */
    Job *job;
    Node *left{nullptr};
    Node *right{nullptr};

public:
    explicit Node(Job *job) : job(job) {}
    ~Node()
    {
        delete left;
        delete right;
    }

    auto left_child() -> Node * { return left; }
    auto right_child() -> Node * { return right; }
    auto get_job() -> Job * { return job; }
    auto set_job(Job *job) -> void { this->job = job; }
    auto set_child(Node *node) -> bool
    {
        if (left == nullptr)
        {
            left = node;
        }
        else if (right == nullptr)
        {
            right = node;
        }
    }
    auto remove_child(Node *node) -> bool
    {
        if (left == node)
        {
            left = nullptr;
            return true;
        }
        if (right == node)
        {
            right = nullptr;
            return true;
        }
        return false;
    }

    auto parent(Node *root) -> Node * // NOLINT
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (root->left == this || root->right == this)
        {
            return root;
        }
        auto *left = parent(root->left);
        auto *right = parent(root->right);
        return (left != nullptr) ? left : right;
    }

    auto operator>(const Node &node) -> bool { return job > node.job; }
    auto operator<(const Node &node) -> bool { return job < node.job; }

    // delete copy constructor and copy assignment operator
    Node(const Node &) = delete;
    auto operator=(const Node &) -> Node & = delete;

    // delete move constructor and move assignment operator
    Node(Node &&) = delete;
    auto operator=(Node &&) -> Node & = delete;
};

#endif // NODE_H
