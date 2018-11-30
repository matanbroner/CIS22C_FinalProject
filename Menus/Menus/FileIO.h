#pragma once
#ifndef FILEIO_H
#define FILEIO_H

// Implement files
#include <fstream>
#include <iostream>
using namespace std;

const int F_SIZE = 31;			// CONSTANT ARRAY SIZE
const int MAX_LINE_SIZE = 1024;		// We assume no line in the text file is bigger than this

class ReadOnlyMode {};
class WriteOnlyMode {};

class File
{
private:
	char fileName[F_SIZE];						// File Name
	fstream fileObj;						// fstream object
public:
	// This ctor opens an existing file for reading
	File(const char* fileName, ReadOnlyMode mode);

	// This ctor opens a file for writing.  If the file already existed,
	// the old contents are discarded before we start writing.
	File(const char* fileName, WriteOnlyMode mode);

	void readOneLine(char buffer[MAX_LINE_SIZE]);       // fills in buffer from the next line in fileObj
	void writeOneLine(const char* line);                // we add a newline character
	void writeOneLine(int);                             // we add a newline character
	void writeOneLine(double);                          // we add a newline character

	bool  eof();					    // Check end of the file
};

#endif
