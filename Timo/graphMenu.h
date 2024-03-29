/*
Author:		Timo Bitterli
File:		graph.h
Last edit:	12/4/2018

Graph menu is a menu that interacts with a HashTable<Day> object to display bar graphs

Current functionality:
View cal/fat/carb/prot by week ( requires at least 1 day )
View average weekly cal/fat/carb/prot ( requires at least 8 days )
*/

#ifndef GRAPHMENU_H
#define GRAPHMENU_H

#include "Hashtable.h"
#include "graph.h"

//included in graph.h:
//#include <string>
//#include <iostream>

//  gets valid int from user with error checking, validation by existence in options[]
int getInt(const std::string options);

//  CentralApplication.h should call graphMenu with its daysTable
void graphMenu(HashTable<Day>& daysTable);

int getInt(const std::string options)
{
	int input = 0;
	bool error = false;
	bool loop = true;

	do {
		loop = true;
		error = false;
		try {
			std::cin >> input;
			if (std::cin.fail()) {	// catch nonint
				std::cin.clear();	// clear error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// remove any extra characters if user typed more than one
				error = true;	// loop
				throw std::exception("Input is invalid. Please try again with an integer value.");
			}
			else {
				for (int i = 0; i < options.size(); i++) {
					if (input == (int(options[i]) - 48)) {
						error = false;
						loop = false;
						return input;
					}
					else {
						error = true;
					}
				}
			}
		}
		catch (const std::exception& ex) {
//			system("cls||clear");
			std::cout << ex.what() << std::endl;
			std::cout << "--> ";
			error = false;
		}
		catch (...) {
			system("cls||clear");
			std::cout << "Unknown error occurred" << std::endl;
			error = false;
		};
		if (error == true) {
			std::cout << "Input out of range. Please try again." << std::endl;
			std::cout << "--> ";
		}
	} while (loop == true);

	return 0;
}

void graphMenu(HashTable<Day>& daysTable)
{
	//  prepare for graph function
	int numWeeks = 0;
	int daysInFinalWeek = 0;
	int tableSize = daysTable.getCount();
	int currentWeek = 1;

	std::cout << tableSize << std::endl;
	int test = ceil(double(double(tableSize) / 7));
	std::cout << test << std::endl;

	if (tableSize > 7) {
		numWeeks = ceil(double(double(tableSize) / 7));;
		daysInFinalWeek = tableSize % 7;
	}
	else if (tableSize == 7) {
		numWeeks = 1;
		daysInFinalWeek = 7;
	}
	else {
		numWeeks = 1;
		daysInFinalWeek = tableSize % 7;
	}

	//  start menu loop
	int quit = 0;
	int option = 0;
	std::string options = "0123456789";

	int *passToGraph = NULL;  //  array of to pass to graph function;
	passToGraph = new int[tableSize];
	HashNode<Day> **tableArray;
	tableArray = new HashNode<Day>*[tableSize];

	if (tableSize > 0) {  //  require at least one day

		//  grab all data from daystable
		int counter = 0;

		for (int index = 0; index < daysTable.getSize(); index++) {
			if (daysTable[index] != nullptr) {
				tableArray[counter] = daysTable[index];
				counter++;  //  numDays
			}
		}

		do {
			
			system("cls||clear");
			std::cout << "==================" << std::endl;
			std::cout << "Graph Menu Options" << std::endl;
			std::cout << "==================" << std::endl;
			std::cout << "[1] - View data by week" << std::endl;
			std::cout << "[2] - View weekly averages" << std::endl;
			std::cout << "[0] - Return to previous Menu" << std::endl;
			std::cout << "--> ";
			options = "012";
			quit = getInt(options);
			switch (quit)
			{
			default:
				break;
			case 1:  //  weekly views
				system("cls||clear");
				std::cout << "===================" << std::endl;
				std::cout << "Weekly View Options" << std::endl;
				std::cout << "===================" << std::endl;
				std::cout << "[1] - View by calories" << std::endl;
				std::cout << "[2] - View by fats" << std::endl;
				std::cout << "[3] - View by carbohydrates" << std::endl;
				std::cout << "[4] - View by proteins" << std::endl;
				std::cout << "[0] - Return to previous Menu" << std::endl;
				std::cout << "--> ";
				options = "01234";
				switch (getInt(options))
				{
				default:
					option = 0;
					break;
				case 1:  //  calories
					currentWeek = 1;
					if (numWeeks > 1) {
						do {
							option = 1;
							if (currentWeek != numWeeks) {  //  display currentWeek
								for (int i = (currentWeek*7-7); i < 7+(currentWeek * 7 - 7); i++) {
									Day *temp = new Day;
									*temp = tableArray[i]->getData();
									passToGraph[i] = temp->totalCal();
									delete temp;
								}
								system("cls||clear");
								graph::graph(passToGraph, 7);

								if (currentWeek != 1 && currentWeek != numWeeks) {
									std::cout << "Calorie view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[1] Next  "
										<< "[2] Previous  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "012";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 1:
										currentWeek++;
										break;
									case 2:
										currentWeek--;
										break;
									}
								}
								else if (currentWeek == 1) {  //  first week, can only view next
									std::cout << "Calorie view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[1] Next  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "01";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 1:
										currentWeek++;
										break;
									}
								}
								else {  //  last week, can only view previous
									std::cout << "Calorie view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[2] Previous  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "02";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 2:
										currentWeek--;
										break;
									}
								}
							}
							else {  //  display last week
								int last = 0;
								for (int i = ( numWeeks * 7 - 7 ); i < ( numWeeks * 7 + daysInFinalWeek -7 ); i++) {
									Day *temp = new Day;
									*temp = tableArray[i]->getData();
									passToGraph[last] = temp->totalCal();
									delete temp;
									last++;
								}
								system("cls||clear");

								graph::graph(passToGraph, daysInFinalWeek);

								std::cout << "Calorie view of week " << currentWeek << "/" << numWeeks << "\t"
									<< "[2] Previous  "
									<< "[0] Return" << std::endl;
								std::cout << "--> ";
								options = "02";
								switch (getInt(options))
								{
								default:
									option = 0;
									break;
								case 2:
									currentWeek--;
									break;
								}
							}
						} while (option != 0);
					}
					else {
						for (int i = 0; i < tableSize; i++) {
							Day *temp = new Day;
							*temp = tableArray[i]->getData();
							passToGraph[i] = temp->totalCal();
							delete temp;
						}
						system("cls||clear");
						graph::graph(passToGraph, 7);

						std::cout << "Calorie view of week " << currentWeek << "/" << numWeeks << "\t"
							<< "[0] Return" << std::endl;
						std::cout << "--> ";
						options = "0";
						option = getInt(options);
					}
					break;
				case 2:  //  fats
					if (numWeeks > 1) {
						currentWeek = 1;
						do {
							option = 1;
							if (currentWeek != numWeeks) {  //  display currentWeek
								for (int i = 0; i < 7; i++) {
									Day *temp = new Day;
									*temp = tableArray[i]->getData();
									passToGraph[i] = temp->getFat();
									delete temp;
								}
								system("cls||clear");
								graph::graph(passToGraph, 7);

								if (currentWeek != 1 && currentWeek != numWeeks) {
									std::cout << "Fats view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[1] Next  "
										<< "[2] Previous  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "012";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 1:
										currentWeek++;
										break;
									case 2:
										currentWeek--;
										break;
									}
								}
								else if (currentWeek == 1) {  //  first week, can only view next
									std::cout << "Fats view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[1] Next  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "01";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 1:
										currentWeek++;
										break;
									}
								}
								else {  //  last week, can only view previous
									std::cout << "Fats view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[2] Previous  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "02";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 2:
										currentWeek--;
										break;
									}
								}
							}
							else {  //  display last week
								int last = 0;
								for (int i = ( numWeeks * 7 - 7 ); i < ( numWeeks * 7 + daysInFinalWeek -7 ); i++) {
									Day *temp = new Day;
									*temp = tableArray[i]->getData();
									passToGraph[last] = temp->getFat();
									delete temp;
									last++;
								}
								system("cls||clear");
								graph::graph(passToGraph, daysInFinalWeek);

								std::cout << "Fats view of week " << currentWeek << "/" << numWeeks << "\t"
									<< "[2] Previous  "
									<< "[0] Return" << std::endl;
								std::cout << "--> ";
								options = "02";
								switch (getInt(options))
								{
								default:
									option = 0;
									break;
								case 2:
									currentWeek--;
									break;
								}
							}
						} while (option != 0);
					}
					else {
						for (int i = 0; i < tableSize; i++) {
							Day *temp = new Day;
							*temp = tableArray[i]->getData();
							passToGraph[i] = temp->getFat();
							delete temp;
						}
						system("cls||clear");
						graph::graph(passToGraph, 7);

						std::cout << "Fats view of week " << currentWeek << "/" << numWeeks << "\t"
							<< "[0] Return" << std::endl;
						std::cout << "--> ";
						options = "0";
						option = getInt(options);
					}
					break;
				case 3:  //  carbs
					if (numWeeks > 1) {
						currentWeek = 1;
						do {
							option = 1;
							if (currentWeek != numWeeks) {  //  display currentWeek
								for (int i = 0; i < 7; i++) {
									Day *temp = new Day;
									*temp = tableArray[i]->getData();
									passToGraph[i] = temp->getCarb();
									delete temp;
								}
								system("cls||clear");
								graph::graph(passToGraph, 7);

								if (currentWeek != 1 && currentWeek != numWeeks) {
									std::cout << "Carbs view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[1] Next  "
										<< "[2] Previous  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "012";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 1:
										currentWeek++;
										break;
									case 2:
										currentWeek--;
										break;
									}
								}
								else if (currentWeek == 1) {  //  first week, can only view next
									std::cout << "Carbs view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[1] Next  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "01";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 1:
										currentWeek++;
										break;
									}
								}
								else {  //  last week, can only view previous
									std::cout << "Carbs view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[2] Previous  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "02";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 2:
										currentWeek--;
										break;
									}
								}
							}
							else {  //  display last week
								int last = 0;
								for (int i = ( numWeeks * 7 - 7 ); i < ( numWeeks * 7 + daysInFinalWeek -7 ); i++) {
									Day *temp = new Day;
									*temp = tableArray[i]->getData();
									passToGraph[last] = temp->getCarb();
									delete temp;
									last++;
								}
								system("cls||clear");
								graph::graph(passToGraph, daysInFinalWeek);

								std::cout << "Carbs view of week " << currentWeek << "/" << numWeeks << "\t"
									<< "[2] Previous  "
									<< "[0] Return" << std::endl;
								std::cout << "--> ";
								options = "02";
								switch (getInt(options))
								{
								default:
									option = 0;
									break;
								case 2:
									currentWeek--;
									break;
								}
							}
						} while (option != 0);
					}
					else {
						for (int i = 0; i < tableSize; i++) {
							Day *temp = new Day;
							*temp = tableArray[i]->getData();
							passToGraph[i] = temp->getCarb();
							delete temp;
						}
						system("cls||clear");
						graph::graph(passToGraph, 7);

						std::cout << "Carbs view of week " << currentWeek << "/" << numWeeks << "\t"
							<< "[0] Return" << std::endl;
						std::cout << "--> ";
						options = "0";
						option = getInt(options);
					}
					break;
				case 4:  //  proteins
					if (numWeeks > 1) {
						currentWeek = 1;
						do {
							option = 1;
							if (currentWeek != numWeeks) {  //  display currentWeek
								for (int i = 0; i < 7; i++) {
									Day *temp = new Day;
									*temp = tableArray[i]->getData();
									passToGraph[i] = temp->getProt();
									delete temp;
								}
								system("cls||clear");
								graph::graph(passToGraph, 7);

								if (currentWeek != 1 && currentWeek != numWeeks) {
									std::cout << "Proteins view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[1] Next  "
										<< "[2] Previous  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "012";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 1:
										currentWeek++;
										break;
									case 2:
										currentWeek--;
										break;
									}
								}
								else if (currentWeek == 1) {  //  first week, can only view next
									std::cout << "Proteins view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[1] Next  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "01";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 1:
										currentWeek++;
										break;
									}
								}
								else {  //  last week, can only view previous
									std::cout << "Proteins view of week " << currentWeek << "/" << numWeeks << "\t"
										<< "[2] Previous  "
										<< "[0] Return" << std::endl;
									std::cout << "--> ";
									options = "02";
									switch (getInt(options))
									{
									default:
										option = 0;
										break;
									case 2:
										currentWeek--;
										break;
									}
								}
							}
							else {  //  display last week
								int last = 0;
								for (int i = ( numWeeks * 7 - 7 ); i < ( numWeeks * 7 + daysInFinalWeek -7 ); i++) {
									Day *temp = new Day;
									*temp = tableArray[i]->getData();
									passToGraph[last] = temp->getProt();
									delete temp;
									last++;
								}
								system("cls||clear");
								graph::graph(passToGraph, daysInFinalWeek);

								std::cout << "Proteins view of week " << currentWeek << "/" << numWeeks << "\t"
									<< "[2] Previous  "
									<< "[0] Return" << std::endl;
								std::cout << "--> ";
								options = "02";
								switch (getInt(options))
								{
								default:
									option = 0;
									break;
								case 2:
									currentWeek--;
									break;
								}
							}
						} while (option != 0);
					}
					else {
						for (int i = 0; i < tableSize; i++) {
							Day *temp = new Day;
							*temp = tableArray[i]->getData();
							passToGraph[i] = temp->getProt();
							delete temp;
						}
						system("cls||clear");
						graph::graph(passToGraph, 7);

						std::cout << "Proteins view of week " << currentWeek << "/" << numWeeks << "\t"
							<< "[0] Return" << std::endl;
						std::cout << "--> ";
						options = "0";
						option = getInt(options);
					}
					break;
				}
				break;
			case 2:  //  weekly averages
				option = 1;
				system("cls||clear");

				if (numWeeks == 1) {
					std::cout << "There are not enough days to display weekly averages.\n"
						<< "Please ensure there are more than 7 days.\n";
					std::cout << "Type 0 to continue..." << std::endl;
					std::cout << "--> ";
					options = "0";
					getInt(options);
					break;
				}
				else {
					std::cout << "===========================" << std::endl;
					std::cout << "Weekly Average View Options" << std::endl;
					std::cout << "===========================" << std::endl;
					std::cout << "[1] - View by calories" << std::endl;
					std::cout << "[2] - View by fats" << std::endl;
					std::cout << "[3] - View by carbohydrates" << std::endl;
					std::cout << "[4] - View by proteins" << std::endl;
					std::cout << "[0] - Return to previous Menu" << std::endl;
					std::cout << "--> ";
					options = "01234";
					switch (getInt(options))
					{
					default:
						option = 0;
						break;
					case 1:  //  calories
						currentWeek = 7;  //  start with first page, then ask for others
						do {
							option = 1;

							//  start position is one week before current week
							//  unless numWeeks < currentWeek
							//  end position is currentWeek
							//int i = 0;

							//if (numWeeks < currentWeek) {
							//	i = numWeeks - ( 7 - (currentWeek - numWeeks) );
							//}
							//else {
							//	i = currentWeek * 7 - 7;
							//}
							//int tempInt = i;

							for (int i = 0;  i < numWeeks; i++) {  //  loop numWeeks times, adding 7 days to each position
								passToGraph[i] = 0;  //  start at 0, add each day, then divide for average
								if (i != numWeeks-1) {
									for (int j = i * 7; j < (i * 7 + 7); j++) {
										Day* temp = new Day;
										*temp = tableArray[j]->getData();
										passToGraph[i] += temp->totalCal();
										delete temp;
									}
									passToGraph[i] /= 7;  //  divide by days to get average
								}
								else {  //  we are at lastWeek, and need to divide by something less than 7
									for (int j = i * 7; j < (i * 7 + daysInFinalWeek); j++) {
										Day* temp = new Day;
										*temp = tableArray[j]->getData();
										passToGraph[i] += temp->totalCal();
										delete temp;
									}
									passToGraph[i] /= daysInFinalWeek;  //  divide by days to get average
								}
							}

							if (numWeeks <= 7) {  //  there is only one page--display and wait until input for return
								system("cls||clear");
								graph::graph(passToGraph, numWeeks);
								std::cout << "Average view of Calories" << "\t"
									<< "[0] Return" << std::endl;
								std::cout << "--> ";
								options = "0";
								option = getInt(options);
							}
							else {
								system("cls||clear");
								graph::graph(passToGraph, numWeeks);

								do {
									option = 1;			
									if (currentWeek <= 7) {  //  first page
										std::cout << "Average view of Calories" << "\t"
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "0";
									}
									else if (numWeeks - currentWeek <= 7) {  //  at final page
										std::cout << "Average view of Calories" << "\t"
											<< "[2] Previous  "
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "02";
									}
									else {  //  at a middle page
										std::cout << "Average view of Calories" << "\t"
											<< "[1] Next  "
											<< "[2] Previous  "
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "012";
									}

									switch (getInt(options)) {
									default:  //  return to prev menu
										option = 0;
										break;
									case 1:  //  next page
										currentWeek += 7;
										break;
									case 2:  //  previous page
										currentWeek -= 7;
										break;
									}

								} while (option != 0);
							}
						} while (option != 0);
						break;  //  end case for average calories
					case 2:  //  fats
						currentWeek = 7;  //  start with first page, then ask for others
						do {
							option = 1;

							for (int i = 0;  i < numWeeks; i++) {  //  loop numWeeks times, adding 7 days to each position
								passToGraph[i] = 0;  //  start at 0, add each day, then divide for average
								if (i != numWeeks-1) {
									for (int j = i * 7; j < (i * 7 + 7); j++) {
										Day* temp = new Day;
										*temp = tableArray[j]->getData();
										passToGraph[i] += temp->getFat();
										delete temp;
									}
									passToGraph[i] /= 7;  //  divide by days to get average
								}
								else {  //  we are at lastWeek, and need to divide by something less than 7
									for (int j = i * 7; j < (i * 7 + daysInFinalWeek); j++) {
										Day* temp = new Day;
										*temp = tableArray[j]->getData();
										passToGraph[i] += temp->getFat();
										delete temp;
									}
									passToGraph[i] /= daysInFinalWeek;  //  divide by days to get average
								}
							}

							if (numWeeks <= 7) {  //  there is only one page--display and wait until input for return
								system("cls||clear");
								graph::graph(passToGraph, numWeeks);
								std::cout << "Average view of Fats" << "\t"
									<< "[0] Return" << std::endl;
								std::cout << "--> ";
								options = "0";
								option = getInt(options);
							}
							else {
								system("cls||clear");
								graph::graph(passToGraph, numWeeks);

								do {
									option = 1;
									if (currentWeek <= 7) {  //  first page
										std::cout << "Average view of Fats" << "\t"
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "0";
									}
									else if (numWeeks - currentWeek <= 7) {  //  at final page
										std::cout << "Average view of Fats" << "\t"
											<< "[2] Previous  "
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "02";
									}
									else {  //  at a middle page
										std::cout << "Average view of Fats" << "\t"
											<< "[1] Next  "
											<< "[2] Previous  "
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "012";
									}

									switch (getInt(options)) {
									default:  //  return to prev menu
										option = 0;
										break;
									case 1:  //  next page
										currentWeek += 7;
										break;
									case 2:  //  previous page
										currentWeek -= 7;
										break;
									}

								} while (option != 0);
							}
						} while (option != 0);
						break;
					case 3:  //  carbs
						currentWeek = 7;  //  start with first page, then ask for others
						do {
							option = 1;

							for (int i = 0;  i < numWeeks; i++) {  //  loop numWeeks times, adding 7 days to each position
								passToGraph[i] = 0;  //  start at 0, add each day, then divide for average
								if (i != numWeeks-1) {
									for (int j = i * 7; j < (i * 7 + 7); j++) {
										Day* temp = new Day;
										*temp = tableArray[j]->getData();
										passToGraph[i] += temp->getCarb();
										delete temp;
									}
									passToGraph[i] /= 7;  //  divide by days to get average
								}
								else {  //  we are at lastWeek, and need to divide by something less than 7
									for (int j = i * 7; j < (i * 7 + daysInFinalWeek); j++) {
										Day* temp = new Day;
										*temp = tableArray[j]->getData();
										passToGraph[i] += temp->getCarb();
										delete temp;
									}
									passToGraph[i] /= daysInFinalWeek;  //  divide by days to get average
								}
							}

							if (numWeeks <= 7) {  //  there is only one page--display and wait until input for return
								system("cls||clear");
								graph::graph(passToGraph, numWeeks);
								std::cout << "Average view of Carbs" << "\t"
									<< "[0] Return" << std::endl;
								std::cout << "--> ";
								options = "0";
								option = getInt(options);
							}
							else {
								system("cls||clear");
								graph::graph(passToGraph, numWeeks);

								do {
									option = 1;
									if (currentWeek <= 7) {  //  first page
										std::cout << "Average view of Carbs" << "\t"
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "0";
									}
									else if (numWeeks - currentWeek <= 7) {  //  at final page
										std::cout << "Average view of Carbs" << "\t"
											<< "[2] Previous  "
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "02";
									}
									else {  //  at a middle page
										std::cout << "Average view of Carbs" << "\t"
											<< "[1] Next  "
											<< "[2] Previous  "
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "012";
									}

									switch (getInt(options)) {
									default:  //  return to prev menu
										option = 0;
										break;
									case 1:  //  next page
										currentWeek += 7;
										break;
									case 2:  //  previous page
										currentWeek -= 7;
										break;
									}

								} while (option != 0);
							}
						} while (option != 0);
						break;
					case 4:  //  proteins
						currentWeek = 7;  //  start with first page, then ask for others
						do {
							option = 1;

							for (int i = 0; i < numWeeks; i++) {  //  loop numWeeks times, adding 7 days to each position
								passToGraph[i] = 0;  //  start at 0, add each day, then divide for average
								if (i != numWeeks - 1) {
									for (int j = i * 7; j < (i * 7 + 7); j++) {
										Day* temp = new Day;
										*temp = tableArray[j]->getData();
										passToGraph[i] += temp->getProt();
										delete temp;
									}
									passToGraph[i] /= 7;  //  divide by days to get average
								}
								else {  //  we are at lastWeek, and need to divide by something less than 7
									for (int j = i * 7; j < (i * 7 + daysInFinalWeek); j++) {
										Day* temp = new Day;
										*temp = tableArray[j]->getData();
										passToGraph[i] += temp->getProt();
										delete temp;
									}
									passToGraph[i] /= daysInFinalWeek;  //  divide by days to get average
								}
							}

							if (numWeeks <= 7) {  //  there is only one page--display and wait until input for return
								system("cls||clear");
								graph::graph(passToGraph, numWeeks);
								std::cout << "Average view of Proteins" << "\t"
									<< "[0] Return" << std::endl;
								std::cout << "--> ";
								options = "0";
								option = getInt(options);
							}
							else {
								system("cls||clear");
								graph::graph(passToGraph, numWeeks);

								do {
									option = 1;
									if (currentWeek <= 7) {  //  first page
										std::cout << "Average view of Proteins" << "\t"
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "0";
									}
									else if (numWeeks - currentWeek <= 7) {  //  at final page
										std::cout << "Average view of Proteins" << "\t"
											<< "[2] Previous  "
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "02";
									}
									else {  //  at a middle page
										std::cout << "Average view of Proteins" << "\t"
											<< "[1] Next  "
											<< "[2] Previous  "
											<< "[0] Return" << std::endl;
										std::cout << "--> ";
										options = "012";
									}

									switch (getInt(options)) {
									default:  //  return to prev menu
										option = 0;
										break;
									case 1:  //  next page
										currentWeek += 7;
										break;
									case 2:  //  previous page
										currentWeek -= 7;
										break;
									}

								} while (option != 0);
							}
						} while (option != 0);
						break;
					}
				}
				break;
			}
		} while (quit != 0);
	}
	 else {
		 system("cls||clear");
		 std::cout << "Graph requires at least one day to display." << std::endl
			 << "Please add more days." << std::endl
			 << "Press ENTER to continue...";
		 std::cin.get();
	}

	 delete [] passToGraph;
	 delete [] tableArray;
	 system("cls||clear");
}  //  end graphMenu function

#endif
