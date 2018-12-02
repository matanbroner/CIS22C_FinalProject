#ifndef DAYMANAGER_H
#define DAYMANAGER_H

#include <string>
#include <iostream>
#include <fstream>
#include "List.h"
#include "BinarySearchTree.h"
#include "Food.h"
#include "Stack.h"
#include "Day.h"

class DayManager {
private:
	bool choice();
	static int days;
	static Day* currentDay;
	static Stack removedDays;
public:
	DayManager();
	~DayManager();
	static Day* foodInputFunction();
	static bool foodFileFunction(ifstream &input, BinarySearchTree &tree);
};

bool DayManager::choice() {
	
	bool valid = false;
	std::string answer;

	do {
		std::cout << "Enter Food? [Y/n] ";
		getline(std::cin, answer);
		std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

		valid =
			(answer == "y") ||
			(answer == "n") ||
			(answer == "yes") ||
			(answer == "no");
	} while (!valid);
	return ((answer == "y") || (answer == "yes")) ? true : false;
}

DayManager::DayManager() : days(0) {}
DayManager::~DayManager() {}

static Day* DayManager::foodInputFunction();
	List foodInputList;
	while(true) {
		if (!choice()) {
			break;
		}
		else {
		days++;								// add to static days for date input
		// search for food
		
		foodInputList.addAtHead();			// build food list for day
		}
	// create day
	currentDay = new Day(foodInputList, days);	// assign ptr to current day
	return currentDay;							// return ptr to current day
}

static bool DayManager::foodFileFunction(ifstream &input, BinarySearchTree &tree) {
	
	// validate file
	if (!input.is_open()) {
		return false;
	}
	while (input.is_open() && !input.eof()) {
		std::string tempString;
		std::string name, quantity, unit, carb, fat, protein;
		getline(input, name, '(');

		getline (input, tempString, ')');
		parseQuantityAndUnit(tempString, quantity, unit);
		getline(input, tempString, '-');
		getline(input, tempString, ' ');
		getline(input, carb, ' ');
		getline(input, fat, ' ');
		getline(input, protein);
		StringAssistant::trimSpaces(name);
		Food addedFood(name, std::stod(protein), std::stod(carb), std::stod(fat), std::stod(quantity), unit);
		tree.insert(addedFood, name);
	}
	return true;
}

static void DayManager::removeToStack(Day &toRemove, BinarySearchTree &tree) {
	Day temp();
	tree.findForModification(toRemove, temp)
	tree.remove(toRemove);
	removedDays.push(temp);
}


#endif
