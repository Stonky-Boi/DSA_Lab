#include <iostream>
#include <vector>
#include "../../trees/binary_tree.hpp"

bt::Node<int> *build_tree_in_post(const std::vector<int> &in, int in_start, int in_end, const std::vector<int> &post, int post_start, int post_end, bt::Node<int> *parent)
{
    if (in_start > in_end || post_start > post_end)
        return nullptr;
    bt::Node<int> *root = new bt::Node<int>(post[post_end]);
    root->parent = parent;
    int idx = in_start;
    while (in[idx] != post[post_end])
        idx++;
    int left_size = idx - in_start;
    root->left = build_tree_in_post(in, in_start, idx - 1, post, post_start, post_start + left_size - 1, root);
    root->right = build_tree_in_post(in, idx + 1, in_end, post, post_start + left_size, post_end - 1, root);
    return root;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> inorder(n), postorder(n);
    for (int &x : inorder)
        std::cin >> x;
    for (int &x : postorder)
        std::cin >> x;
    bt::BinaryTree<int> tree;
    tree.root = build_tree_in_post(inorder, 0, n - 1, postorder, 0, n - 1, nullptr);
    tree.preorder(tree.root);
    std::cout << std::endl;
    return 0;
}