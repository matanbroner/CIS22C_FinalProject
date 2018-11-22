

#ifndef BinaryTree_h
#define BinaryTree_h

#include "BSTNode.h"

template <typename T>
class BinarySearchTree
{
private:
    BSTNode<T>* rootNode = nullptr;
    int nodeCount = 0;
    
    BSTNode<T>* insertInternal(BSTNode<T>*, BSTNode<T>*);
    BSTNode<T>* removeInternal(BSTNode<T>*, BSTNode<T>*);
    BSTNode<T>* findNode(BSTNode<T>*, const T);
    BSTNode<T>* deleteNodeProperly(BSTNode<T>*);
    BSTNode<T>* deleteNodeWithTwoChildren(BSTNode<T>*, T);
    
    void processLevelOfTree(BSTNode<T>*, int, std::ofstream&);
    
public:
    bool insert(T&);
    bool remove(T&);
    
    BSTNode<T>* retrieveRootPointer();
    
    void preOrderTraversal(BSTNode<T>*, std::ofstream&);
    void postOrderTraversal(BSTNode<T>*, std::ofstream&);
    void inOrderTraversal(BSTNode<T>*, std::ofstream&);
    void breadthFirstTraversal(BSTNode<T>*, std::ofstream&);
    
    static int treeDepth(BSTNode<T>*);
    
};

/*
 Private Functions
 */

template <typename T>
BSTNode<T>* BinarySearchTree<T>::insertInternal(BSTNode<T>* rootNode, BSTNode<T>* newNode)
{
    if (rootNode == nullptr)
        return newNode;
    else
    {
        if (newNode->getData() < rootNode->getData())
            rootNode->setLeft(insertInternal(rootNode->getLeft(), newNode));
        else
            rootNode->setRight(insertInternal(rootNode->getRight(), newNode));
        return rootNode;
    }
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::removeInternal(BSTNode<T> *root, BSTNode<T> *nodeToRemove)
{
    if (root == nullptr)
        return root;
    if (nodeToRemove->getData() < root->getData())
        root->setLeft(removeInternal(root->getLeft(), nodeToRemove));
    else if (root->getData() < nodeToRemove->getData())
        root->setRight(removeInternal(root->getRight(), nodeToRemove));
    else
    {
        root = deleteNodeProperly(root); // we have found our node
    }
    return root;
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::findNode(BSTNode<T> *root, const T dataToFind)
{
    if (this->rootNode != nullptr)
    {
        if (root->getData() == dataToFind)
            return root;
        else if (!root->isLeafNode())
        {
            if (root->getData() < dataToFind)
                return (findNode(root->getRight(), dataToFind));
            else
                return (findNode(root->getLeft(), dataToFind));
        }
        else return nullptr;
    }
    else return this->rootNode;
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::deleteNodeProperly(BSTNode<T> *nodeToDelete)
{
    if (nodeToDelete->isLeafNode()) // no children
    {
        delete nodeToDelete;
        return nullptr;
    }
    else if (nodeToDelete->getLeft() == nullptr) // no left child
    {
        BSTNode<T>* replacingRootNode = nodeToDelete->getRight();
        delete nodeToDelete;
        return replacingRootNode;
    }
    else if (nodeToDelete->getRight() == nullptr) // no right child
    {
        BSTNode<T>* replacingRootNode = nodeToDelete->getLeft();
        delete nodeToDelete;
        return replacingRootNode;
    }
    else // two children, replace left child with right-most node in right subtree
    {
        T contentOfNewNode;
        nodeToDelete->setLeft(deleteNodeWithTwoChildren(nodeToDelete->getRight(), contentOfNewNode));
        nodeToDelete->setData(contentOfNewNode);
        return nodeToDelete;
    }
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::deleteNodeWithTwoChildren(BSTNode<T> *root, T newValue)
{
    if (root->getRight() == nullptr) // we have reached the rightmost node in the subtree
    {
        newValue = root->getData();
        return deleteNodeProperly(root);
    }
    else
    {
        // recursive fashion of traversal, use same method to move to next right node and see if it is the one we are looking for
        root->setRight(deleteNodeWithTwoChildren(root->getRight(), newValue));
        return root;
    }
}

/*
 Public Functions
 */

template<typename T>
bool BinarySearchTree<T>::insert(T& valueForNewNode)
{
    BSTNode<T>* newNode = new BSTNode<T>(valueForNewNode);
    this->rootNode = insertInternal(this->rootNode, newNode);
    newNode->setKey(this->nodeCount);
    this->nodeCount++;
    return true;
}

template <typename T>
bool BinarySearchTree<T>::remove(T& dataToRemove)
{
    BSTNode<T>* nodeToFind = findNode(this->rootNode, dataToRemove);
    if (nodeToFind != nullptr)
    {
        removeInternal(this->rootNode, nodeToFind);
        return true;
    }
    return false;
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::retrieveRootPointer()
{
    return this->rootNode;
}

template <typename T>
void BinarySearchTree<T>::preOrderTraversal(BSTNode<T>* rootNode, std::ofstream &outputFile)
{
    if (rootNode == nullptr)
        return;
    outputFile << rootNode->getData() << std::endl;
    preOrderTraversal(rootNode->getLeft(), outputFile);
    preOrderTraversal(rootNode->getRight(), outputFile);
}

template <typename T>
void BinarySearchTree<T>::postOrderTraversal(BSTNode<T>* rootNode, std::ofstream &outputFile)
{
    if (rootNode == nullptr)
        return;
    postOrderTraversal(rootNode->getLeft(), outputFile);
    postOrderTraversal(rootNode->getRight(), outputFile);
    outputFile << rootNode->getData() << std::endl;
}

template <typename T>
void BinarySearchTree<T>::inOrderTraversal(BSTNode<T>* rootNode, std::ofstream &outputFile)
{
    if (rootNode == nullptr)
        return;
    inOrderTraversal(rootNode->getLeft(), outputFile);
    outputFile << rootNode->getData() << std::endl;
    inOrderTraversal(rootNode->getRight(), outputFile);
}

template <typename T>
void BinarySearchTree<T>::breadthFirstTraversal(BSTNode<T>* rootNode, std::ofstream &outputFile)
{
    int heightOfTree = treeDepth(rootNode);
    for (int level = 1; level <= heightOfTree; level++)
        processLevelOfTree(rootNode, level, outputFile);
}

template <typename T>
void BinarySearchTree<T>::processLevelOfTree(BSTNode<T>* rootNode, int givenLevel, std::ofstream &outputFile)
{
    if (rootNode == nullptr)
        return;
    if (givenLevel == 1)
        outputFile << rootNode->getData() << std::endl;
    else if (givenLevel > 1)
    {
        processLevelOfTree(rootNode->getLeft(), givenLevel - 1, outputFile);
        processLevelOfTree(rootNode->getRight(), givenLevel - 1, outputFile);
    }
}

template <typename T>
int BinarySearchTree<T>::treeDepth(BSTNode<T>* rootNode)
{
    if (rootNode == nullptr)
        return 0;
    int leftSubtreeDepth = treeDepth(rootNode->getLeft());
    int rightSubtreeDepth = treeDepth(rootNode->getRight());
    
    if (leftSubtreeDepth > rightSubtreeDepth)
        return (leftSubtreeDepth + 1);
    else return (rightSubtreeDepth + 1);
}


#endif /* BinaryTree_h */
