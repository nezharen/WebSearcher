/*
*
* WebSearcher.cpp
* Author: Zhang Kai
* The member functions of class WebSearcher
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include "WebSearcher.h"
#include "CharString.h"

//Constructor
WebSearcher::WebSearcher()
{
	dic = new WordDic;
	codeType = new CodeType(UTF);
	stack = new Stack<CharString>;
	result = new LinkedList<CharString>;
}

//Destructor
WebSearcher::~WebSearcher()
{
	delete result;
	delete stack;
	delete codeType;
	delete dic;
}

//Analyzing a HTML file, getting the code type, and the paragraphs
void WebSearcher::analyze(const char *fileName)
{
	FILE *fin = fopen(fileName, "r");
	FILE *fout = fopen("WebSearcher.temp", "w");		//The file name to save the paragraphs
	char ch;
	CharString s;
	int p = 0;						//The number of "<p>" now in stack
	bool pop;

	if (fin == NULL)
	{
		printf("Can't open file %s!\n", fileName);
		exit(0);
	}

	(*codeType) = UTF;					//Default code type is UTF
	while (true)
	{
		fscanf(fin, "%c", &ch);
		if (feof(fin))
			break;
		if (ch == '<')					//The beginning of a label
		{
			s = "";
			while (true)
			{
				fscanf(fin, "%c", &ch);
				if (ch < 0)			//If word, the add to the back of s
					s += ch;
				else
					if (isalpha(ch))
						s += ch;
					else
					{
						if (ch == '>')
							break;
						if (ch == '/')	//Found"/XX>", pop
						{
							if (stack->pop() == CharString("p"))
								p--;
							while (ch != '>')
								fscanf(fin, "%c", &ch);
							s = "";
							break;
						}
						else
						{
							if (!(s == ""))	//Found"<XX", push
							{
								stack->push(s);
								if (s == CharString("p"))	//label <p>
									p++;
								if (s == CharString("meta"))	//label <meta>, try to get the code type
									while (true)
									{
										s.fsscanf(fin);
										if (s.subString(0, 6) == CharString("charset"))
											if (s.subString(8, 9) == CharString("gb"))
												(*codeType) = GBK;
										if (s.subString(s.getLength() -1, s.getLength() - 1) == CharString(">"))
										{
											stack->pop();
											s = "";
											goto loop;
										}
									}
								s = "";
							}
							pop = false;
							while (true)
							{
								fscanf(fin, "%c", &ch);
								if (ch == '>')
									break;
								if (ch == '/')			//Found "<XX />", pop
									pop = true;
								if (ch >= 0)
									if (!isalpha(ch))
										pop = false;
							}
							if (pop)
								if (stack->pop() == CharString("p"))
									p--;
							loop:;
							break;
						}
					}
			}
			if (!(s == ""))
			{
				stack->push(s);
				if (s == CharString("p"))
					p++;
				s = "";
			}
		}
		else
			if (p > 0)				//Found paragraph
			{
				while (ch == '&')		//Deal with "&" words
				{
					while (true)
					{
						fscanf(fin, "%c", &ch);
						if (ch >= 0)
							if (!isalpha(ch))
								break;
					}
				}
				if (ch < '0')
					fprintf(fout, "%c", ch);
			}
	}
	fclose(fin);
	fclose(fout);
	printf("HTML analyzing successful.\n");
}

//Load the dictionary
void WebSearcher::loadDic()
{
	if ((*codeType) == UTF)		//Load the dictionary of specific code type
	{
		if (!dic->loadFile("UTF-8.dic"))
		{
			printf("Error while loading UTF dictionary!\n");
			exit(0);
		}
		dic->setCodeType(UTF);
		printf("The char code is UTF.\n");
	}
	else
	{
		if (!dic->loadFile("ANSI.dic"))
		{
			printf("Error while loading GBK dictionary!\n");
			exit(0);
		}
		dic->setCodeType(GBK);
		printf("The char code is GBK.\n");
	}

	if (!dic->getSorted())			//If not in sort, then sort it and update the dictionary
	{
		printf("The dictionary is not in sort and will be updated to sort.\n");
		dic->sortWord();
		dic->updateFile();
	}
}

//Do parsing to the paragraphs
//Divide the paragraph into some words and find whether they exist in the dictionary. If exist then save it to a file
void WebSearcher::parse()
{
	FILE *fin = fopen("WebSearcher.temp", "r");		//The file of the paragraphs
	FILE *fout = fopen("WebSearcher.txt", "w");		//The file of the results
	int maxLength = dic->getMaxLength();			//Max length of words in the dictionary
	CharString s = "";
	Stack<char> mem, t;
	char ch;
	
	while (true)
	{
		while (s.getLength() < maxLength)		//Make a string of maxLength
		{
			fscanf(fin, "%c", &ch);
			if (feof(fin))
				goto step;
			s += ch;
			mem.push(ch);				//Stack push is synchronous with CharString s
		}
		while (!dic->findWord(s))			//Find string s in the dictionary
		{
			if (s.getLength() > 1)
			{
				s.decChar(1);			//If not exist then dec the last char
				t.push(mem.pop());		//Stack mem pop, and push it to t
			}
			else
			{
				s = "";
				break;
			}
		}
		if (!(s == ""))				//If exist, then insert s to the linkedlist, and write it to file
		{
			result->insert(s);
			s.fsprintf(fout);
			fprintf(fout, "\n");
		}
		s = "";
		while (!mem.isEmpty())
			mem.pop();
		while (!t.isEmpty())				//Add the chars of Stack t to s
		{
			mem.push(t.pop());
			s += mem.peek();
		}
	}
	step:;							//After the file is end
	while (!mem.isEmpty())
	{
		while (!dic->findWord(s))
		{
			if (s.getLength() > 1)
			{
				s.decChar(1);
				t.push(mem.pop());
			}
			else
			{
				s = "";
				break;
			}
		}
		if (!(s == ""))
		{
			result->insert(s);
			s.fsprintf(fout);
			fprintf(fout, "\n");
		}
		s = "";
		while (!mem.isEmpty())
			mem.pop();
		while (!t.isEmpty())
		{
			mem.push(t.pop());
			s += mem.peek();
		}
	}
	fclose(fin);
	fclose(fout);
	printf("HTML parsing successful.\n");
	printf("The result has been saved to \"WebSearcher.txt\".\n");
}

//Use the member functions to parse a HTML
void WebSearcher::htmlParse(const char *fileName)
{
	analyze(fileName);
	loadDic();
	parse();
}

