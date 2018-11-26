#ifndef DAY_H
#define DAY_H
#include "List.h"
#include "Food.h"
#include "Stack.h"

class Day {
private:
    static int calTarget;
    const int pVal = 4,        // value of calories to macros
    cVal = 4,
    fVal = 9;
    
    unsigned int pKey = 10;
    
    int date,
    fat = 0,
    carb = 0,
    prot = 0;
    
    List<Food> allFood;
    
public:
    Day(List<Food> &foods, int dt);    // default constructor
    Day(int f, int c, int p, int dt);    // file in constructor
    Day(Day &day);                        // copy constructor
    ~Day();                                // destructor
    
    void display();                        // display contents of the day
    double offTarget();                    // return % away from target cal
    int totalCal();                        // return total calories of macros
    
    bool operator== (const Day &right);
    bool operator< (const Day &right);
    bool operator> (const Day &right);
    
    // public static variable
    // must be public for setter
    
    static int getCal() {                // only seems to work inline
        return calTarget;
        return 0;// return target calories for day
    }
    void setCT(int CT) {                // inline
        calTarget = CT;                    // calTarget setter
    }
};

int Day::calTarget = 1200;

Day::Day(List<Food> &foods, int dt) : date(dt) {
    Food temp;
    while(foods.getCount() > 0) {
        temp = foods.deleteHead();
        prot += temp.getProtein();
        carb += temp.getCarb();
        fat += temp.getFat();
        allFood.addAtHead(temp);
    }
}

Day::Day(int f, int c, int p, int dt) :
fat(f),
carb(c),
prot(p),
date(dt)
{}

Day::Day(Day &copy) :
pKey(copy.pKey),
date(copy.date),
prot(copy.prot),
carb(copy.carb),
fat(copy.fat),
allFood(copy.allFood)
{}

Day::~Day() {}

void Day::display(){
    std::cout << "pKey: " << pKey << std::endl
    << "Calorie Target: " << getCal() <<  std::endl
    << "Foods: " << std::endl;
    allFood.printList();
    std::cout << "Calories Consumed: " << this->totalCal() << std::endl;
    std::cout << "Percent off target " << offTarget() << "%" << std::endl;
}

double Day::offTarget() {
    int temp = getCal();
    return (1 - (totalCal() / static_cast<double>(temp))) * 100.0;
}

int Day::totalCal() {
    return ((prot * pVal) + (carb * cVal) + (fat * fVal));
}

bool Day::operator== (const Day &right) {
    return (
            fat == right.fat &&
            carb == right.carb &&
            prot == right.prot
            );
}

bool Day::operator< (const Day &right) {
    return (
            fat < right.fat &&
            carb < right.carb &&
            prot < right.prot
            );
}

bool Day::operator> (const Day &right) {
    return (
            fat > right.fat &&
            carb > right.carb &&
            prot > right.prot
            );
}
#endif
