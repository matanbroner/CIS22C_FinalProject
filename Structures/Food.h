
#ifndef FOOD_H
#define FOOD_H
#include <string>
#include <iostream>

class Food {
private:
    const double pVal = 4, cVal = 4, fVal = 9;
    unsigned int pKey;
    double protein, carb, fat, quantity;
    std::string unit;
    std::string name;
public:
    Food();
    Food(const Food &copy);
    Food(std::string n, double p, double c, double f);
    Food(std::string n, double p, double c, double f, double, std::string);
    ~Food();
    std::string getName();
    double getProtein();
    double getCarb();
    double getFat();
    double getCal();
    void printFoodWithMacros();
    Food operator= (const Food &right);
    bool operator< (Food &right);
    bool operator== (Food &right);
    bool operator<= (Food &right);
    friend std::ostream& operator<< (std::ostream &out, const Food &food);
};


Food::Food()
{
    this->protein = this->carb = this->fat = 0;
    this->name = "***";
}

Food::Food(const Food &copy) {
    protein = copy.protein;
    carb = copy.carb;
    fat = copy.fat;
    name = copy.name;
}

Food::Food(std::string n, double c, double f, double p) :
protein(p),
carb(c),
fat(f),
name(n)
{
    this->quantity = 1;
    this->unit = "unit";
}

Food::Food(std::string n, double c, double f, double p, double q, std::string u) :
name(n), protein(p), carb(c), fat(f), quantity(q), unit(u)
{
}

Food::~Food() {}

std::string Food::getName(){
    return this->name;
}

double Food::getProtein() {
    return protein;
}
double Food::getCarb() {
    return carb;
}
double Food::getFat() {
    return fat;
}
double Food::getCal() {
    return ((protein * pVal) + (carb * cVal) + (fat * fVal));
}
Food Food::operator= (const Food &right) {
    this->name = right.name;
    this->protein = right.protein; this->carb = right.carb; this->fat = right.fat;
    return right;
}
bool Food::operator< (Food &right) {
    return (getCal() < right.getCal());
}
bool Food::operator== (Food &right) {
    return (getCal() == right.getCal());
}
bool Food::operator<= (Food &right) {
    return (getCal() <= right.getCal());
}
std::ostream& operator<< (std::ostream &out, const Food &food) {
    out << food.name;
    return out;
}
void Food::printFoodWithMacros()
{
    std::cout << this->name << ", "
    << "f: " << this->fat << ", "
    << "c: " << this->carb << ", "
    << "p: " << this->protein << " (" << this->quantity << " " << this->unit << ")";
}
#endif 
