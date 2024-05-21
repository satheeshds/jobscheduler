#ifndef NODE_H
#define NODE_H

#include "job.h"

class Node
{
private:
    /* data */
    Job *job{};
    Node *left{nullptr};
    Node *right{nullptr};

public:
    explicit Node(Job *job) : job(job) {}
    Node() = default;
    ~Node() = default;

    auto left_child() -> Node * { return left; }
    auto right_child() -> Node * { return right; }
    auto get_job() -> Job * { return job; }
    auto set_job(Job *job) -> void { this->job = job; }
    auto set_child(Node *node) -> bool;

    auto remove_child(Node *node) -> bool;

    auto parent(Node *root) -> Node *; // NOLINT

    auto operator>(const Node &node) -> bool;

    auto operator<(const Node &node) -> bool;

    // delete copy constructor and copy assignment operator
    Node(const Node &) = delete;
    auto operator=(const Node &) -> Node & = delete;

    // delete move constructor and move assignment operator
    Node(Node &&) = delete;
    auto operator=(Node &&) -> Node & = delete;
};

#endif // NODE_H
