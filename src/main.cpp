/*
*
* main.cpp
* Author: Zhang Kai
* The main function
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "WebSearcher.h"
#include "CharString.h"

int main()
{
	WebSearcher app;		//Define an application of WebSearcher
	CharString fileName;		//The HTML file name to be parsed

	printf("Please enter the file name of the HTML webpage:\n");
	fileName.sscanf();
	app.htmlParse(fileName.getBase());
	return 0;
}

