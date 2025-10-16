#ifndef binary_search_tree
#define binary_search_tree

#include "binary_tree.hpp"

namespace bst
{
    template <typename T>
    class BinarySearchTree : public bt::BinaryTree<T>
    {
    public:
        bt::Node<T> *search(bt::Node<T> *node, const T &key)
        {
            if (!node || node->key == key)
                return node;
            if (key < node->key)
                return search(node->left, key);
            return search(node->right, key);
        }

        void insert(const T &key)
        {
            bt::Node<T> *node = new bt::Node<T>(key);
            if (!this->root)
            {
                this->root = node;
                return;
            }
            bt::Node<T> *curr = this->root;
            bt::Node<T> *parent = nullptr;
            while (curr)
            {
                parent = curr;
                if (key < curr->key)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            node->parent = parent;
            if (key < parent->key)
                parent->left = node;
            else
                parent->right = node;
        }

        void remove(const T &key)
        {
            this->root = remove_helper(this->root, key);
        }

        bt::Node<T> *min_node(bt::Node<T> *node)
        {
            while (node && node->left)
                node = node->left;
            return node;
        }

        bt::Node<T> *max_node(bt::Node<T> *node)
        {
            while (node && node->right)
                node = node->right;
            return node;
        }

        bool is_bst()
        {
            std::vector<T> vals;
            collect_inorder(this->root, vals);
            return std::is_sorted(vals.begin(), vals.end());
        }

        bt::Node<T> *inorder_successor(bt::Node<T> *node)
        {
            if (node->right)
                return min_node(node->right);
            bt::Node<T> *p = node->parent;
            while (p && node == p->right)
            {
                node = p;
                p = p->parent;
            }
            return p;
        }

    private:
        bt::Node<T> *remove_helper(bt::Node<T> *node, const T &key)
        {
            if (!node)
                return node;
            if (key < node->key)
                node->left = remove_helper(node->left, key);
            else if (key > node->key)
                node->right = remove_helper(node->right, key);
            else
            {
                if (!node->left)
                {
                    bt::Node<T> *r = node->right;
                    if (r)
                        r->parent = node->parent;
                    delete node;
                    return r;
                }
                else if (!node->right)
                {
                    bt::Node<T> *l = node->left;
                    if (l)
                        l->parent = node->parent;
                    delete node;
                    return l;
                }
                bt::Node<T> *succ = min_node(node->right);
                node->key = succ->key;
                node->right = remove_helper(node->right, succ->key);
            }
            return node;
        }

        void collect_inorder(bt::Node<T> *node, std::vector<T> &vals)
        {
            if (!node)
                return;
            collect_inorder(node->left, vals);
            vals.push_back(node->key);
            collect_inorder(node->right, vals);
        }
    };
}

#endif