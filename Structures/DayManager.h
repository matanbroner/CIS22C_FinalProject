#ifndef DAYMANAGER_H
#define DAYMANAGER_H

#include <string>
#include <iostream>
#include <fstream>
#include "List.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "Food.h"
#include "Stack.h"
#include "Day.h"

class DayManager {
private:
    static bool choice();
    //static int days;
    static Day* currentDay;
    static int mostRecentDate;
public:
    //static Stack removedDays;
    DayManager();
    ~DayManager();
    static Day& createNewDay(HashTable<Food>&);
    static bool readFromDayFile(std::ifstream &input, BinarySearchTree<Day> &tree, HashTable<Day> &dayTable);
};

int DayManager::mostRecentDate = 0;

DayManager::DayManager() {}
DayManager::~DayManager() {}

bool DayManager::choice() {
    
    bool valid = false;
    std::string answer;
    
    do {
        std::cout << "[Y/N]\n--> ";
        getline(std::cin, answer);
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        
        valid =
        (answer == "y") ||
        (answer == "n") ||
        (answer == "yes") ||
        (answer == "no");
    } while (!valid);
    return ((answer == "y") || (answer == "yes")) ? true : false;
}

Day& DayManager::createNewDay(HashTable<Food>& foodsPresent)
{
    int date = ++mostRecentDate;
    List<Food> foodInputList;
    
    std::string searchTerm = "pie";
    while (searchTerm != "")
    {
        std::cout << "Food eaten to add [Press ENTER to stop adding foods]: ";
        getline(std::cin, searchTerm);
        if (searchTerm == "")
            break;
        int index = foodsPresent.searchFood(searchTerm);
        if (index == -1)
        {
            std::cout << "Would you like to add '" << searchTerm << "' to your available foods?" << std::endl;
            if(choice())
            {
                Food newFood = FoodCreator::create(searchTerm);
                foodsPresent.insertFood(newFood, searchTerm);
                int indexOfNewFood = foodsPresent.searchFood(searchTerm);
                foodInputList.add(foodsPresent[indexOfNewFood]->getData());
                std::cin.ignore();
            }
            else std::cout << "Okay, not adding '" << searchTerm << "' to database." << std::endl;
        }
        else foodInputList.add(foodsPresent[index]->getData());
    }
    std::cout << "Okay, so today you have eaten:\n[";
    foodInputList.printList();
    std::cout << "]" << std::endl;
    Day temp(foodInputList, date);// assign ptr to current day
    return temp;                            // return ptr to current day
}
    
bool DayManager::readFromDayFile(std::ifstream &input, BinarySearchTree<Day> &tree, HashTable<Day> &dayTable)
{
        
    // validate file
    if (!input.is_open()) {
        return false;
    }
    std::string tempString;
        getline(input, tempString);            // trash header line
        getline(input, tempString);            // get calorie target
    Day::setCT(std::stoi(tempString));                // set calorie target
        while (!input.eof()) {
            std::string date, carb, fat, protein;
            getline(input, protein, ' ');
            getline(input, carb, ' ');
            getline(input, fat, ' ');
            getline(input, date);
            Day temp(std::stod(fat), std::stod(carb), std::stod(protein), std::stoi(date));
            std::cout << temp << std::endl;
            tree.insert(temp);
            dayTable.insert(temp, date);
            if (temp.getDate() > mostRecentDate)
                mostRecentDate = temp.getDate();
        }
        return true;
    }
    
    //  void DayManager::removeToStack(Day &toRemove, BinarySearchTree<Day> &tree) {
    //     Day temp();
    //     tree.findForModification(toRemove, temp)
    //     tree.remove(toRemove);
    //     removedDays.push(temp);
    // }
    
    
#endif
