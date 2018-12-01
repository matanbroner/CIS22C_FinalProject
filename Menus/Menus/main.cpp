// Implement files						
#define _CRT_SECURE_NO_WARNINGS
// Include rest of header files for functions
#include "Check.h"	
#include "Menu.h"	
#include "Options.h"

#include <iomanip>
#include <iostream>
using namespace std;

Menu mainOptions;					    // Menu class
Check menuInput;					    // Check class
Options option;



int main()
{
	while (true)
	{
		mainOptions.mainMenu();
		if (!menuInput.isValid(mainOptions.itemListPrompt(), 1, 9)) { // Get the input & validate.  Fill in 'menuInput.input' if successful.
			continue;
		}

		switch (menuInput.getIntCheck())                    // Choose selected option
		{
		case 1:
			// Add new data	
			// option.newData();
			break;
		case 2:
			// Delete data	
			// option.deleteData();
			break;
		case 3:
			// Find and display one data record using the primary key	
			// option.findData();
			break;
		case 4:
			// List data in hash table sequence			
			// option.listDataHash();
			break;
		case 5:
			// List data in key sequence (sorted)		
			// option.efficiency();
			break;
		case 6:
			// Print indented tree 			
			// option.printIndentedTree();
			break;
		case 7:
			// Efficiency			
			// option.efficiency();
			break;
		case 8:
			// <Team choice menu option>
			// option.teamChoice();
			break;

	
		case 9:	// Main menu selection 9: end program
	
			cout << "\n\nGoodbye\n\n";
			exit(0);  //Use exit(0) to completey close program 
			break;
		}

	}

	return 0;
}
