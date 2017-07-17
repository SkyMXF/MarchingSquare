#include "MyLinkedList.h"

MyLinkedList::MyLinkedList()
{
	first = NULL;
	last = NULL;
	length = 0;
}


MyLinkedList::~MyLinkedList()
{
	if (first != NULL)
	{
		LinkedNode *thisNode = first;
		LinkedNode *nextNode = first;
		for (int i = 0; i < length; i++)
		{
			nextNode = thisNode->next;
			if (thisNode != NULL)
			{
				delete thisNode;
				thisNode = nextNode;
			}
		}
	}
}

void MyLinkedList::addNode(int xValue, int yValue)
{
	LinkedNode *newNode = new LinkedNode;
	newNode->x = xValue;
	newNode->y = yValue;
	newNode->next = NULL;

	if (first == NULL)
	{
		first = newNode;
		last = newNode;
	}
	else
	{
		last->next = newNode;
		last = last->next;
	}
	length++;
}

void MyLinkedList::deleteNextNode(LinkedNode *pre)
{
	LinkedNode *deleteNode = pre->next;
	pre->next = deleteNode->next;
	if (deleteNode == last) last = pre;
	delete deleteNode;
	deleteNode = NULL;
	length--;
}
