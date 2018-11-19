#ifndef FOOD_H
#define FOOD_H
#include <string>
#include <iostream>

class Food {
private:
	const int pVal = 4, cVal = 4, fVal = 9;
	unsigned int pKey;
	int protein, carb, fat;
	std::string name;
public:
	Food();
	Food(const Food &copy);
	Food(int p, int c, int f, std::string n);
	~Food();
	int getProtein();
	int getCarb();
	int getFat();
	int getCal();
	Food operator= (const Food &right);
	bool operator< (Food &right);
	bool operator== (Food &right);
	friend std::ostream& operator<< (std::ostream &out, const Food &food);
};

Food::Food() :
	protein(1),
	carb(1),
	fat(1),
	name("normal")
{}

Food::Food(const Food &copy) {
	protein = copy.protein;
	carb = copy.carb;
	fat = copy.fat;
	name = copy.name;
}

Food::Food(int p, int c, int f, std::string n) :
	protein(p),
	carb(c),
	fat(f),
	name(n)
{}

Food::~Food() {}

int Food::getProtein() {
	return protein;
}
int Food::getCarb() {
	return carb;
}
int Food::getFat() {
	return fat;
}
int Food::getCal() {
	return ((protein * pVal) + (carb * cVal) + (fat * fVal));
}
Food Food::operator= (const Food &right) {
	return Food(right);
}
bool Food::operator< (Food &right) {
	return (getCal() < right.getCal());
}
bool Food::operator== (Food &right) {
	return (getCal() == right.getCal());
}
std::ostream& operator<< (std::ostream &out, const Food &food) {
	out << "name: " << food.name << std::endl;
	out << "fat: " << food.fat << std::endl;
	out << "carb: " << food.carb << std::endl;
	out << "protein: " << food.protein << std::endl;
	return out;
}
#endif 
