#include <iostream>
#include "../../trees/binary_search_tree.hpp"

bt::Node<int> *lca(bt::Node<int> *root, int a, int b)
{
    if (!root)
        return nullptr;
    if (root->key > a && root->key > b)
        return lca(root->left, a, b);
    if (root->key < a && root->key < b)
        return lca(root->right, a, b);
    return root;
}

int main()
{
    bst::BinarySearchTree<int> tree;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        tree.insert(x);
    }
    int u, v;
    std::cin >> u >> v;
    bt::Node<int> *ans = lca(tree.root, u, v);
    if (ans)
        std::cout << ans->key << std::endl;
    else
        std::cout << "No LCA" << std::endl;
    return 0;
}