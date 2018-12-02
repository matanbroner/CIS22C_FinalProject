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
public:
    static void printBinarySearchTree(BinarySearchTree<T>&);
};


template <typename T>
void StructurePrinter<T>::printBinarySearchTree(BinarySearchTree<T> &tree)
{
    std::cout << "*** INDENTED BST GOES HERE! ***" << std::endl;
}


#endif /* StructurePrinter_h */
