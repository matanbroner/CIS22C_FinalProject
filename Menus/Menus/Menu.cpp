// Implement files
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <iostream>
#include <iomanip>
using namespace std;

// All menus and large print statements should be made as functions in this class to make life easier


// Constructor, set to empty
Menu::Menu()
{
	strcpy(input, "\0");
}

// Display main menu
void Menu::mainMenu()
{			
	cout << "\n\n\tFood Program\n";	// Display header
	cout << "\tMain Menu\n\n";

	cout << "1. Add new data\n";		     // Display inputs
	cout << "2. Delete data\n";
	cout << "3. Find and display one data record using the primary key\n";
	cout << "4. List data in hash table sequence\n";
	cout << "5. List data in key sequence (sorted)\n";
	cout << "6. Print indented tree\n";
	cout << "7. Efficiency\n";
	cout << "8. <Team choice menu option>\n";
	cout << "9. Quit\n\n";
}



// Set input
char* Menu::itemListPrompt()
{
	cout << "Enter your choice: ";
	cin >> input;
	return input;
}

// Set input 
char* Menu::simplePrompt()
{
	cin >> input;
	return input;
}
