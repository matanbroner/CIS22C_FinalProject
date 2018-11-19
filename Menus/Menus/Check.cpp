// Implement files
#define _CRT_SECURE_NO_WARNINGS
#include "Check.h"
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

// This class stops dumb users from breaking the program by typing the wrong input when a Menu pops up
// Can used for other things besides menu, like just checking if a input is valid

// Constructor, Set input to empty
Check::Check()
{
	strcpy(input, "");
}

// Convert C-string to uppercase
void Check::cstrUpper(char* userinput)
{
	while (*userinput != '\0')
	{
		*userinput = toupper(*userinput);
		userinput++;
	}
}

// Returns char input
char* Check::getCheck()
{
	return input;
}

// Returns integer input
int Check::getIntCheck()
{
	return atoi(input);
}

// Checks user's input is between set integer paramaeters.
// Only stores the user's input if it was valid.
bool Check::isValid(char* userinput, int startRange, int endRange)
{
	int intinput;	// Convert the c-string to an integer
	intinput = atoi(userinput);
	if (intinput < startRange || intinput > endRange) // Check input
	{													   // Invad input
		cout << "\nPlease enter a number in the range "    // Display valid input
			<< startRange << " - " << endRange << "." << endl << endl;
		return false;
	}
	strcpy(input, userinput); // Reset input
	return true;
}

// Check's users input is between set char paramaeters
// Only stores the user's input if it was valid.
bool Check::isValid(char* userinput)
{
	cstrUpper(userinput);  	// Convert char to uppercase

	if (strcmp(userinput, "Y") != 0 && strcmp(userinput, "N") != 0) // Check input
	{
		cout << "\nPlease enter Y for Yes or N for no." << endl << endl;  // Display input
		return false;
	}
	strcpy(input, userinput); // Reset input
	return true;
}
