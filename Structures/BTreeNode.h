//
//  BTreeNode.h
//  CIS22C_FinalProject
//
//  Created by Matan Broner on 11/29/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#ifndef BTreeNode_h
#define BTreeNode_h

template <typename T>
class BTreeNode
{
private:
    T values*; // array of values
    int minDegree; // minimum degree of tree (number of keys possible per Node)
    BTreeNode<T> **children; // array of child pointers
    int keyCount; // current amount of keys in Node
    bool leaf; // flag to tell whether Node is a leaf
public:
    
};

#endif /* BTreeNode_h */
