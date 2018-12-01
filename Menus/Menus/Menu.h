#pragma once
#ifndef MENU_H
#define MENU_H

const int PROMPT_SIZE = 51;			// MAXIMUM STRING SIZE

class Menu
{
private:
	char input[PROMPT_SIZE];		// User's input
public:
	Menu();				// Constructor
	void mainMenu();		// Main menu output
	void addNewDataMenu();          // Add new Data Menu
	void deleteDataMenu();		// Delete Data Menu
	void findAndDisplayMenu();      // Find and display Menu
	void listDataPrint();           // Print data in hash table sequence
	void printTree();		// Print Indented tree
	void pIT();
	void printEfficieny();          // Print Efficiency
	void printTeamChoices();

	char* itemListPrompt();		// Set input
	char* simplePrompt();		// Set input
};
#endif 

