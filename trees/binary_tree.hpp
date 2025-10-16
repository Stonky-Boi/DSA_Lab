#ifndef binary_tree
#define binary_tree

#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <algorithm>

namespace bt
{
    template <typename T>
    class Node
    {
    public:
        T key;
        Node<T> *left;
        Node<T> *right;
        Node<T> *parent;

        Node(const T &value)
        {
            key = value;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }
    };

    template <typename T>
    class BinaryTree
    {
    private:
        void destroy(Node<T> *node)
        {
            if (!node)
                return;
            destroy(node->left);
            destroy(node->right);
            delete node;
        }

        int check_balance(Node<T> *node)
        {
            if (!node)
                return 0;
            int lh = check_balance(node->left);
            if (lh == -1)
                return -1;
            int rh = check_balance(node->right);
            if (rh == -1)
                return -1;
            if (std::abs(lh - rh) > 1)
                return -1;
            return 1 + std::max(lh, rh);
        }

        int height_diameter(Node<T> *node, int &d)
        {
            if (!node)
                return 0;
            int lh = height_diameter(node->left, d);
            int rh = height_diameter(node->right, d);
            d = std::max(d, lh + rh);
            return 1 + std::max(lh, rh);
        }

        void serialize_helper(Node<T> *node, std::ostringstream &out)
        {
            if (!node)
            {
                out << "# ";
                return;
            }
            out << node->key << " ";
            serialize_helper(node->left, out);
            serialize_helper(node->right, out);
        }

        Node<T> *deserialize_helper(std::istringstream &in, Node<T> *parent)
        {
            std::string val;
            if (!(in >> val))
                return nullptr;
            if (val == "#")
                return nullptr;
            Node<T> *node = new Node<T>(static_cast<T>(std::stoi(val)));
            node->parent = parent;
            node->left = deserialize_helper(in, node);
            node->right = deserialize_helper(in, node);
            return node;
        }

    public:
        Node<T> *root;

        BinaryTree()
        {
            root = nullptr;
        }

        ~BinaryTree()
        {
            destroy(root);
        }

        void inorder(Node<T> *node)
        {
            if (!node)
                return;
            inorder(node->left);
            std::cout << node->key << " ";
            inorder(node->right);
        }

        void preorder(Node<T> *node)
        {
            if (!node)
                return;
            std::cout << node->key << " ";
            preorder(node->left);
            preorder(node->right);
        }

        void postorder(Node<T> *node)
        {
            if (!node)
                return;
            postorder(node->left);
            postorder(node->right);
            std::cout << node->key << " ";
        }

        int height(Node<T> *node)
        {
            if (!node)
                return -1;
            return 1 + std::max(height(node->left), height(node->right));
        }

        int depth(Node<T> *node)
        {
            int d = 0;
            while (node && node->parent)
            {
                d++;
                node = node->parent;
            }
            return d;
        }

        void level_order(Node<T> *node)
        {
            if (!node)
                return;
            std::queue<Node<T> *> q;
            q.push(node);
            while (!q.empty())
            {
                Node<T> *curr = q.front();
                q.pop();
                std::cout << curr->key << " ";
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
        }

        bool is_balanced(Node<T> *node)
        {
            return check_balance(node) != -1;
        }

        int count_leaves(Node<T> *node)
        {
            if (!node)
                return 0;
            if (!node->left && !node->right)
                return 1;
            return count_leaves(node->left) + count_leaves(node->right);
        }

        int diameter(Node<T> *node)
        {
            int d = 0;
            height_diameter(node, d);
            return d;
        }

        std::string serialize(Node<T> *node)
        {
            std::ostringstream out;
            serialize_helper(node, out);
            return out.str();
        }

        Node<T> *deserialize(const std::string &data)
        {
            std::istringstream in(data);
            return deserialize_helper(in, nullptr);
        }
    };
}

#endif