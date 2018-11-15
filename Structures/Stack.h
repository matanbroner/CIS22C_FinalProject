
#ifndef Stack_h
#define Stack_h
#include "List.h"

template <typename T>
class Stack : private List<T>
{
public:
    void push(T data); // adds new node to tail
    T pop(); // removes node from tail
    
    /* This method returns true is the stack has no nodes, and false otherwise
     Pre: none
     Post: none
     Return: true or false
     */
    bool isEmpty();
    
    void sortStackAscending(); // uses the List object's sort ascending order function
    void sortStackDescending(); // uses the List object's sort descending order function
    T rear();
    void printStack();
    int getStackCount();
    void emptyStackContents();
    void reverseStack();
    
    
    ~Stack<T>(); // deletes all nodes in stack and then object itself
};

template <typename T>
void Stack<T>::push(T data)
{
    this->addAtTail(data); // adds new node at tail using List method
}

template <typename T>
T Stack<T>::pop()
{
    return this->deleteTail(); // deletes the tail node using List method and returns the data member of deleted node
}

template <typename T>
bool Stack<T>::isEmpty()
{
    if (this->getCount() > 0) // if 1 or more nodes in stack
        return false;
    else return true; // stack is empty
}

template <typename T>
void Stack<T>::sortStackAscending()
{
    this->sortListAcsending(); // uses the List method to sort nodes in ascending order
}

template <typename T>
void Stack<T>::sortStackDescending()
{
    this->sortListDecsending(); // uses the List method to sort nodes in descending order
}


template <typename T>
Stack<T>::~Stack<T>()
{
    this->emptyListContents();
}

template <typename T>
T Stack<T>::rear()
{
    return this->getDataAtIndex(this->getCount()-1);
}

template <typename T>
void Stack<T>::printStack()
{
    this->printList();
}

template <typename T>
int Stack<T>::getStackCount()
{
    return this->getCount();
}

template <typename T>
void Stack<T>::emptyStackContents()
{
    this->emptyListContents();
}


template<typename T>
void Stack<T>::reverseStack()
{
    this->reverseList();
}


#endif /* Stack_h */
