#pragma once
/*
 String Assistant Class
 This class is used for hashing a date of type string.
 The three functions present in the class allow the same functionality but with different input:
 Date, Person, or string
 */
#ifndef StringAssistant_h
#define StringAssistant_h
#include <algorithm>
#include "Food.h"
class StringAssistant
{
private:

public:
	static int hashFoodByName(Food&);
	static int hashStringName(std::string);
	static void trimSpaces(std::string&);
	static void clearInput();
	static double calculateStringSimilarity(const std::string&, const std::string&);
	static double similarity(const std::string, const std::string);
};

int StringAssistant::hashFoodByName(Food& food)
{
	std::string name = food.getName();
	int sum = 0;
	for (char c : name)
	{
		sum += (int)c;
	}
	while (sum > 9)
	{
		std::string stringSum = std::to_string(sum);
		sum = 0;
		for (char c : stringSum)
		{
			sum += c - '0';
		}
	}
	//std::cout << "SUM: " << sum << std::endl;
	return sum;
}

int StringAssistant::hashStringName(std::string name)
{
	Food temp(name, 1, 1, 1);
	return hashFoodByName(temp);
}

void StringAssistant::trimSpaces(std::string& word)
{
	std::string trimmed = "";
	for (int i = 0; i < word.length(); i++)
	{
		if ((i == 0 || i == word.length() - 1) && isspace(word[i]))
			continue;
		if (!isspace(word[i]))
			trimmed += word[i];
		if ((isspace(word[i]) && (!isspace(word[i - 1]) && !isspace(word[i + 1]))))
			trimmed += word[i];
	}
	word = trimmed;
}

void StringAssistant::clearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // removes illegal value
}

double StringAssistant::similarity(std::string word1, std::string word2)
{
	if (word1.length() == word2.length())
		return calculateStringSimilarity(word1, word2);
	std::string longerWord, shorterWord;
	double maxSimilarityIndex = -1;
	int minLength;
	if (word1.length() > word2.length()) { longerWord = word1; shorterWord = word2; }
	else { longerWord = word2; shorterWord = word1; }

	minLength = shorterWord.length();
	for (int i = 0; i <= longerWord.length() / minLength; i++)
	{
		std::string sub;
		try {
			sub = longerWord.substr(i*minLength, minLength + 1);
		}
		catch (std::out_of_range)
		{
			if (longerWord.length() % minLength == 0) return maxSimilarityIndex;
			else sub = longerWord.substr(i*minLength, longerWord.length() - 1);
		}
		double s = calculateStringSimilarity(sub, shorterWord);
		std::cout << "Comparing " << sub << " + " << shorterWord << std::endl;
		if (s > maxSimilarityIndex)
			maxSimilarityIndex = s;
	}
	return maxSimilarityIndex;
}

double StringAssistant::calculateStringSimilarity(const std::string& word1, const std::string& word2)
{
	unsigned const int length1 = word1.length();
	unsigned int length2 = word2.length();
	if (length1 == 0)
		return length2 == 0 ? 1.0 : 0.0; // return 100% or 0% depending on empty strings
	unsigned int distance = (std::max(length1, length2) / 2) - 1; // average combined length - 1
	bool* word1_match = new bool[length1];
	bool* word2_match = new bool[length2];
	std::fill(word1_match, word1_match + length1, false); // fill with false
	std::fill(word2_match, word2_match + length2, false); // fill with false
	int matches = 0;
	for (int index = 0; index < length1; index++)
	{
		int ending = std::min(index + distance + 1, length2); // either length 2 is smaller or the current index plus the average distance plus 1
		for (int subIndex = std::max(0u, index - distance); subIndex < ending; subIndex++) // read up to the found ending, essentially reading from the current index through found ending
		{
			if (!word2_match[subIndex] && word1[index] == word2[subIndex])
			{
				word1_match[index] = true;
				word2_match[subIndex] = true;
				matches++;
				break;
			}
		}
	}
	if (matches == 0) // if no matches
		return 0.0;
	double totalMetric = 0.0;
	unsigned int index2 = 0;
	for (int index1 = 0; index1 < length1; index1++)
	{
		if (word1_match[index1]) // if found index where words matched
		{
			while (!word2_match[index2]) index2++; // keep moving until you get to a match index
			if (word1[index1] != word2[index2]) totalMetric += 0.5; // but if the words don't have the same value at the index where they each show matching, total metric (error) increases
			index2++;
		}
	}
	double dMatches = matches;
	delete[] word1_match;
	delete[] word2_match;
	return (dMatches / length1 + dMatches / length2 + (dMatches - totalMetric) / dMatches) / 3.0;
	// returning the averages of number of matches divided by each length, plus the percent error between the matches and the total metric.
}



#endif /* StringAssistant
