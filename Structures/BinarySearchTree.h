/*
 Binary Search Tree class
 ========================
 This class serves to function as a Binary Search Tree structure.
 This means that a single root node lies at the top, and every subsequent node can have at most two node children.
 When adding, larger values trend to the right, and lesser values trend to the left of a given node.
 */

#ifndef BinaryTree_h
#define BinaryTree_h

#include "BSTNode.h"

template <typename T>
class BinarySearchTree
{
private:
	BSTNode<T>* rootNode = nullptr; // root BSTNode of the tree
	int nodeCount = 0; // amount of BSTNodes in the tree

	// Finds correct place for the new BSTNode with given root
	BSTNode<T>* insertInternal(BSTNode<T>*, BSTNode<T>*);
	// Find correct place to delete BSTNode with given root
	BSTNode<T>* removeInternal(BSTNode<T>*, BSTNode<T>*);
	// Traverses the BST with a given search value using a Binary Search method
	BSTNode<T>* findNode(BSTNode<T>*, T&);
	// Finds the correct BSTNode to replace the one being deleted, and deletes the given BSTNode
	BSTNode<T>* deleteNodeProperly(BSTNode<T>*);
	// Correctly reorganizes the tree to accomodate deletion of BSTNode with left and right active pointers
	BSTNode<T>* deleteNodeWithTwoChildren(BSTNode<T>*, T&);
	// traverses a horizontal level of a BST and uses a given output file stream to write the level to a file (Breadth First Traversal)
	void processLevelOfTree(BSTNode<T>*, int, std::ofstream&);

public:

	/*
	 This method takes a template value and creates a new BSTNode with the given value. It then calls the internal insert method to find the correct place for the node in the tree.
	 Pre: T&
	 Post: tree contains node with given value
	 Return: true if succesful
	 */
	bool insert(T&);

	/*
	 This method takes a template value and removes a BSTNode with the given value if found. It then calls the internal remove method to find the correct place of the node in the tree, and deletes it.
	 Pre: T&
	 Post: tree will not contain the node with given value
	 Return: true if node was found and removed
	 */
	bool remove(T&);

	/*
	 This method returns the pointer address of the root node in the BST
	 Pre: none
	 Post: none
	 Return: BSTNode Pointer
	 */
	BSTNode<T>* retrieveRootPointer();

	/*
	 This method prints a preorder traversal (root, left, right) of the BST to a given output file stream
	 Pre: root pointer, output file stream
	 Post: file is appended
	 Return: none
	 */
	void preOrderTraversal(BSTNode<T>*, std::ofstream&);

	/*
	 This method prints a postorder traversal (left, right, root) of the BST to a given output file stream
	 Pre: root pointer, output file stream
	 Post: file is appended
	 Return: none
	 */
	void postOrderTraversal(BSTNode<T>*, std::ofstream&);

	/*
	 This method prints a inorder traversal (left, root, right) of the BST to a given output file stream
	 Pre: root pointer, output file stream
	 Post: file is appended
	 Return: none
	 */
	void inOrderTraversal(BSTNode<T>*, std::ofstream&);

	/*
	 This method prints a traversal by breadth (horizontal levels starting at the root) of the BST to a given output file stream
	 Pre: root pointer, output file stream
	 Post: file is appended
	 Return: none
	 */
	void breadthFirstTraversal(BSTNode<T>*, std::ofstream&);

	/*
	 This method takes a given value of a template variable, and if found assigns the value found in the tree to the given template
	 variable address. This is meant to allow finding the correct variable for modification.
	 Pre: T, T&
	 Post: If value is found in the tree, address variable now contains the found data
	 Return: true if found, false if not
	 */
	bool findForModification(T, T&);

	/*
	 This method finds the number of horizontal levels in the tree from root to the deepest node
	 Pre: root pointer
	 Post: none
	 Return: integer based depth
	 */
	static int treeDepth(BSTNode<T>*);

	/*
	 This method prints an indented binary search tree in the console of the given tree to show parent - child relationships
	 between BSTNodes.
	 Pre: root pointer, level to start from (use 0 if using root of tree)
	 Post: tree prints to console
	 Return: none
	 */
	void printTree(BSTNode<T>*, int);


	~BinarySearchTree(); // deletes all BSTNode pointers allocated
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
BSTNode<T>* BinarySearchTree<T>::findNode(BSTNode<T> *root, T& dataToFind)
{
	if (root != nullptr)
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
	else return root;
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::deleteNodeProperly(BSTNode<T> *nodeToDelete)
{
	if (nodeToDelete->isLeafNode()) // no children
	{
		delete nodeToDelete;
		nodeToDelete = nullptr;
		return nullptr;
	}
	else if (nodeToDelete->getLeft() == nullptr) // no left child
	{
		BSTNode<T>* replacingRootNode = nodeToDelete->getRight();
		delete nodeToDelete;
		nodeToDelete = nullptr;
		return replacingRootNode;
	}
	else if (nodeToDelete->getRight() == nullptr) // no right child
	{
		BSTNode<T>* replacingRootNode = nodeToDelete->getLeft();
		delete nodeToDelete;
		nodeToDelete = nullptr;
		return replacingRootNode;
	}
	else // two children, replace left child with right-most node in right subtree
	{
		T contentOfNewNode;
		nodeToDelete->setRight(deleteNodeWithTwoChildren(nodeToDelete->getRight(), contentOfNewNode));
		nodeToDelete->setData(contentOfNewNode);
		return nodeToDelete;
	}
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::deleteNodeWithTwoChildren(BSTNode<T> *root, T& newValue)
{
	if (root->getLeft() == nullptr) // we have reached the rightmost node in the subtree
	{
		newValue = root->getData();
		return deleteNodeProperly(root);
	}
	else
	{
		// recursive fashion of traversal, use same method to move to next right node and see if it is the one we are looking for
		root->setLeft(deleteNodeWithTwoChildren(root->getLeft(), newValue));
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
		this->nodeCount--;
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

template <typename T>
bool BinarySearchTree<T>::findForModification(T searchValue, T& returnValue)
{
	BSTNode<T>* testerNode;
	testerNode = findNode(this->rootNode, searchValue);
	if (testerNode != nullptr)
	{
		returnValue = testerNode->getData();
		return true;
	}
	else return false;
}

template <typename T>
void BinarySearchTree<T>::printTree(BSTNode<T> *root, int depth)
{
	if (root == nullptr)
		return;

	printTree(root->getRight(), depth + 1);
	std::cout << std::string(depth, ' ') << root->getData() << std::endl;
	printTree(root->getLeft(), depth + 1);
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree<T>()
{
	while (this->rootNode != nullptr)
		this->rootNode = this->deleteNodeProperly(this->rootNode);
}


#endif /* BinaryTree_h */#pragma once
