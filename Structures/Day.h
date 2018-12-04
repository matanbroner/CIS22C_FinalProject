#ifndef DAY_H
#define DAY_H
#include "List.h"
#include "Food.h"
#include "Stack.h"
#include <iostream>
#include "StringAssistant.h"


class Day {
private:
    static int calTarget;
    static bool sortByCals;
    const int pVal = 4,        // value of calories to macros
    cVal = 4,
    fVal = 9;
    
    int date,
    fat = 0,
    carb = 0,
    prot = 0;
    
    List<Food> allFood;
    
public:
    Day(List<Food> &foods, int dt);    // default constructor
    Day(double f, double c, double p, int dt);    // file in constructor
    Day(Day &day);// copy constructor
    Day();
    ~Day();                                // destructor
    
    int getDate();
    void display();                        // display contents of the day
    double offTarget();                    // return % away from target cal
    int totalCal();                         // return total calories of macros
    int getDayProtein();
    int getDayCarb();
    int getDayFat();
    
    bool operator== (Day &right);
    bool operator< (Day &right);
    bool operator> (Day &right);
    bool operator<=(Day &right);
    void operator= (Day &right);
    
    // public static variable
    // must be public for setter
    
    static int getTargetCal() {                // only seems to work inline
        return calTarget;
    }
    static void setCT(int CT) {                // inline
        calTarget = CT;                    // calTarget setter
    }
    
    static void sortByCalories();
    static void sortByDates();
};

bool Day::sortByCals = true;

std::ostream& operator<<(std::ostream& out, Day& day)
{
    std::string formatted = std::to_string(day.getDate()) + ": " + std::to_string(day.totalCal()) + " kC";
    out << formatted;
    return out;
}

int Day::calTarget = 1200;



Day::Day(List<Food> &foods, int dt) : date(dt) {
    Food temp;
    this->allFood = foods;
    for (int i = 0; i < this->allFood.getCount(); i++)
    {
        this->prot += this->allFood.getDataAtIndex(i).getProtein();
        this->carb += this->allFood.getDataAtIndex(i).getCarb();
        this->fat += this->allFood.getDataAtIndex(i).getFat();
    }
}

Day::Day(double f, double c, double p, int dt) :
fat(f),
carb(c),
prot(p),
date(dt)
{}

Day::Day(Day &copy) :
date(copy.date),
prot(copy.prot),
carb(copy.carb),
fat(copy.fat),
allFood(copy.allFood)
{}

Day::Day() : date(0), prot(0), carb(0), fat(0)
{
}

Day::~Day() {}

void Day::display(){
    std::cout << "Date: " << this->date << std::endl
    << "Calorie Target: " << getTargetCal() <<  std::endl
    << "Foods: " << std::endl;
    allFood.printList();
    std::cout << "Calories Consumed: " << this->totalCal() << std::endl;
    std::cout << "Percent off target " << offTarget() << "%" << std::endl;
}

double Day::offTarget() {
    int temp = getTargetCal();
    return (1 - (totalCal() / static_cast<double>(temp))) * 100.0;
}

int Day::totalCal() {
    double calories = (((prot * pVal) + (carb * cVal) + (fat * fVal)) * 100) / 100;
    return calories;
}

int Day::getDate(){return this->date;}
int Day::getDayProtein(){return this->prot;}
int Day::getDayCarb(){return this->carb;}
int Day::getDayFat(){return this->fat;}

bool Day::operator== (Day &right) {
    if(sortByCals)
        return (this->totalCal() == right.totalCal());
    else return (this->date == right.date);
}

bool Day::operator< (Day &right) {
    if(sortByCals)
        return (this->totalCal() < right.totalCal());
    else return (this->date < right.date);
}

bool Day::operator<=(Day& right)
{
    if(sortByCals)
        return (this->totalCal() <= right.totalCal());
    else return (this->date <= right.date);
}

bool Day::operator> (Day &right) {
    if (sortByCals)
        return (this->totalCal() > right.totalCal());
    
    else return (this->date > right.date);
}

void Day::operator=(Day &right)
{
    this->date = right.date;
    this->prot = right.prot;
    this->carb = right.carb;
    this->fat = right.fat;
    this->allFood.emptyListContents();
    for (int i = 0; i < right.allFood.getCount(); i++)
    {
        this->allFood.addAtPos(i, right.allFood.getDataAtIndex(i));
    }
}


void Day::sortByCalories(){sortByCals = true;}
void Day::sortByDates(){sortByCals = false;}
#endif
