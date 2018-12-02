#ifndef DAY_H
#define DAY_H
#include "List.h"
#include "Food.h"
#include "Stack.h"

#include <iostream>

static bool sortByCals;

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
    Day(Day &day);// copy constructor
    Day();
    ~Day();                                // destructor
    
    int getDate();
    void display();                        // display contents of the day
    double offTarget();                    // return % away from target cal
    int totalCal();                        // return total calories of macros
    
    bool operator== (const Day &right);
    bool operator< (const Day &right);
    bool operator> (const Day &right);
    void operator= (const Day &right);
    void operator<<(std::ostream&);
    
    // public static variable
    // must be public for setter
    
    static int getCal() {                // only seems to work inline
        return calTarget;
    }
    void setCT(int CT) {                // inline
        calTarget = CT;                    // calTarget setter
    }
    
    static void sortByCalories();
    static void sortByDates();
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

Day::Day()
{
    this->date = 0; this->pKey = 0;
    this->prot = 0; this->carb = 0; this->fat = 0;
}

Day::~Day() {}

void Day::display(){
    std::cout << "Date: " << this->date << std::endl
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

int Day::getDate(){return this->date;}

bool Day::operator== (const Day &right) {
    if(sortByCals)
        return (
                fat == right.fat &&
                carb == right.carb &&
                prot == right.prot
                );
    else return (this->date == right.date);
}

bool Day::operator< (const Day &right) {
    if(sortByCals)
        return (
                fat < right.fat &&
                carb < right.carb &&
                prot < right.prot
                );
    else return (this->date < right.date);
}

bool Day::operator> (const Day &right) {
    if (sortByCals)
        return (
                fat > right.fat &&
                carb > right.carb &&
                prot > right.prot
                );
    
    else return (this->date > right.date);
}

void Day::operator=(const Day &right)
{
    this->pKey = right.pKey;
    this->prot = right.prot;
    this->carb = right.carb;
    this->fat = right.fat;
    this->allFood = right.allFood;
}

void Day::operator<<(std::ostream &out)
{
    out << "[" << this->date << "]";
}

void Day::sortByCalories(){sortByCals = true;}
void Day::sortByDates(){sortByCals = false;}
#endif
