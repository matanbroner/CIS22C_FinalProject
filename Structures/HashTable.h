/*
 Hash Table Class
 This class implements a common Hash Table structure using a dynamically created array of a template type.
 Most functionality in the class can be used for any data, but the hashing mechanism MUST be evaluated for its usefulness for each data type a user may use. This is especially important for a UDT.
 
 Functions that need to be ammended due to unique hasing functions:
 1. insert
 2. search
 */

#ifndef HashTable_h
#define HashTable_h
#include <iomanip>
#include "HashNode.h"
#include "StringAssistant.h"
#include "BinarySearchTree.h"
#include "List.h"


const double SIMILIARITY_METRIC = 0.75;

template <typename T>
class HashTable
{
private:
    HashNode<T> **dataTable; // holds the HashNode pointers
    const int size = 300; // maximum entries the table can hold
    int count = 0, collisions = 0, attempts = 0;
    // current entries, number of collisions that have occured, and attmepted insertions into the table
    double loadFactor = 0; // percentage of table filled
    List<std::string> keyList;
    void sortKeyListBySimilarity(std::string, int n);
    bool createPotentialMatches(std::string&);
    
public:
    HashTable(); // Constructor
    
    /*
     This method takes a template type value and a key, and using a hash function it finds a place for the given value as a new node in the table. Hash function in this case is based on type Person, and if data changes, user must ensure that an alternative hash function is used.
     Pre: T value, string
     Post: Data is inserted into the table
     Return: true if inserted
     */
    bool insert(T, std::string);
    bool insertFood(Food, std::string);
    
    /*
     This method is used to find an alternative index for a value to be inserted if the index found according to the user defined hash function has yielded an occupied index. It continually adds a step value squared and modulo's the entire value by the size of the table. If the value is occupied it does so continually, until a free spot is found.
     Pre: index
     Post: none
     Return: unoccupied index
     */
    int quadraticProbe(int);
    
    /*
     This method takes a string key value and searches the table for it's hashed value. If the value is found, the node at this index is removed. Otherwise, the function returns false, indicating the value is not present in the table.
     Pre: string
     Post: if found, data with given key removed
     Return: true if removed, false if not
     */
    bool remove(std::string);
    
    /*
     This method takes a string key value and searches the table for it's hashed value. The method will continually perform quadratic probing on the hashed key for as many times as there are entries in the table. If the key is found at a hashed index, the key is returned, otherwise -1 is returned to symbolize not found.
     Pre: string
     Post: none
     Return: index is found, -1 if not
     */
    int searchFood(std::string);
    int search(std::string);
    int getCount(); // returns the amount of entries in the table (ie. count)
    T operator[](int); // allows user to treat table as an array by using bracketed index notation
    
    /*
     This method calculates the table's load factor. This value is the percentage of spots in the table that are occupied.
     Pre: none
     Post: none
     Return: percentage value
     */
    double calcLoadFactor();
    
    bool isFull(); // returns true if all spaces in table are occupied
    
    void displayTable(); // displays table with key - value pairs, and collision information for each pair
    void stats(); // diplays table size, load factor, collisions, and entries succesfully performed
    bool allIndexNull(); // returns true if all indeces of the table are set to nullptr
    
    ~HashTable();
};

/*
 Public Functions
 */

template <typename T>
HashTable<T>::HashTable()
{
    this->dataTable = new HashNode<T>*[size]{0}; // dynamic table with max size
}

template <typename T>
bool HashTable<T>::allIndexNull()
{
    for (int i = 0; i < size; i++)
        if (this->dataTable[i] != nullptr)
            return false;
    return true;
}

template <typename T>
int HashTable<T>::getCount()
{return this->count;}

template <typename T>
bool HashTable<T>::insert(T value, std::string givenKey)
{
    this->keyList.add(givenKey);
    this->attempts++; // attempts always increased to show if attempts are failed
    bool inserted = false;
    if (this->isFull())
        return inserted;
    
    HashNode<Food>* tempNode = new HashNode<Food>(value, givenKey); // create temporary node
    int hashKey = StringAssistant::hasher(givenKey); // Person type specific hashing function
    if (this->dataTable[hashKey] == nullptr) // if initial hash index is not occupied
    {
        this->dataTable[hashKey] = tempNode; // insert the node
        this->count++;
        inserted = true;
        return inserted;
    }
    else // a collision has occured
    {
        this->collisions++;
        tempNode->setCollisionFlag(); // nodes hold the knowledge that they have caused a collision
        hashKey = quadraticProbe(hashKey); // quadratic probe until empty spot found
        this->dataTable[hashKey] = tempNode; // insert the node
        this->count++;
        inserted = true;
    }
    return inserted;
}

template <>
bool HashTable<Food>::insertFood(Food value, std::string givenKey)
{
    this->keyList.add(givenKey);
    this->attempts++; // attempts always increased to show if attempts are failed
    bool inserted = false;
    if (this->isFull())
        return inserted;
    
    HashNode<Food>* tempNode = new HashNode<Food>(value, givenKey); // create temporary node
    int hashKey = StringAssistant::hashStringName(givenKey); // Person type specific hashing function
    if (this->dataTable[hashKey] == nullptr) // if initial hash index is not occupied
    {
        this->dataTable[hashKey] = tempNode; // insert the node
        this->count++;
        inserted = true;
        return inserted;
    }
    else // a collision has occured
    {
        this->collisions++;
        tempNode->setCollisionFlag(); // nodes hold the knowledge that they have caused a collision
        hashKey = quadraticProbe(hashKey); // quadratic probe until empty spot found
        this->dataTable[hashKey] = tempNode; // insert the node
        this->count++;
        inserted = true;
    }
    return inserted;
}

template <typename T>
int HashTable<T>::quadraticProbe(int index)
{
    int step = 1;
    for (; this->dataTable[index] != nullptr; step++) // while the spots visited are occupied
    {
        index = (index + (step * step)) % this->size; // (ex. index 6: (6 + (2 * 2)) % 20 = 10)
    }
    return index;
}

template <>
void HashTable<Food>::sortKeyListBySimilarity(std::string word, int listCount)
{
    // Implements a classic bubble sort
    if (listCount == 0)
        return;
    for (int i = 0; i < listCount-1; i++)
        if (StringAssistant::similarity(word, this->keyList[i]) < StringAssistant::similarity(word, this->keyList[i+1]))
        {
            std::string temp = this->keyList[i];
            if (temp == "White Sugar") temp+="***HERE***";
            this->keyList[i] = this->keyList[i+1];
            this->keyList[i+1] = temp;
        }
    sortKeyListBySimilarity(word, listCount - 1);
    
}

template <>
bool HashTable<Food>::createPotentialMatches(std::string& word)
{
    int choice;
    if (StringAssistant::similarity(word, this->keyList[0]) < SIMILIARITY_METRIC)
        return false;
    else
    {
        std::cout << "Your request for '" << word << "' was not found\nDid you possibly mean:" << std::endl;
        int index = 0;
        while (StringAssistant::similarity(word, this->keyList[index]) >= SIMILIARITY_METRIC)
        {
            std::cout << "[" << index + 1 << "] -- " << keyList[index] << std::endl;
            index++;
        }
        std::cout << "[-1] -- None of these match what I was looking for." << std::endl;
        std::cout << "--> ";
        std::cin >> choice;
        while (std::cin.fail() || choice > index + 1)
        {
            StringAssistant::clearInput();
            std::cout << "*** invalid, please choose again ***" << std::endl;
            std::cout << "--> ";
            std::cin >> choice;
        }
    }
    if (choice == -1)
        return false;
    else
    {
        word = this->keyList[choice-1];
        return true;
    }
}


template <>
int HashTable<Food>::searchFood(std::string searchValue)
{
    StringAssistant::trimSpaces(searchValue);
    int hashKey = StringAssistant::hashStringName(searchValue); // type specific hashing function

    if (this->dataTable[hashKey] != nullptr)
        if (this->dataTable[hashKey]->getKey() == searchValue) // if found at first try
            return hashKey;
    int counter = 0;
    List<HashNode<Food>*> potentialMatches;
    for (int step = 1; counter < this->count; counter++, step++) //should not take more attempts than there are entries in the table (ie. counter)
    {
        hashKey = ((hashKey + (step * step)) % this->size); // quadratically probe
        
        if (hashKey >= 0 && hashKey < this->size && this->dataTable[hashKey] != nullptr) // if new index is even valid for the table
            if (this->dataTable[hashKey]->getKey() == searchValue)
                return hashKey; // if found value, return
    }
    sortKeyListBySimilarity(searchValue, this->keyList.getCount());
    if (createPotentialMatches(searchValue))
        return this->searchFood(searchValue);
    return -1; // indicates not found
}

template<typename T>
int HashTable<T>::search(std::string searchValue)
{
    StringAssistant::trimSpaces(searchValue);
    int hashKey = StringAssistant::hasher(searchValue); // type specific hashing function
    
    if (this->dataTable[hashKey] != nullptr)
        if (this->dataTable[hashKey]->getKey() == searchValue) // if found at first try
            return hashKey;
    int counter = 0;
    for (int step = 1; counter < this->count; counter++, step++) //should not take more attempts than there are entries in the table (ie. counter)
    {
        hashKey = ((hashKey + (step * step)) % this->size); // quadratically probe
        
        if (hashKey >= 0 && hashKey < this->size && this->dataTable[hashKey] != nullptr) // if new index is even valid for the table
            if (this->dataTable[hashKey]->getKey() == searchValue)
                return hashKey; // if found value, return
    }

    return -1; // indicates not found
}


template <typename T>
bool HashTable<T>::remove(std::string removeValue)
{
    int elementPosition = this->search(removeValue); // search for value
    if (elementPosition == -1) // -1 indicates not found
        return false;
    else
    { // delete the node at the index
        delete this->dataTable[elementPosition];
        this->dataTable[elementPosition] = nullptr;
        this->count--;
        return true;
    }
}

template <typename T>
bool HashTable<T>::isFull()
{
    return (count >= size);
}

template <typename T>
double HashTable<T>::calcLoadFactor()
{
    this->loadFactor = (double(this->count)/this->size) * 100;
    return this->loadFactor;
}

template <typename T>
T HashTable<T>::operator[](int index)
{
    return this->dataTable[index]->getData();
}


template <typename T>
void HashTable<T>::displayTable()
{
    std::printf("%-20s %-15s %10s %10s %5s", "Hash Key", "Data", "Index", "C?", "IPC");
    std::cout  << "\n=================================================================" << std::endl;
    for (int index = 0; index < this->size; index++)
    {
        if (this->dataTable[index] != nullptr)
        {
            std::cout << std::left << std::setw(22) << this->dataTable[index]->getKey();
            std::cout << std::setw(22) << &this->dataTable[index]->getData();
            std::cout << std::left << std::setw(13) << index;
            if (this->dataTable[index]->collision())
            {
                std::cout << std::left << std::setw(5) << "*";
                std::cout << std::left << std::setw(10) << StringAssistant::hasher(this->dataTable[index]->getData());
            }
            std::cout << std::endl;
        }
    }
    std::cout  << "\n=================================================================" << std::endl;
    std::cout << "[C? - Collision occured on entry?] == [IPC - Index Pre Collision]" << std::endl;
    std::cout  << "=================================================================" << std::endl;
}

template <typename T>
void HashTable<T>::stats()
{
    std::cout << "=======================" << std::endl;
    std::cout << "Hash Table Information:" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "Table size: " << this->size << std::endl;
    std::cout << "Items Loaded: " << this->count << " of " << this->attempts << " attempts" << std::endl;
    std::cout << "Load Factor: " << this->calcLoadFactor() << "%" << std::endl;
    std::cout << "Number of Collisions: " << this->collisions << std:: endl;
}


template <typename T>
HashTable<T>::~HashTable<T>()
{
    if (this->count == 0)
        delete[] this->dataTable;
    else
    {
        for (int index = 0; index < this->size; index++)
            if (this->dataTable[index] != nullptr)
                delete this->dataTable[index];
        delete[] this->dataTable;
    }
}

#endif /* HashTable_h */
