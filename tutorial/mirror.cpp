#include <iostream>
using namespace std;

struct Node
{
    int v;
    Node* l;
    Node* r;
};

void mirror(Node* node)
{
    if (node == nullptr)
        return;

    Node* temp = node->l;
    node->l = node->r;
    node->r = temp;

    mirror(node->l);
    mirror(node->r);
}

void inorder(Node* node)
{
    if (node == nullptr)
        return;

    inorder(node->l);
    cout << node->v << " ";
    inorder(node->r);
}

int main()
{
    Node *node = new Node(), *nodeL = new Node(), *nodeR = new Node(),
         *nodeLL = new Node(), *nodeLR = new Node(), *nodeRL = new Node(), *nodeRR = new Node(),
         *nodeLLL = new Node(), *nodeLLR = new Node(), *nodeLRL = new Node(), *nodeLRR = new Node();

    node->v = 10;
    node->l = nodeL;
    node->r = nodeR;

    nodeL->v = 6;
    nodeL->l = nodeLL;
    nodeL->r = nodeLR;

    nodeR->v = 15;
    nodeR->l = nodeRL;
    nodeR->r = nodeRR;

    nodeLL->v = 3;
    nodeLL->l = nodeLLL;
    nodeLL->r = nodeLLR;

    nodeLR->v = 8;
    nodeLR->l = nodeLRL;
    nodeLR->r = nodeLRR;

    nodeRL->v = 12;
    nodeRL->l = nullptr;
    nodeRL->r = nullptr;

    nodeRR->v = 18;
    nodeRR->l = nullptr;
    nodeRR->r = nullptr;

    nodeLLL->v = 1;
    nodeLLL->l = nullptr;
    nodeLLL->r = nullptr;

    nodeLLR->v = 5;
    nodeLLR->l = nullptr;
    nodeLLR->r = nullptr;

    nodeLRL->v = 7;
    nodeLRL->l = nullptr;
    nodeLRL->r = nullptr;

    nodeLRR->v = 9;
    nodeLRR->l = nullptr;
    nodeLRR->r = nullptr;

    cout << "Original tree inorder: ";
    inorder(node);
    cout << endl;

    mirror(node);

    cout << "Mirrored tree inorder: ";
    inorder(node);
    cout << endl;

    return 0;
}