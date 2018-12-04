
#ifndef FoodCreator_h
#define FoodCreator_h

#include "Food.h"
#include "HashTable.h"

class FoodCreator
{
private:
    
public:
    static bool getMacroNutrient(std::string, double&);
    static void getUnit(std::string&);
    static Food create(std::string);
};

Food FoodCreator::create(std::string name)
{
    StringAssistant::nameFormatter(name);
    std::string unit;
    double carb, fat, protein, quantity;
    getMacroNutrient("[Carb]", carb);
    getMacroNutrient("[Fat]", fat);
    getMacroNutrient("[Protein]", protein);
    std::cout << "[Unit of measurement]:" << std::endl;
    getUnit(unit);
    std::cout << "[Quantity of '" << unit << "' for given macronutrients]: ";
    std::cin >> quantity;
    while (std::cin.fail() || quantity < 0.1)
    {
        StringAssistant::clearInput();
        std::cout << "*** invalid *** --> ";
    }
    Food temp(name, carb, fat, protein, quantity, unit);
    return temp;
}

bool FoodCreator::getMacroNutrient(std::string name, double& nutrient)
{
    nutrient = -1;
    while (nutrient < 0)
    {
        std::cout << name << " count: ";
        std::cin >> nutrient;
        if (std::cin.fail() || nutrient < 0)
        {
            StringAssistant::clearInput();
            std::cout << "*** invalid " << name << " count ***" << std::endl;
            nutrient = -1;
        }
    }
    return true;
}

void FoodCreator::getUnit(std::string &unit)
{
    int unitInteger = -1;
    while(unitInteger < 1 || unitInteger > 8)
    {
        std::cout << "[1] - gram" << std::endl;
        std::cout << "[2] - pound" << std::endl;
        std::cout << "[3] - ounce" << std::endl;
        std::cout << "[4] - cup" << std::endl;
        std::cout << "[5] - liter" << std::endl;
        std::cout << "[6] - teaspoon" << std::endl;
        std::cout << "[7] - tablespoon" << std::endl;
        std::cout << "[8] - unit\n--> ";
        std::cin >> unitInteger;
        if (std::cin.fail())
            StringAssistant::clearInput();
    }
    switch(unitInteger)
    {
        case 1: unit = "g"; break;
        case 2: unit = "lbs"; break;
        case 3: unit = "oz"; break;
        case 4: unit = "c"; break;
        case 5: unit = "l"; break;
        case 6: unit = "tsp"; break;
        case 7: unit = "tbsp"; break;
        case 8: unit = "unit"; break;
    }
}


#endif /* FoodCreator_h */
