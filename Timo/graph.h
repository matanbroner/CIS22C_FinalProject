/*
Author:		Timo Bitterli
File:		graph.h
Last edit:	12/4/2018

Graph is a bar graph function that takes an array of integers and outputs a bar graph onto a 80 x 25 console window in ascii.
The output is scaled by the maximum, so if the max is an outlier, the other bars may appear excessively small.

The current max of number of bars output is 7, the number of days in a week, though 8 is the max that would fit on screen.
The height used for the bar graph is 78 of 80, so the remaining two lines can be used for pagination or menus outside of graph.

The graph function takes an array and an array size ( expected <= 7 )
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>

namespace graph {
	//  global variables

	int numBars = 7;  //  display 7 days at a time
	const int width = 80, height = 25;  //  console window
	const int maxHeight = height - 2;	//  2 for pagination ( 1 for display, 1 for input )
	const int leftAxisBuffer = 6;  //  size of gap left of y-axis ( increase for bigger digit numbers x-axis: max digits = barWidth-2 )
	const int tickBuffer = leftAxisBuffer - 1;  //  buffer between y-axis and 0 ( used to position ticks )
	const int barWidth = 7;  //  width of one bar ( increase for bigger digit numbers on x-axis: max digits = barWidth-2 )
	const int bufferSize = 2;  //  buffer between bars

	std::string leftGap(leftAxisBuffer, ' ');  //  gap between y-axis and 0
	std::string buffer(bufferSize, ' ');  //  buffer between bars
	std::string edge = "|";  //  the x-axis edge
	std::string top((barWidth - 2), '_');  //  the top of bar
	std::string yaxisRepeatS((barWidth + bufferSize - 1) / 2, '-');  // y-axis number of '-'
	std::string yaxisRepeat = yaxisRepeatS + "|" + yaxisRepeatS;  //  the y-axis with tick marks
	std::string yaxisEnd(width - (leftAxisBuffer + 2 + 1 + (numBars * barWidth + (numBars * bufferSize))), '-');  //  put a few '-' at end of x-axis to fill out axis to 79
	std::string barSpaces((barWidth - 2), ' ');  //  spaces between bars = the width of bar minus two ( for bars on sides )


	//  functions

	//  returns max int in array
	int findMax(const int inputArray[], const int inputArraySize);

	// draws a bar graph for int array, arraySize must be <= 7
	// arraySize determines the number of bars drawn from int array, starting from 0 ( graph does not manage your array )
	void graph(const int inputArray[], const int inputArraySize);


	//  function definitions

	int findMax(const int inputArray[], const int inputArraySize)
	{
		int max = 0;

		for (int i = 0; i < inputArraySize; i++) {
			if (inputArray[i] > max) {
				max = inputArray[i];
			}
		}

		return max;
	}

	void graph(const int inputArray[], const int inputArraySize)
	{
		if (inputArraySize < 7)  //  display 7 days at a time maximum
			numBars = inputArraySize;

		double maxValue = findMax(inputArray, inputArraySize);  //  double used to find y-axis scale
		int leftBuffer = findMax(inputArray, inputArraySize);  //  integer used as numdigits for formatting

		std::string value = std::to_string(leftBuffer); // or wherever it's from;
		const int digits = value.size();  //  max numdigits in data

		std::string graphOutput[height];  //  string array to hold bar graph

		int i = height - 4;  // -1, start from 0
							 //  -4: one for y axis, one for numbers, one for page prompt & page entry

		graphOutput[0] += leftGap + '|';;
		graphOutput[i] += leftGap + "+";

		graphOutput[i] += "-";
		for (int j = 0; j < numBars; j++) {
			graphOutput[i] += yaxisRepeat;  //  when time, create num "-" of of barwidth and buffer numBars + 2 - 1
		}
		graphOutput[i] += yaxisEnd;  //  fill out to end of screen, maybe remove if it looks weird

		// begin x-axis tick values
		i++;
		graphOutput[i] += leftGap + " "; // was 9, now 6+1
		for (int j = 0; j < inputArraySize; j++) {
			std::string temp = std::to_string(inputArray[j]);;
			//  the number of digits = temp.size();
			//  the number of spaces = barWidth - digits +/- 1 depending on odd/even
			//  two spaces default buffer, then up to barWidth for digits
			//  barWidth is max for odd, barWidth-1 is max for even

			graphOutput[i] += buffer;

			int spacesLeft = ((barWidth - temp.size()) / 2);
			int spacesRight = spacesLeft;

			if ((temp.size() % 2) == 0)  // if even number of digits
				spacesRight++;
			//  else { do nothing } if odd number of digits, keep spaces same
			for (int k = 0; k < spacesLeft; k++)  //  add spaces left
				graphOutput[i] += " ";
			graphOutput[i] += temp;  //  add tick value 
			for (int k = 0; k < spacesRight; k++)  //  add spaces right
				graphOutput[i] += " ";
		}

		// find tickScale for y-axis

		//  one level of bar height is equal to half of the tickScale
		//  we round the value to the nearest halfTickscale

		int tickScale = ceil(maxValue / 10);
		std::string tickScaleS = std::to_string(tickScale);

		double findTick = double(maxValue / 10);


		if (findTick >= 2.5 && findTick < 7.5) {  //  rounds to 5
			tickScaleS[tickScaleS.size()] = 5;
		}
		else if (findTick >= 7.5) {  //  round to next 10
			findTick = double((maxValue + 10) / 10);
			tickScale = findTick;

			tickScaleS = std::to_string(tickScale);
			tickScaleS[tickScaleS.size()] = 0;
		}
		else {  //  < 2.5 round to 0
			tickScaleS[tickScaleS.size()] = 0;
		}

		tickScale = stoi(tickScaleS);

		if (tickScaleS[tickScaleS.size()] != 0 && tickScaleS[tickScaleS.size()] != 5)
			tickScale++;  //  if small tickscale, increment because max can be higher than tickscale*10

		i = i - 2;  //  go back to before y axis and build bar graphs vertically

		const int bottom = i;  //  used to begin loops from bottom
		int count = 0;  //  place on y-axis
		int innerCount = 1;  //  current tick

		//  populate left ticks
		for (i = bottom; innerCount <= 10; i--) {  //  loop from bottom to top
			if (count % 2 != 0) {  //  if count is odd, add tick
				std::string tempTick = std::to_string(tickScale*innerCount);
				int tempTickSize = tickBuffer - tempTick.size();
				std::string tickBufferS(tempTickSize, ' ');  //  determine number of spaces by number of digits of tick: the more digits, the less spaces
				graphOutput[i] += tickBufferS + std::to_string(tickScale*innerCount);
				graphOutput[i] += " " + edge;  //  add space after tick, then add y-axis line
				innerCount++;
			}
			else {  //  else just add line
				graphOutput[i] = leftGap + edge;
			}
			count++;
		}

		//  go back to bottom and draw all bars
		count = 0;
		i = bottom;

		for (int j = 0; j < numBars; j++) {
			bool barDone = false;

			for (i = bottom; i >= 0; i--) {
				if ((inputArray[j] - (double(tickScale) / 2)) >(double(tickScale) / 2 * count)) {
					graphOutput[i] += buffer + '|' + barSpaces + '|';  //  
				}
				else if (barDone == false) {
					barDone = true;
					graphOutput[i] += buffer + ' ' + top + ' ';
				}
				else {
					graphOutput[i] += buffer + ' ' + barSpaces + ' ';
				}
				count++;  //  number of bars drawn
			}
			count = 0;
		}

		for (int i = 0; i < height - 2; i++) {  //  height - 2 because we only use 78
			std::cout << graphOutput[i] << std::endl;
		}
	}  //  end graph function
}  //  end namespace

#endif
