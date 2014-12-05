/*
*
* LinkedList.h
* Author: Zhang Kai
* The defination of template LinkedList
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

template <class DataType>
class LinkedList;

//The defination of template LinkedListNode
template <class DataType>
class LinkedListNode
{
public:
	LinkedListNode();
	virtual ~LinkedListNode();
	friend class LinkedList<DataType>;
private:
	DataType *data;				//The data area
	LinkedListNode *next;			//The pointer area, pointing to next node
};

//Constructor
template <class DataType>
LinkedListNode<DataType>::LinkedListNode()
{
	data = new DataType;
	next = NULL;
}

//Destructor
template <class DataType>
LinkedListNode<DataType>::~LinkedListNode()
{
	delete data;
}

//The defination of template LinkedList
//Defining a linkedlist with a head node
template <class DataType>
class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();
	void insert(const DataType &x);
	bool find(const DataType &x);
	void remove(const DataType &x);
private:
	LinkedListNode<DataType> *head;		//head node
};

//Constructor
template <class DataType>
LinkedList<DataType>::LinkedList()
{
	head = new LinkedListNode<DataType>;
}

//Destructor
template <class DataType>
LinkedList<DataType>::~LinkedList()
{
	LinkedListNode<DataType> *p, *q;

	p = head;
	q = head->next;
	while (true)
	{
		delete p;
		p = q;
		if (p == NULL)
			break;
		q = p->next;
	}
}

//Insert a data
template <class DataType>
void LinkedList<DataType>::insert(const DataType &x)
{
	LinkedListNode<DataType> *p = new LinkedListNode<DataType>;
	*(p->data) = x;
	p->next = head->next;
	head->next = p;
}

//Find whether a data exists
template <class DataType>
bool LinkedList<DataType>::find(const DataType &x)
{
	LinkedListNode<DataType> *p = head->next;

	while (p != NULL)
	{
		if (*(p->data) == x)
			return true;
		p = p->next;
	}
	return false;
}

//Delete the nodes containing a data
template <class DataType>
void LinkedList<DataType>::remove(const DataType &x)
{
	LinkedListNode<DataType> *p, *q;

	p = head;
	q = head->next;
	while (q != NULL)
	{
		if (*(q->data) == x)
		{
			p->next = q->next;
			delete q;
			q = p->next;
		}
		else
		{
			p = q;
			q = p->next;
		}
	}
}

#endif

