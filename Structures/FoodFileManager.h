//
//  FoodFileManager.h
//  CIS22C_FinalProject
//
//  Created by Matan Broner on 11/28/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//


// add food by quantity
#ifndef FoodFileManager_h
#define FoodFileManager_h
#include "HashTable.h"
#include <fstream>
#include <string>
class FoodFileManager
{
private:
    static void parseQuantityAndUnit(std::string&, std::string&, std::string&);
public:
    static bool readFromInputFileIntoTable(std::ifstream&, HashTable<Food>&);
    static bool writeTableToInputFile(std::ofstream& outFile, HashTable<Food> &table);
};

bool FoodFileManager::readFromInputFileIntoTable(std::ifstream &input, HashTable<Food> &table)
{
    if (!input.is_open())
        return false;
    while (input.is_open() && !input.eof())
    {
        std::string tempString;
        std::string name, quantity, unit, carb, fat, protein;
        getline(input, name, '(');
        getline (input, tempString, ')');
        parseQuantityAndUnit(tempString, quantity, unit);
        getline(input, tempString, '-');
        getline(input, tempString, ' ');
        getline(input, carb, ' ');
        getline(input, fat, ' ');
        getline(input, protein);
        StringAssistant::trimSpaces(name);
        Food addedFood(name, std::stod(protein), std::stod(carb), std::stod(fat), std::stod(quantity), unit);
        table.insertFood(addedFood, name);
    }
    input.close();
    return true;
}

bool FoodFileManager::writeTableToInputFile(std::ofstream& outFile, HashTable<Food> &table)
{
   
    if (table.getCount() > 0)
        for (int i = 0; i < table.getSize(); i++)
        {
            if (table[i] != nullptr)
            {
                outFile << table[i]->getData().getName() << " (";
                outFile << table[i]->getData().getQuantity() << " ";
                outFile << table[i]->getData().getUnit() << ") - ";
                outFile << table[i]->getData().getCarb() << " ";
                outFile << table[i]->getData().getFat() << " ";
                outFile << table[i]->getData().getProtein();
                if (i < table.getSize() - 1)
                    outFile << std::endl;
            }
        }
    return true;
}

void FoodFileManager::parseQuantityAndUnit(std::string &container, std::string &quantity, std::string &unit)
{
    bool dec = false;
    for (char c : container)
    {
        if (isdigit(c) || (c == '.' && !dec))
        {
            quantity += c;
            if (c == '.')
                dec = true;
        }
        else if (c != ' ')
            unit += c;
    }
}


#endif /* FoodFileManager_h */
