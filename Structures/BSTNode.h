/*
 BST Node class
 ==============
 This class serves to act as a Node in a Binary Search Tree.
 It as such has two pointer varaibles to children nodes in the tree.
 It  can print data it is holding and provide manipulation of children nodes.
 */
#ifndef BSTNode_h
#define BSTNode_h

#include "Node.h"

template <typename T>
class BSTNode : public Node<T>
{
private:
    int key;
    BSTNode<T> *right; // right child node
    BSTNode<T> *left; // left child node
    
public:
    BSTNode<T>(T);
    void setLeft(BSTNode*);
    void setRight(BSTNode*);
    void setKey(int);
    
    BSTNode<T>* getLeft();
    BSTNode<T>* getRight();
    int getKey();
    
    bool isLeafNode(); // has no children (ie. left and right children are NULL)
};

template <typename T>
BSTNode<T>::BSTNode(T data) : Node<T>(data)
{
    this->left = nullptr;
    this->right = nullptr;
}

template <typename T>
void BSTNode<T>::setLeft(BSTNode<T> *ptr)
{
    this->left = ptr;
}

template <typename T>
void BSTNode<T>::setRight(BSTNode<T> *ptr)
{
    this->right = ptr;
}

template <typename T>
void BSTNode<T>::setKey(int number)
{
    this->key = number;
}

template <typename T>
BSTNode<T>* BSTNode<T>::getLeft()
{
    return this->left;
}

template <typename T>
BSTNode<T>* BSTNode<T>::getRight()
{
    return this->right;
}

template <typename T>
int BSTNode<T>::getKey()
{
    return this->key;
}

template <typename T>
bool BSTNode<T>::isLeafNode()
{
    return (this->left == nullptr && this->right == nullptr);
}
#endif /* BSTNode_h */
