#include <iostream>
#include "../../trees/binary_tree.hpp"

int main()
{
    bt::BinaryTree<int> t1;
    t1.root = new bt::Node<int>(1);
    t1.root->left = new bt::Node<int>(2);
    t1.root->left->left = new bt::Node<int>(3);

    std::cout << "Tree 1 Preorder: ";
    t1.preorder(t1.root);
    std::cout << std::endl;

    std::cout << "Tree 1 Postorder: ";
    t1.postorder(t1.root);
    std::cout << std::endl;

    bt::BinaryTree<int> t2;
    t2.root = new bt::Node<int>(1);
    t2.root->left = new bt::Node<int>(2);
    t2.root->left->right = new bt::Node<int>(3);

    std::cout << "Tree 2 Preorder: ";
    t2.preorder(t2.root);
    std::cout << std::endl;

    std::cout << "Tree 2 Postorder: ";
    t2.postorder(t2.root);
    std::cout << std::endl;

    return 0;
}