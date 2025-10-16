#include <iostream>
#include "../../trees/binary_tree.hpp"

int main()
{
    bt::BinaryTree<int> t1;
    t1.root = new bt::Node<int>(1);
    t1.root->right = new bt::Node<int>(2);
    t1.root->right->right = new bt::Node<int>(3);
    t1.inorder(t1.root);
    std::cout << std::endl;

    bt::BinaryTree<int> t2;
    t2.root = new bt::Node<int>(1);
    t2.root->right = new bt::Node<int>(3);
    t2.root->right->left = new bt::Node<int>(2);
    t2.inorder(t2.root);
    std::cout << std::endl;

    bt::BinaryTree<int> t3;
    t3.root = new bt::Node<int>(2);
    t3.root->left = new bt::Node<int>(1);
    t3.root->right = new bt::Node<int>(3);
    t3.inorder(t3.root);
    std::cout << std::endl;

    bt::BinaryTree<int> t4;
    t4.root = new bt::Node<int>(3);
    t4.root->left = new bt::Node<int>(1);
    t4.root->left->right = new bt::Node<int>(2);
    t4.inorder(t4.root);
    std::cout << std::endl;

    bt::BinaryTree<int> t5;
    t5.root = new bt::Node<int>(3);
    t5.root->left = new bt::Node<int>(2);
    t5.root->left->left = new bt::Node<int>(1);
    t5.inorder(t5.root);
    std::cout << std::endl;

    return 0;
}