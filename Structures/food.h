#ifndef FOOD_H
#define FOOD_H
#include <string>

class Food {
private:
	const int pVal = 4, cVal = 4, fVal = 9;
	unsigned int pKey;
	int protein, carb, fat;
	std::string name;
public:
	Food(int p, int c, int f, std::string n);
	~Food();
	int getProtein();
	int getCarb();
	int getFat();
	int getCal();
	bool operator< (const Food &right);
	bool operator== (const Food &right);
};
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
	return ((protein * pVal) + (carb * cVal) + (fat * fVal))
}
bool Food::operator< (const Food &right) {
	return (this.getCal() < right.getCal());
}
bool Food::operator== (const Food &right) {
	return (this.getCal() == right.getCal());
}
#endif 