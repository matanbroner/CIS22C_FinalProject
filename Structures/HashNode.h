/*
 Hash Node Class
 This class is intended to act as a node for a Hash Table structure.
 As such, the class contains a key of type string, which can be hashed. It also contains a templatized data value.
 The class has a boolean collision indicator to indicate if it caused a collision upon entry into the Hash Table.
 */

#ifndef HashNode_h
#define HashNode_h

#include "Node.h"

template <typename T>
class HashNode
{
private:
    std::string key;
    T data;
    bool collisionFlag = false; // true if caused collision
    
public:
    HashNode(T&, std::string); // data and key
    std::string getKey();
    T& getData();
    void setCollisionFlag(); // sets to true
    bool collision();
    
    void print();
};


template <typename T>
HashNode<T>::HashNode(T& givenData, std::string givenKey) : data(givenData)
{
    this->data = givenData;
    this->key = givenKey;
}

template <typename T>
std::string HashNode<T>::getKey()
{
    return this->key;
}

template <typename T>
T& HashNode<T>::getData()
{
    return this->data;
}

template <typename T>
void HashNode<T>::setCollisionFlag()
{
    this->collisionFlag = true;
}

template <typename T>
bool HashNode<T>::collision()
{
    return this->collisionFlag;
}

template <typename T>
void HashNode<T>::print()
{
    std::cout << "Key: " << this->key << " -- Data: " << this->data << std::endl;
}





#endif /* HashNode_h */
