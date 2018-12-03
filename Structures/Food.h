
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
	double getQuantity();
	std::string getUnit();
	void printFoodWithMacros();
	Food operator= (const Food &right);
	bool operator< (Food &right);
	bool operator== (Food &right);
	bool operator<= (Food &right);
	friend std::ostream& operator<< (std::ostream &out, Food &food);
};


Food::Food()
{
	this->protein = this->carb = this->fat = 0;
	this->name = "***";
}

Food::Food(const Food &copy) {
	this->protein = copy.protein;
	this->carb = copy.carb;
	this->fat = copy.fat;
	this->name = copy.name;
	this->unit = copy.unit;
	this->quantity = copy.quantity;
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
{}

Food::~Food() {}

std::string Food::getName() {
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
double Food::getQuantity()
{
	return this->quantity;
}
std::string Food::getUnit()
{
	return this->unit;
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
std::ostream& operator<< (std::ostream &out, Food &food) {
	out << food.getName() << ": " << food.getCal() << " kC";
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