#include <iostream>
#include "../../trees/binary_search_tree.hpp"

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
    tree.inorder(tree.root);
    std::cout << std::endl;
    tree.level_order(tree.root);
    std::cout << std::endl;
    std::cout << "Height: " << tree.height(tree.root) << std::endl;
    std::cout << "Depth of root: " << tree.depth(tree.root) << std::endl;
    int key;
    std::cin >> key;
    bt::Node<int> *node = tree.search(tree.root, key);
    if (node)
        std::cout << "Found: " << node->key << std::endl;
    else
        std::cout << "Not found" << std::endl;
    std::cin >> key;
    tree.remove(key);
    tree.inorder(tree.root);
    std::cout << std::endl;
    return 0;
}