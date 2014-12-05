/*
*
* CharString.cpp
* Author: Zhang Kai
* The member functions of class CharString
*/

#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include "CharString.h"

//Constructor
CharString::CharString()
{
	size = new int(STRING_MIN_SIZE);
	base = new char[(*size)];
	length = new int;
	makeEmpty();
}

//Constructor
CharString::CharString(const char &ch)
{
	size = new int(STRING_MIN_SIZE);
	base = new char[(*size)];
	length = new int;
	base[0] = ch;
	base[1] = '\0';
	*length = 1;
}

//Constructor
CharString::CharString(const char *s)
{
	size = new int(STRING_MIN_SIZE);
	base = new char[(*size)];
	length = new int;
	makeEmpty();
	while (s[*length] != '\0')
	{
		base[*length] = s[*length];
		(*length)++;
		if ((*length) == (*size))
			enlargeSize();
	}
	base[*length] = '\0';
}

//Constructor
CharString::CharString(const CharString &s)
{
	size = new int(*s.size);
	base = new char[(*size)];
	length = new int;
	*length = (*s.length);
	for (int i = 0; i <= (*length); i++)
		base[i] = s.base[i];
}

//Overloading "="
void CharString::operator = (const char &ch)
{
	makeEmpty();
	(*this) += ch;
}

//Overloading "="
void CharString::operator = (const char *s)
{
	makeEmpty();
	(*this) += s;
}

//Overloading "="
void CharString::operator = (const CharString &s)
{
	makeEmpty();
	(*this) += s;
}

//Overloading "+="
void CharString::operator += (const char &ch)
{
	base[*length] = ch;
	(*length)++;
	if ((*length) == (*size))
		enlargeSize();
	base[*length] = '\0';
}

//Overloading "+="
void CharString::operator += (const char *s)
{
	for (int i = 0; ; i++)
	{
		if (s[i] == '\0')
			break;
		base[*length] = s[i];
		(*length)++;
		if ((*length) == (*size))
			enlargeSize();
	}
	base[*length] = '\0';
}

//Overloading "+="
void CharString::operator += (const CharString &s)
{
	for (int i = 0; i < (*s.length); i++)
	{
		base[*length] = s.base[i];
		(*length)++;
		if ((*length) == (*size))
			enlargeSize();
	}
	base[*length] = '\0';
}

//Overloading "=="
bool CharString::operator == (const char &ch)
{
	CharString t(ch);
	if (compare(t) == 0)
		return true;
	return false;
}

//Overloading "=="
bool CharString::operator == (const char *s)
{
	CharString t(s);
	if (compare(t) == 0)
		return true;
	return false;
}

//Overloading "=="
bool CharString::operator == (const CharString &s)
{
	if (compare(s) == 0)
		return true;
	return false;
}

//Overloading "<"
bool CharString::operator < (const char &ch)
{
	CharString t(ch);
	if (compare(t) < 0)
		return true;
	return false;
}

//Overloading "<"
bool CharString::operator < (const char *s)
{
	CharString t(s);
	if (compare(t) < 0)
		return true;
	return false;
}

//Overloading "<"
bool CharString::operator < (const CharString &s)
{
	if (compare(s) < 0)
		return true;
	return false;
}

//Destructor
CharString::~CharString()
{
	delete length;
	delete [] base;
	delete size;
}

//Get the array base
char *CharString::getBase()
{
	return base;
}

//Get the length of the string
int CharString::getLength()
{
	return (*length);
}

//Get the capacity
int CharString::getSize()
{
	return (*size);
}

//Enlarge the capacity
void CharString::enlargeSize()
{
	char *p;

	p = new char[(*size) * SIZE_STEP];
	for (int i = 0; i < (*size); i++)
		p[i] = base[i];
	delete [] base;
	base = p;
	(*size) *= SIZE_STEP;
}

//Compare two strings
//First by length, then by chars
int CharString::compare(const CharString &s)
{
	int l = (*length);
	if ((*s.length) < l)
		l = (*s.length);
	for (int i = 0; i < l; i++)
		if (base[i] < s.base[i])
			return -1;
		else
			if (base[i] > s.base[i])
				return 1;
	if ((*length) < (*s.length))
		return -1;
	else
		if ((*length) > (*s.length))
			return 1;
		else
			return 0;
}

//Empty the string
void CharString::makeEmpty()
{
	base[0] = '\0';
	(*length) = 0;
}

//Delete the last x chars of the string
void CharString::decChar(const int &x)
{
	(*length) -= x;
	if ((*length) < 0)
		(*length) = 0;
	base[*length] = '\0';
}

//Return the sub string from x to y
CharString CharString::subString(const int &x, const int &y)
{
	CharString ans = "";

	for (int i = x; i <= y; i++)
		ans += base[i];
	return ans;
}

//Reading a string from terminal
void CharString::sscanf()
{
	char ch;

	makeEmpty();
	while (true)
	{
		scanf("%c", &ch);
		if (ch < 0)
			break;
		if ((!isspace(ch)) && (!iscntrl(ch)))
			break;
	}
	(*this) += ch;
	while (true)
	{
		scanf("%c", &ch);
		if (ch >= 0)
			if (isspace(ch) || iscntrl(ch))
				break;
		(*this) += ch;
	}
}

//Reading a string from file
void CharString::fsscanf(FILE *fp)
{
	char ch;

	makeEmpty();
	while (true)
	{
		fscanf(fp, "%c", &ch);
		if (feof(fp))
			return;
		if (ch < 0)
			break;
		if ((!isspace(ch)) && (!iscntrl(ch)))
			break;
	}
	(*this) += ch;
	while (true)
	{
		fscanf(fp, "%c", &ch);
		if (feof(fp))
			break;
		if (ch >= 0)
			if (isspace(ch) || iscntrl(ch))
				break;
		(*this) += ch;
	}
}

//Writing a string to terminal
void CharString::sprintf()
{
	for (int i = 0; i < (*length); i++)
		printf("%c", base[i]);
}

//Writing a string to file
void CharString::fsprintf(FILE *fp)
{
	for (int i = 0; i < (*length); i++)
		fprintf(fp, "%c", base[i]);
}

