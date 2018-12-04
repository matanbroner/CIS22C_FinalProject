#ifndef Node_h
#define Node_h

template<typename T>
class Node
{
private:
    T* data; // data held by the node
    Node<T> *pNode; // pointer to the next node in the structure
public:
    Node<T>(T&);
    void setData(T& dataAdd); // assigns to the data attribute
    T& getData(); // returns data
    void setNext(Node<T> *ptr); // assigns the pnode attribute
    Node<T>* getNext(); // returns pnode address
    ~Node();
};

template<typename T>
Node<T>::Node(T& content) : pNode(nullptr)
{
    this->data = new T(content);
}

template<typename T>
void Node<T>::setData(T& dataAdd)
{
    delete this->data;
    this->data = new T(dataAdd);
}

template<typename T>
T& Node<T>::getData()
{
    return *this->data;
}

template<typename T>
void Node<T>::setNext(Node<T> *ptr)
{
    this->pNode = ptr; // sets pointer after this to the given pointer (ptr)
}

template<typename T>
Node<T>* Node<T>::getNext()
{
    return this->pNode; // returns the address of pointer to node after this
}

template <typename T>
Node<T>::~Node<T>()
{delete this->data;}

#endif /* Node_h */
