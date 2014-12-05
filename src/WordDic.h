/*
*
* WordDic.h
* Author: Zhang Kai
* The defination of class WordDic
*/

#ifndef WORD_DIC_H
#define WORD_DIC_H
#define DIC_MAX_SIZE 300000		//The capacity of the dictionary

class CharString;

//The defination of enum type CodeType
typedef enum {UTF, GBK} CodeType;

//The defination of class WordDic
class WordDic
{
public:
	WordDic();
	~WordDic();
	bool loadFile(const char *file);
	void updateFile();
	bool getSorted();
	void sortWord();
	void qSort(const int &x, const int &y);
	void setCodeType(const CodeType &type);
	bool findWord(CharString word);
	bool find(const int &x, const int &y, CharString word);
	int getMaxLength();
private:
	CharString *fileName;		//The file name of the dictionary
	CharString *base;		//A string array, containing the words
	int *length;			//The number of the words
	bool *sorted;			//Whether the dictionary is in sort
	int *maxLength;		//The max length of the words
	CodeType *codeType;		//The code type of the dictionary
};

#endif

