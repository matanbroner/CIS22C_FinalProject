/*
Author:		Timo Bitterli
File:		graph.h
Last edit:	12/4/2018

Graph menu is a menu that interacts with a HashTable<Day> object to display bar graphs

Current functionality:
View cal/fat/carb/prot by week ( requires at least 1 day )

Current wip:
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

//hashtable
//int getSize();  // returns available size of table
//HashNode<T>* operator[](int); // allows user to treat table as an array by using bracketed index notation

int getInt(const std::string options)
{
	int input = 0;
	bool error = false;

	do {
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
		}
		catch (...) {
			system("cls||clear");
			std::cout << "Unknown error occurred" << std::endl;
		};

	} while (error == true);

	return 0;
}

void graphMenu(HashTable<Day>& daysTable)
{
	//  prepare for graph function
	int numWeeks = 0;
	int daysInFinalWeek = 0;
	int tableSize = daysTable.getCount();
	int currentWeek = 1;

	if (tableSize > 7) {
		numWeeks = ceil(tableSize / 7);
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
	int option = 0;
	std::string options = "";

	int passToGraph[7];  //  array of size 7 to pass to graph function;

	if (tableSize > 0) {  //  require at least one day
		do {
			option = 0;  //  just in case

			system("cls||clear");
			std::cout << "==================" << std::endl;
			std::cout << "Graph Menu Options" << std::endl;
			std::cout << "==================" << std::endl;
			std::cout << "[1] - View data by week" << std::endl;
			std::cout << "[2] - View weekly averages" << std::endl;
			std::cout << "[0] - Return to previous Menu" << std::endl;
			std::cout << "--> ";
			options = "012";
			switch (getInt(options))
			{
			default:
				option = 0;
				break;
			case 1:
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
				case 1:
					if (numWeeks > 1) {
						currentWeek = 1;
						do {
							if (currentWeek != numWeeks) {  //  display currentWeek
								for (int i = 0; i < 7; i++) {
									Day *temp = new Day;
									*temp = daysTable[i]->getData();
									passToGraph[i] = temp->totalCal();
									delete temp;
								}
								system("cls||clear");
								graph::graph(passToGraph, 7);

								if (currentWeek != 1 && currentWeek != numWeeks) {
									std::cout << "Weekly view of week " << currentWeek << "/" << numWeeks << "\t"
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
									std::cout << "Weekly view of week " << currentWeek << "/" << numWeeks << "\t"
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
									std::cout << "Weekly view of week " << currentWeek << "/" << numWeeks << "\t"
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
								for (int i = 0; i < daysInFinalWeek; i++) {
									Day *temp = new Day;
									*temp = daysTable[i]->getData();
									passToGraph[i] = temp->totalCal();
									delete temp;
								}
								system("cls||clear");
								graph::graph(passToGraph, daysInFinalWeek);

								std::cout << "Weekly view of week " << currentWeek << "/" << numWeeks << "\t"
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
							*temp = daysTable[i]->getData();
							passToGraph[i] = temp->totalCal();
							delete temp;
						}
						system("cls||clear");
						graph::graph(passToGraph, tableSize);
					}
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				}
				break;
			case 2:
				system("cls||clear");

				if (numWeeks == 1) {
					std::cout << "There are not enough days to display weekly averages.\n"
						<< "Please ensure there are more than 7 days.\n";
					std::cout << "Press ENTER to continue...";
					std::cin.get();
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
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					}
				}
				break;
			}
		} while (option != 0);
	}
	 else {
		 system("cls||clear");
		 std::cout << "Graph requires at least one day to display." << std::endl
			 << "Please add more days." << std::endl
			 << "Press ENTER to continue...";
		 std::cin.get();
	}
}  //  end graphMenu function

#endif
