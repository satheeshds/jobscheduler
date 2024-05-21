#include "node.h"

auto Node::set_child(Node *node) -> bool
{
    if (left == nullptr)
    {
        left = node;
        return true;
    }
    if (right == nullptr)
    {
        right = node;
        return true;
    }
    return false;
}

auto Node::remove_child(Node *node) -> bool
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

auto Node::parent(Node *root) -> Node * // NOLINT
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
auto Node::operator>(const Node &node) -> bool
{
    return job->operator>(*node.job);
}

auto Node::operator<(const Node &node) -> bool
{
    return job->operator<(*node.job);
}
