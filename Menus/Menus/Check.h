#pragma once


const int CHECK_INPUT_SIZE = 81;	// CONSTANT ARRAY SIZE

class Check
{
private:
	char input[CHECK_INPUT_SIZE];	 // User's Input
	void cstrUpper(char*);			 // C-string to uppercase
public:
	Check();						 // Constructor
	char* getCheck();			     // Returns the char input
	int	  getIntCheck();		     // Returns the integer input
	bool isValid(char*, int, int);   // Returns true if the input is valid
	bool isValid(char*);			 // Returns true if the input is valid
};


