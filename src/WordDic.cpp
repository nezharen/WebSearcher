/*
*
* WordDic.cpp
* Author: Zhang Kai
* The member functions of class WordDic
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "WordDic.h"
#include "CharString.h"

//Constructor
WordDic::WordDic()
{
	fileName = new CharString("");
	base = new CharString[DIC_MAX_SIZE];
	length = new int(0);
	sorted = new bool(true);
	maxLength = new int(0);
	codeType = new CodeType(UTF);
}

//Destructor
WordDic::~WordDic()
{
	delete codeType;
	delete maxLength;
	delete sorted;
	delete length;
	delete [] base;
	delete fileName;
}

//Read the words from the dictionary file
bool WordDic::loadFile(const char *file)
{
	FILE *fp = fopen(file, "r");

	if (fp == NULL)
		return false;
	(*fileName) = file;
	(*length) = 0;
	(*sorted) = true;
	(*maxLength) = 0;
	while (true)
	{
		(*length)++;
		base[*length].fsscanf(fp);
		if (base[*length] == "")
		{
			(*length)--;
			break;
		}
		if (base[*length].getLength() > (*maxLength))
			(*maxLength) = base[*length].getLength();
		if ((*length) > 1)
		if (base[*length] < base[(*length) - 1])
			(*sorted) = false;
	}
	fclose(fp);
	return true;
}

//Update the dictionary file
void WordDic::updateFile()
{
	FILE *fp = fopen(fileName->getBase(), "w");

	for (int i = 1; i <= (*length); i++)
	{
		base[i].fsprintf(fp);
		fprintf(fp, "\n");
	}
	fclose(fp);
}

//Get whether the dictionary is sorted
bool WordDic::getSorted()
{
	return (*sorted);
}

//Sort the words
void WordDic::sortWord()
{
	if (!(*sorted))
	{
		qSort(1, (*length));
		(*sorted) = true;
	}
}

//Quick sort
void WordDic::qSort(const int &x, const int &y)
{
	int i = x, j = y;
	CharString k = base[(i + j ) >> 1];
	CharString t;

	while (i < j)
	{
		while (base[i] < k)
			i++;
		while (k < base[j])
			j--;
		if (i <= j)
		{
			t = base[i];
			base[i] = base[j];
			base[j] = t;
			i++;
			j--;
		}
	}
	if (x < j) qSort(x, j);
	if (y > i) qSort(i, y);
}

//Set the code type
void WordDic::setCodeType(const CodeType &type)
{
	(*codeType) = type;
}

//Find whether a word exists in the dictionary
bool WordDic::findWord(CharString word)
{
	return find(1, (*length), word);
}

//Find word using bisection method
bool WordDic::find(const int &x, const int &y, CharString word)
{
	int k = ((x + y) >> 1);

	if (base[k] == word)
		return true;
	if (word < base[k])
	{
		if (x < k)
			if (find(x, k - 1, word))
				return true;
	}
	else
		if (y > k)
			if (find(k + 1, y, word))
				return true;
	return false;
}

//Get the max length of the words in the dictionary
int WordDic::getMaxLength()
{
	return (*maxLength);
}

