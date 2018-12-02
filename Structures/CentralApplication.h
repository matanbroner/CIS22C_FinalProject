
#ifndef CentralApplication_h
#define CentralApplication_h

#include "FoodFileManager.h"
#include "FoodCreator.h"
#include "StructurePrinter.h"
#include "Day.h"

#endif /* CentralApplication_h */

class CentralApplication
{
private:
    HashTable<Food> foodsTable;
    HashTable<Day> daysTable;
    BinarySearchTree<Day> daysByCaloriesTree;
    static std::string getFileAddress(std::string);
    static int getMenuChoice();
    void processMenuChoice(int);
    int findByDate(Day&);
    bool removeDay();
    static void pressEnterToContinue();
    static void quit();
public:
    void menu();
};

// main app functionality. All main menu UI and File IO should take place here

/*
 Public Functions
 */

void CentralApplication::menu()
{
    std::ifstream foodFile, dayFile;
    foodFile.open(getFileAddress("Foods and Macronutrients"));
    dayFile.open(getFileAddress("Logged Days"));
    if (FoodFileManager::readFromInputFileIntoTable(foodFile, this->foodsTable)) // will add DayFileManager file reader condition once present
    {
        pressEnterToContinue();
        int menuOption = getMenuChoice();
        processMenuChoice(menuOption);
    }
}

/*
 Private Functions
 */

std::string CentralApplication::getFileAddress(std::string context)
{
    std::string address;
    std::cout << "File address for " << context << ": ";
    getline(std::cin, address);
    return address;
}

int CentralApplication::getMenuChoice()
{
    int choice = -1;
    std::cout << "============" << std::endl;
    std::cout << "Menu Options" << std::endl;
    std::cout << "============" << std::endl;
    std::cout << "[1] - Log a new day of eating" << std::endl;
    std::cout << "[2] - Delete a logged day" << std::endl;
    std::cout << "[3] - Display a day's stats by date" << std::endl;
    std::cout << "[4] - Display Hash Table of available foods" << std::endl;
    std::cout << "[5] - Display all logged days in sorted fashion" << std::endl;
    std::cout << "[6] - Display Indneted BST of all logged days" << std::endl;
    std::cout << "[7] - List efficiency stats" << std::endl;
    std::cout << "[8] - Visualize logged days' calories vs. target consumption" << std::endl;
    std::cout << "[9] - Undo last deletion of a day" << std::endl;
    std::cout << "[10] - Save all changes" << std::endl;
    std::cout << "[0] - Quit" << std::endl;
    std::cout << "--> ";
    std::cin >> choice;
    while(std::cin.fail() || choice < 0 || choice > 10)
    {
        StringAssistant::clearInput();
        std::cout << "*** Not a valid menu option! ***" << std::endl;
        std::cin >> choice;
    }
    
    return choice;
}

void CentralApplication::processMenuChoice(int choice)
{
    switch (choice)
    {
        case 1: // run day creator
            break;
        case 2:
        {
            if (removeDay())
                std::cout << "== Deletion was succesful ==" << std::endl;
            else std::cout << "== Given date was not found in this database ==" << std::endl;
            break;
        }
        case 3:
        {
            Day temp;
            if (findByDate(temp))
                temp.display();
            else std::cout << "== Given date was not found in this database ==" << std::endl;
        }
        case 4: this->foodsTable.displayTable(); break;
        case 5: this->daysTable.displayTable(); break;
        case 6: StructurePrinter<Day>::printBinarySearchTree(this->daysByCaloriesTree); break;
        case 7: this->foodsTable.stats(); break;
        case 8: // graph function
            break;
        case 9: // pop from stack and reinsert both into tree and into days hash table
            break;
        case 10: // will use write to file for both food and day, to be added
            break;
        case 0: quit();
    }
    pressEnterToContinue();
}

bool CentralApplication::removeDay()
{
    int day;
    std::cout << "Date of day to be displayed: ";
    std::cin >> day;
    while(std::cin.fail() || day < 1 || day > 100)
    {
        StringAssistant::clearInput();
        std::cout << "*** Not a valid day for search! ***" << std::endl;
        std::cin >> day;
    }
    if (this->daysTable.remove(std::to_string(day)))
        return true;
    else return false;
}

int CentralApplication::findByDate(Day& holder)
{
    int day;
    std::cout << "Date of day to be displayed: ";
    std::cin >> day;
    while(std::cin.fail() || day < 1 || day > 100)
    {
        StringAssistant::clearInput();
        std::cout << "*** Not a valid day for search! ***" << std::endl;
        std::cin >> day;
    }
    return this->daysTable.search(std::to_string(day));
}

void CentralApplication::pressEnterToContinue()
{
    std::cout << "Press ENTER to continue...";
    std::cin.get();
    system("clear");
}

void CentralApplication::quit()
{
    int choice;
    std::cout << "Would you like to save all changes before quitting?" << std::endl;
    std::cout << "[1] -- SAVE" << std::endl;
    std::cout << "[2] -- QUIT WITHOUT SAVING\n--> " << std::endl;
    std::cin >> choice;
    while(std::cin.fail() || choice < 1 || choice > 2)
    {
        StringAssistant::clearInput();
        std::cout << "*** Not a valid response! ***\n--> " << std::endl;
        std::cin >> choice;
    }
    if (choice == 1)
        // write to input files
        ;
    std::cout << "Goodbye!" << std::endl;
}
