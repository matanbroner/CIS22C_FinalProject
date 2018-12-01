
#ifndef FoodCreator_h
#define FoodCreator_h

#include "Food.h"
#include "HashTable.h"

class FoodCreator
{
private:
    
public:
    static bool getMacroNutrient(std::string, double&);
    static Food create(std::string);
};

Food FoodCreator::create(std::string name)
{
    double carb, fat, protein;
    getMacroNutrient("Carb", carb);
    getMacroNutrient("Fat", fat);
    getMacroNutrient("Protein", protein);
    Food temp(name, carb, fat, protein);
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

#endif /* FoodCreator_h */
