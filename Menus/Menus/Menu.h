#pragma once
const int PROMPT_SIZE = 51;			// MAXIMUM STRING SIZE

class Menu
{
private:
	char input[PROMPT_SIZE];		// User's input
public:
	Menu();						    // Constructor
	void mainMenu();				// Main menu output
	char* itemListPrompt();			// Set input
	char* simplePrompt();			// Set input
};


