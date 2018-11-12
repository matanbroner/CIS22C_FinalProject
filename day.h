#ifndef DAY_H
#define DAY_H

class Day {
private:
	unsigned int pKey;
	int date;
	static calTarget;
	List<Food> allFood;
public:
	Day(Stack<Food> f, int dt);
	~Day();
	void display() const;
	double offTarget();
	bool operator== (const Day &right);
	bool operator< (const Day &right);
};

Day(Stack<Food> f, int dt) : date(dt) {
	// loop through stack
	while (f.peektop() != NULL) {
		allFood.add(f.pop());
	}
}
~Day() {}

void display() const {
	std::cout << "pKey: " << pKey << std::endl
		<< "Calorie Target: " << calTarget << std::endl
		<< "Foods: "
		<< "Percent off target % " << 
}

double offTaget() {
	return 1.0 - calTarget / allFood.total(); // need function to return calories of all food in list
}

bool operator== (const Day &right) {
	return (this.allFood.total() == right.allFood.total());
}
bool operator< (const Day &right) {
	return (this.allFood.total() < right.allFood.total());
}