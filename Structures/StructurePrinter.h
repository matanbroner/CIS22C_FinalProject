//
//  StructurePrinter.h
//  CIS22C_FinalProject
//
//  Created by Matan Broner on 11/30/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#ifndef StructurePrinter_h
#define StructurePrinter_h

#include "BinarySearchTree.h"
#include "List.h"

template <typename T>
class StructurePrinter
{
private:
	/*
	 BST Printing Related
	 */
	static void _printBST(std::string, BSTNode<T>*, bool);
public:
	static void printBinarySearchTree(BinarySearchTree<T>&);
};

/*
 BST Printing Related
 */
template <typename T>
void StructurePrinter<T>::_printBST(std::string fixed, BSTNode<T> *node, bool isLeftNode)
{
	if (node != nullptr)
	{
		std::cout << fixed;

		std::wcout << (isLeftNode ? "|==" : "\==");

		// print the value of the node
		std::cout << node->getData() << std::endl;

		// enter the next tree level - left and right branch
		_printBST(fixed + (isLeftNode ? "|   " : "    "), node->getLeft(), true);
		_printBST(fixed + (isLeftNode ? "|   " : "    "), node->getRight(), false);
	}
}

template <typename T>
void StructurePrinter<T>::printBinarySearchTree(BinarySearchTree<T> &tree)
{
	_printBST("", tree.retrieveRootPointer(), false);
}


#endif /* StructurePrinter_h */#pragma once
