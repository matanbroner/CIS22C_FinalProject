//
//  Queue.h
//  CIS22C_Lab2
//
//  Created by Matan Broner on 10/16/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#ifndef Queue_h
#define Queue_h
#include "List.h"

template<typename T>
class Queue : private List<T>
{
private:
    
public:
    void enqueue(T data);
    T dequeue();
    T front();
    T rear();
    
    void printQueue();
    bool queueEmpty();
    void emptyQueueContents();
    
    void reverseQueue();
    
    ~Queue<T>();
};

template<typename T>
T Queue<T>::dequeue()
{
    return this->deleteHead();
}

template<typename T>
void Queue<T>::enqueue(T data)
{
    this->addAtTail(data);
}

template<typename T>
T Queue<T>::front()
{
    return this->getDataAtIndex(0);
}

template<typename T>
T Queue<T>::rear()
{
    return this->getDataAtIndex(this->getCount()-1);
}

template<typename T>
void Queue<T>::printQueue()
{
    this->printList();
}

template<typename T>
bool Queue<T>::queueEmpty()
{
    if (this->getCount() == 0)
        return true;
    else return false;
}

template<typename T>
void Queue<T>::emptyQueueContents()
{
    this->emptyListContents();
}

template<typename T>
void Queue<T>::reverseQueue()
{
    this->reverseList();
}

template<typename T>
Queue<T>::~Queue<T>()
{
    this->emptyQueueContents();
}
#endif /* Queue_h */
