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
	static bool choice();
	//static int days;
	static Day* currentDay;
public:
	//static Stack removedDays;
	DayManager();
	~DayManager();
	static Day foodInputFunction();
	static bool foodFileFunction(std::ifstream &input, BinarySearchTree<Day> &tree);
};

DayManager::DayManager() {}
DayManager::~DayManager() {}

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

Day DayManager::foodInputFunction() {
	List<Food> foodInputList;
	int days;
	while(true) {
		if (!choice()) {
			break;
		}
		else {
		days++;								// add to static days for date input
		// search for food
		
		// foodInputList.addAtHead();			// build food list for day
		}
	// create day
	Day temp(foodInputList, days);	// assign ptr to current day
	return temp;							// return ptr to current day
}

bool DayManager::foodFileFunction(std::ifstream &input, BinarySearchTree<Day> &tree) {
	
	// validate file
	if (!input.is_open()) {
		return false;
	}
	
	std::string tempString;
	getline(input, tempstring);			// trash header line
	getline(input, tempstring);			// get calorie target
	Day::setCT(tempstring);				// set calorie target
	while (input.is_open() && !input.eof()) {
		std::string date, carb, fat, protein;
		getline(input, protein, ' ');
		getline(input, carb, ' ');
		getline(input, fat, ' ');
		getline(input, date);
		Day(fat, carb, protein, date);
		tree.insert(Day(std::stod(fat), std::stod(carb), std::stod(protein), std::stod(date)));
	}

	return true;
}

	//  void DayManager::removeToStack(Day &toRemove, BinarySearchTree<Day> &tree) {
	// 	Day temp();
	// 	tree.findForModification(toRemove, temp)
	// 	tree.remove(toRemove);
	// 	removedDays.push(temp);
// }


#endif
