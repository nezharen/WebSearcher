/*
*
* Stack.h
* Author: Zhang Kai
* The defination of template Stack
*/

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#define STACK_MIN_SIZE 50		//The default capacity
#define SIZE_STEP 10			//The enlarging step

//The defination of template Stack
template <class DataType>
class Stack
{
public:
	Stack();
	virtual ~Stack();
	bool isEmpty();
	void enlargeSize();
	void push(const DataType &x);
	DataType pop();
	DataType peek();
private:
	DataType *base;			//An array, containing the datas
	int *top;			//The top of the stack
	int *size;			//The capacity of the stack
};

//Constructor
template <class DataType>
Stack<DataType>::Stack()
{
	size = new int(STACK_MIN_SIZE);
	base = new DataType[(*size)];
	top = new int(-1);
}

//Destructor
template <class DataType>
Stack<DataType>::~Stack()
{
	delete top;
	delete [] base;
	delete size;
}

//Return whether the stack is empty
template <class DataType>
bool Stack<DataType>::isEmpty()
{
	if ((*top) < 0)
		return true;
	return false;
}

//Enlarge the capacity
template <class DataType>
void Stack<DataType>::enlargeSize()
{
	DataType *p;

	p = new DataType[(*size) * SIZE_STEP];
	for (int i = 0; i < (*size); i++)
		p[i] = base[i];
	delete [] base;
	base = p;
	(*size) *= SIZE_STEP;
}

//Push
template <class DataType>
void Stack<DataType>::push(const DataType &x)
{
	(*top)++;
	if ((*top) == (*size))
		enlargeSize();
	base[*top] = x;
}

//Pop
template <class DataType>
DataType Stack<DataType>::pop()
{
	DataType ans;

	if (isEmpty())
	{
		printf("Exception occured! Stack is empty but poping.\n");
		exit(0);
	}
	ans = base[*top];
	(*top)--;
	return ans;
}

//Peek
template <class DataType>
DataType Stack<DataType>::peek()
{
	if (isEmpty())
	{
		printf("Exception occured! Stack is empty but peeking.\n");
		exit(0);
	}
	return base[*top];
}

#endif

