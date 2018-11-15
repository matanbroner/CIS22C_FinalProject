
#ifndef List_h
#define List_h
#include "Node.h"

template<typename T>
class List
{
private:
    int count = 0; // amount of nodes in the list
    Node<T>* head; // pointer to the first node in the list
    Node<T>* tail; // not used in the Linked List, but can be used in potential queue inheritance structures
    
public:
    List<T>(); // constructor
    int getCount(); // returns count
    
    /* This method accepts an integer based index and a data value of type T. It adds a new node to the given list with the given index and data value. (if possible)
     Pre: integer index, T type data
     Post: Given list + new node at given index with data value
     Return: none
     */
    void addAtPos(int index, T data);
    
    /* This method removes a node at a given integer based index and returns the data that was held in said node. (if possible)
     Pre: integer index
     Post: Given list - node at given index
     Return: data held at list index given (or NULL)
     */
    T deleteAnywhere(int index); // removes a node based on an integer based index
    
    /* This method take an integer based index and fetches the data held at index in the list (if possible)
     Pre: none
     Post: none
     Return: data member of list at index given (or NULL)
     */
    T getDataAtIndex(int i);
    
    /* This method accepts a data value of type T and parses the given list to find the pointer address at which it is held, and returns the address if found. If not found, it returns NULL.
     Pre: T type data
     Post: none
     Return: Node pointer at which data is held in list or NULL if not found
     */
    Node<T>* searchByData(T data);
    
    /* This method parses the entire list if head is not NULL, and deletes each node pointer. It then sets head to NULL to result in an empty list object.
     Pre: none
     Post: emptied list
     Return: none
     */
    void emptyListContents();
    
    /* This method parses through the list object if head is not set to NULL (ie. empty list) and rearranges the DATA values of each node to result in an ascending order of node data. It does NOT exchange pointers, rather only swaps data.
     Pre: none
     Post: List data is sorted in ascending order
     Return: none
     */
    void sortListAcsending();
    
    /* This method parses through the list object if head is not set to NULL (ie. empty list) and rearranges the DATA values of each node to result in an descending order of node data. It does NOT exchange pointers, rather only swaps data.
     Pre: none
     Post: List data is sorted in descending order
     Return: none
     */
    void sortListDecsending();
    
    /* This method accepts a data value of type T and creates a new node with this data. It then sets this node as the head node of the list appropriately.
     Pre: T data
     Post: Given list + new head node
     Return: none
     */
    
    /* This method is used to add nodes into a linked list which is meant to be sorted. The nodes are added in ascending order by value of their data.
     Pre: T data
     Post: List + new node in correctly ordered spot
     Return: none
     */
    void add(T data);
    
    void addAtHead(T data);
    
    /* This method accepts a data value of type T and creates a new node with this data. It then sets this node as the last node of the list appropriately, only if the list has one or more nodes already. Otherwise it calls the addAtHead method with the given data.
     Pre: T data
     Post: Given list + new tail node (or head node if list has 0 nodes)
     Return: none
     */
    void addAtTail(T data);
    
    /* This method removes the first (head) node in the list if one exists, and returns the data that was held in this node.
     Pre: none
     Post: List - head node (if possible)
     Return: T data held at head node or NULL
     */
    T deleteHead();
    
    /* This method removes the last (tail) node in the list if one exists, and returns the data that was held in this node.
     Pre: none
     Post: List - tail node (if possible)
     Return: T data held at head node or NULL
     */
    T deleteTail();
    
    /* This method parses the given list if it has one or more nodes, and prints the data held in each node
     Pre: none
     Post: none
     Return: none
     */
    void printList();
    void reverseList();
    
    ~List<T>(); // deletes all nodes and then the object
};

template<typename T>
List<T>::List()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

template<typename T>
int List<T>::getCount()
{
    return this->count;
}

template<typename T>
void List<T>::add(T data)
{
    Node<T>* newNode = new Node<T>; // new node to add to the list
    newNode->setData(data);
    Node<T>* temp = this->head;
    if (this->count >= 1) // if at least a head exists in the list
    {
        while (temp->getNext() != nullptr) // while we are at before the tail
        {
            if (temp->getNext()->getData() <= data) // if the data we are pointing to is less than the added data
                temp = temp->getNext(); // move to next node
            else break; // if not stop parsing
        }
        if (this->count == 1 && data < temp->getData()) // if only a head node is present and its data is greater than the data we are adding
        {
            newNode->setNext(temp); // switch their positions
            this->head = newNode;
        }
        else{
            newNode->setNext(temp->getNext()); // place the new node in the found spot
            temp->setNext(newNode);
        }
        count++;
    }
    else this->addAtHead(data); // if not set the new node as the head (includes count++)
}

template<typename T>
void List<T>::addAtPos(int index, T data)
{
    if (index >= this->getCount() || index < 0) // if index given is not within acceptable range
    {
        if (index == this->getCount()) // if user is attempting to add node at one after last node in list
        {
            this->addAtTail(data); // method calls the method to add the node at the tail
        }
        else
            throw std::out_of_range("invalid index"); // error message
        return;
    }
   
    if (index == 0) // add at head
    {
        this->addAtHead(data);
    }
    
    
    else
    {
        Node<T>* newNode = new Node<T>; // creates new node with given data which will serve as the new node in the list
        newNode->setData(data);
        
        Node<T>* tempPtr = this->head; // retrieve address of first node in the list
        while(index > 2) // to best add new node, tempPtr should point to the node before the pos. at which we want to add
        {
            tempPtr = tempPtr->getNext(); // parse to the next node
            index--;
        }
        if (tempPtr->getNext() != nullptr) // backup check to ensure that the new node won't point to NULL
        {
            newNode->setNext(tempPtr->getNext()); // new node will replace tempPtr in the chain
            tempPtr->setNext(newNode); // tempPtr will now point to new node instead
            this->count++;
        }

    }
}

template<typename T>
void List<T>::addAtHead(T data)
{
    Node<T>* newNode = new Node<T>; // creates new node pointer with given data to serve as new head node
    newNode->setData(data);
   
    newNode->setNext(this->head); // new node will replace the current head in the chain
    this->head = newNode; // new node is now acting as the list head
    this->count++;
}

template<typename T>
void List<T>::addAtTail(T data)
{
    Node<T>* newNode = new Node<T>; // creates new node pointer with given data to serve as new head node
    newNode->setData(data);
    newNode->setNext(nullptr); // new node will act as the tail, hence its next node should be NULL

    if (this->head != nullptr) // if there is at least one node in the list already
    {
        Node<T>* tempPtr = head; // retrieve address of current head
        while(tempPtr->getNext() != nullptr) // parse until we reach tail (tail's next pointer is NULL)
        {
            tempPtr = tempPtr->getNext(); // parse to next node
        }
        tempPtr->setNext(newNode); // adds new node to right after the last node
    }
    else this->head = newNode; // if no nodes present, sets the new node as he head (essentially making it both the head and the tail)
    this->count++;
}

template<typename T>
T List<T>::deleteHead()
{
    if (this->head) // if a head is present
    {
        Node<T>* tempPtr = this->head;
        T tempData = tempPtr->getData(); // holds the data member held in the head node
        this->head = tempPtr->getNext(); // sets hea pointer to one after the current head
        this->count--;
        delete tempPtr; // deletes head
        if (this->count == 0)
            this->head = nullptr;
        return tempData;
    }
    throw std::out_of_range("invalid deletion"); // if no head present, program cannot fetch it and returns NULL
}

template<typename T>
T List<T>::deleteTail()
{
    if (this->head && this->count > 1) // if a head + 1 or more nodes list is given
    {
        Node<T>* curr = this->head;
        Node<T>* prev = nullptr;
        while(curr->getNext()) // while the list tail is not reached
        {
            prev = curr; // holds the current pointer address
            curr = curr->getNext(); // parses the current pointer to the next one
        }
        prev->setNext(nullptr); // prev pointer is now the tail
        this->count--;
        T temp = curr->getData(); // holds data member of former tail
        delete curr; // deletes former tail
        return temp;
    }
    else {return this->deleteHead();} // if 1 pointer list given, deleteHead is more appropriate
    throw std::out_of_range("invalid deletion");
}

template<typename T>
T List<T>::deleteAnywhere(int index)
{
    if (index < 0 || index > this->getCount() - 1) // if index given is not in acceptable range
    {
        throw std::out_of_range("invalid deletion");
    }
    if (index == 0) // if head is called to be deleted
        return this->deleteHead();
    else if (index >= this->getCount() - 1) // if tail is called to be deleted
        return this->deleteTail();
    else
    {
        Node<T>* curr = this->head;
        Node<T>* prev = nullptr;
        while(index > 0) // parses the list, holding the current pointer and the one before it
        {
            prev = curr;
            curr = curr->getNext();
            index--; // deincrements the iterator
        }
        prev->setNext(curr->getNext()); // sets the previous node's next pointer to the one after the one to be deleted
        this->count--;
        T temp = curr->getData(); // holds data member of deleted node
        delete curr; // deletes the pointer
        return temp;
    }
}

template<typename T>
T List<T>::getDataAtIndex(int i)
{
    Node<T>* tempPtr = this->head;
    while(tempPtr != nullptr) // ensures tempPtr does not move past list
    {
        if (i == 0)
            return tempPtr->getData();
        i--;
        tempPtr = tempPtr->getNext(); // moves to next node pointer
    }
    throw std::out_of_range("invalid index");
}

template<typename T>
Node<T>* List<T>::searchByData(T data)
{
    Node<T>* tempPtr = this->head; // pointer to be used to find data in list
    while(tempPtr->getNext()) // parses through the list
    {
        if (tempPtr->getData() == data) // if data member at current node is the one being searched for
            return tempPtr;
        tempPtr = tempPtr->getNext(); // moves to next node
    }
    std::cout << "Data not contained in list, returning head" << std::endl; // if not found, returns head address
    return -1;
}

template<typename T>
void List<T>::emptyListContents()
{
    while (this->head)
    {
        this->deleteHead();
    }
}

template<typename T>
void List<T>::sortListAcsending()
{
    if (this->head != nullptr)
    {
        for (Node<T> *index = this->head; index->getNext() != nullptr; index = index->getNext())
        {
            for (Node<T> *selection = index->getNext(); selection != nullptr; selection = selection->getNext())
            {
                if (index->getData() > selection->getData())
                {
                    T tempData = index->getData();
                    index->setData(selection->getData());
                    selection->setData(tempData);
                }
            }
        }
    }

}

template<typename T>
void List<T>::sortListDecsending()
{
    if (this->head != nullptr)
    {
        for (Node<T> *index = this->head; index->getNext() != nullptr; index = index->getNext())
        {
            for (Node<T> *selection = index->getNext(); selection != nullptr; selection = selection->getNext())
            {
                if (index->getData() < selection->getData())
                {
                    T tempData = index->getData();
                    index->setData(selection->getData());
                    selection->setData(tempData);
                }
            }
        }
    }
}

template <typename T>
void List<T>::printList()
{
    if (this->head != nullptr) // if list has at least one pointer
    {
        Node<T>* readPtr = this->head;
        while(readPtr) // while the node not set past tail
        {
            std::cout << readPtr->getData(); // prints the data member
            readPtr = readPtr->getNext(); // moves to next pointer
        }
    }
    std::cout << std::endl;
}

template <typename T>
void List<T>::reverseList()
{
    List<T> temp;
    while (this->getCount() >= 1)
    {
        temp.addAtTail(this->deleteTail());
    }
    while (temp.getCount() >= 1)
    {
        this->addAtTail(temp.deleteHead());
    }
}

template <typename T>
List<T>::~List<T>()
{
    this->emptyListContents(); // deletes all the nodes in the list
}




#endif /* List_h */
