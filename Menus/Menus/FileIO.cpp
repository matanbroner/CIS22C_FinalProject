// Implement files
#define _CRT_SECURE_NO_WARNINGS
#include "FileIO.h"
#include <fstream>
#include <iostream>

using namespace std;

// This constructor is used when reading from the file
File::File(const char* fname, ReadOnlyMode mode) :
	fileObj(fname, ios_base::in)
{
	if (fileObj.fail()) {
		throw "Failed to open file for input";
	}
}

// This constructor is used when writing new contents
// to the file.  The old contents are deleted
File::File(const char * fname, WriteOnlyMode mode) :
	fileObj(fname, ios_base::out | ios_base::trunc)
{
	if (fileObj.fail()) {
		throw "Failed to open file for output";
	}
}

void File::readOneLine(char buffer[MAX_LINE_SIZE])
{													                    // Read up to MAX_LINE_SIZE - 1 characters into buffer, until \n is seen.
	fileObj.getline(buffer, MAX_LINE_SIZE);			// Does not store the \n into the string.  Always places the \0.
}

void File::writeOneLine(const char* buffer) {
	fileObj << buffer << endl;
}

void File::writeOneLine(int num) {
	fileObj << num << endl;
}

void File::writeOneLine(double num) {
	fileObj << num << endl;
}

bool File::eof()
{
	return fileObj.eof();
}

