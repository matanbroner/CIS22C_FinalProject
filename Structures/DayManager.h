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
    Day* currentDay = nullptr;
    static int mostRecentDate;
    List<Food> currentDayFood;
    void readFoodsFromUser(double&, double&, double&, HashTable<Food>&);
public:
    //static Stack removedDays;
    DayManager();
    ~DayManager();
     bool createNewDay(HashTable<Food>&, HashTable<Day>&, BinarySearchTree<Day>&);
    static bool readFromDayFile(std::ifstream &input, BinarySearchTree<Day> &tree, HashTable<Day> &dayTable);
    static bool writeToDataFile(std::ofstream& output, HashTable<Day> &dayTable);
     bool editCurrentDay(HashTable<Food>&, HashTable<Day>&, BinarySearchTree<Day>&);
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

bool DayManager::createNewDay(HashTable<Food>& foodsPresent, HashTable<Day>& dayTable, BinarySearchTree<Day>& dayTree)
{
    this->currentDayFood.emptyListContents();
    double protein = 0, carb = 0, fat = 0;
    ++mostRecentDate;
    this->readFoodsFromUser(protein, fat, carb, foodsPresent);
    Day temp(fat, carb, protein, mostRecentDate);
    this->currentDay = &temp;
    dayTable.insert(temp, std::to_string(mostRecentDate));
    dayTree.insert(temp);
    return true;                            // return ptr to current day
}

bool DayManager::editCurrentDay(HashTable<Food> &foods, HashTable<Day> &dayTable, BinarySearchTree<Day> &dayTree)
{
    if (this->currentDay != nullptr)
    {
        double protein = 0, carb = 0, fat = 0;
        Day::sortByDates();
        dayTable.remove(std::to_string(mostRecentDate));
        dayTree.remove(*currentDay);
        this->readFoodsFromUser(protein, fat, carb, foods);
        Day temp(fat, carb, protein, mostRecentDate);
        Day::sortByCalories();
        dayTree.insert(temp);
        dayTable.insert(temp, std::to_string(mostRecentDate));
        this->currentDay = &temp;
        return true;
    }
    else return false;
}



bool DayManager::readFromDayFile(std::ifstream &input, BinarySearchTree<Day> &tree, HashTable<Day> &dayTable)
{
    Day::sortByCalories();
    // validate file
    if (!input.is_open()) {
        return false;
    }
    std::string tempString;
    getline(input, tempString);            // trash header line
    getline(input, tempString);            // get calorie target
    Day::setCT(std::stoi(tempString));                // set calorie target
    std::string date, carb, fat, protein;
    while (getline(input, protein, ' ')) {
        getline(input, carb, ' ');
        getline(input, fat, ' ');
        getline(input, date);
        Day temp(std::stod(fat), std::stod(carb), std::stod(protein), std::stoi(date));
        tree.insert(temp);
        dayTable.insert(temp, date);
        if (temp.getDate() > mostRecentDate)
            mostRecentDate = temp.getDate();
    }
    return true;
}

void DayManager::readFoodsFromUser(double &protein, double &fat, double &carb, HashTable<Food> &foodsPresent)
{
    std::string searchTerm = "pie";
    while (searchTerm != "")
    {
        std::cout << "Food eaten to add [Press ENTER to stop adding foods]: ";
        getline(std::cin, searchTerm);
        if (searchTerm == "")
            break;
        StringAssistant::nameFormatter(searchTerm);
        StringAssistant::trimSpaces(searchTerm);
        int index = foodsPresent.searchFood(searchTerm);
        if (index == -1)
        {
            std::cout << "Would you like to add '" << searchTerm << "' to your available foods?" << std::endl;
            if (choice())
            {
                Food newFood = FoodCreator::create(searchTerm);
                foodsPresent.insertFood(newFood, searchTerm);
                int indexOfNewFood = foodsPresent.searchFood(searchTerm);
                this->currentDayFood.add(foodsPresent[indexOfNewFood]->getData());
                std::cin.ignore();
                std::cout << "'" << searchTerm << "' has been added to your available foods, and to today's food log!" << std::endl;
            }
            else std::cout << "Okay, not adding '" << searchTerm << "' to database." << std::endl;
        }
        else this->currentDayFood.add(foodsPresent[index]->getData());
    }
    std::cout << "Okay, so today you have eaten:\n[";
    this->currentDayFood.printList();
    std::cout << "]" << std::endl;
    for (int i = 0; i < this->currentDayFood.getCount(); i++)
    {
        protein += this->currentDayFood.getDataAtIndex(i).getProtein();
        fat += this->currentDayFood.getDataAtIndex(i).getFat();
        carb += this->currentDayFood.getDataAtIndex(i).getCarb();
    }
}

bool DayManager::writeToDataFile(std::ofstream &output, HashTable<Day> &dayTable)
{
    Day::sortByDates();
    List<Day> dayList;
    output << "p c f d" << std::endl;
    output << Day::getTargetCal() << std::endl;
    for (int i = 0; i < dayTable.getSize(); i++)
    {
        if (dayTable[i])
        {
            dayList.add(dayTable[i]->getData());
            dayList.sortListAcsending();
        }
    }
    while (dayList.getCount() > 0)
    {
        Day temp = dayList.deleteHead();
        output << temp.getDayProtein() << " " << temp.getDayCarb() << " " << temp.getDayFat() << " " << temp.getDate();
        if (dayList.getCount() > 0)
            output << std::endl;
    }
    return true;
}



#endif
