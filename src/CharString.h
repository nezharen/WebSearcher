/*
*
* CharString.h
* Author: Zhang Kai
* The defination of class CharString
*/

#ifndef CHAR_STRING_H
#define CHAR_STRING_H

#include <stdio.h>
#define STRING_MIN_SIZE 50		//The default capacity
#define SIZE_STEP 10			//The enlarging step

//The defination of class CharString
class CharString
{
public:
	CharString();
	CharString(const char &ch);
	CharString(const char *s);
	CharString(const CharString &s);
	void operator = (const char &ch);
	void operator = (const char *s);
	void operator = (const CharString &s);
	void operator += (const char &ch);
	void operator += (const char *s);
	void operator += (const CharString &s);
	bool operator == (const char &ch);
	bool operator == (const char *s);
	bool operator == (const CharString &s);
	bool operator < (const char &ch);
	bool operator < (const char *s);
	bool operator < (const CharString &s);
	virtual ~CharString();
	char *getBase();
	int getLength();
	int getSize();
	void enlargeSize();
	int compare(const CharString &s);
	void makeEmpty();
	void decChar(const int &x);
	CharString subString(const int &x, const int &y);
	void sscanf();
	void fsscanf(FILE *fp);
	void sprintf();
	void fsprintf(FILE *fp);
private:
	char *base;			//A char array, containing the chars of a string
	int *length;			//The length of the string
	int *size;			//The capacity of the string
};

#endif

