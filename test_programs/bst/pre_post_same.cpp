#include <iostream>
#include "../../trees/binary_tree.hpp"

int main()
{
    bt::BinaryTree<int> t1;
    t1.root = new bt::Node<int>(1);
    t1.root->left = new bt::Node<int>(2);
    t1.root->right = new bt::Node<int>(3);
    t1.preorder(t1.root);
    std::cout << std::endl;
    t1.postorder(t1.root);
    std::cout << std::endl;

    bt::BinaryTree<int> t2;
    t2.root = new bt::Node<int>(1);
    t2.root->left = new bt::Node<int>(2);
    t2.root->left->right = new bt::Node<int>(3);
    t2.preorder(t2.root);
    std::cout << std::endl;
    t2.postorder(t2.root);
    std::cout << std::endl;

    return 0;
}