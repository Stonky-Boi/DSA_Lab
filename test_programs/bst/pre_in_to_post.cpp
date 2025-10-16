#include <iostream>
#include <vector>
#include "../../trees/binary_tree.hpp"

bt::Node<int> *build_tree_pre_in(const std::vector<int> &pre, int pre_start, int pre_end, const std::vector<int> &in, int in_start, int in_end, bt::Node<int> *parent)
{
    if (pre_start > pre_end || in_start > in_end)
        return nullptr;
    bt::Node<int> *root = new bt::Node<int>(pre[pre_start]);
    root->parent = parent;
    int idx = in_start;
    while (in[idx] != pre[pre_start])
        idx++;
    int left_size = idx - in_start;
    root->left = build_tree_pre_in(pre, pre_start + 1, pre_start + left_size, in, in_start, idx - 1, root);
    root->right = build_tree_pre_in(pre, pre_start + left_size + 1, pre_end, in, idx + 1, in_end, root);
    return root;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> preorder(n), inorder(n);
    for (int &x : preorder)
        std::cin >> x;
    for (int &x : inorder)
        std::cin >> x;
    bt::BinaryTree<int> tree;
    tree.root = build_tree_pre_in(preorder, 0, n - 1, inorder, 0, n - 1, nullptr);
    tree.postorder(tree.root);
    std::cout << std::endl;
    return 0;
}