/*
*
* WebSearcher.h
* Author: Zhang Kai
* The defination of class WebSearcher
*/

#ifndef WEB_SEARCHER_H
#define WEB_SEARCHER_H
#include "WordDic.h"
#include "Stack.h"
#include "LinkedList.h"

//The defination of class WebSearcher
class WebSearcher
{
public:
	WebSearcher();
	~WebSearcher();
	void analyze(const char *fileName);
	void loadDic();
	void parse();
	void htmlParse(const char *fileName);
private:
	WordDic *dic;				//The dictionary
	CodeType *codeType;			//The code type of the HTML file
	Stack<CharString> *stack;		//The stack to save the labels
	LinkedList<CharString> *result;		//The linkedlist to save the results
};

#endif

