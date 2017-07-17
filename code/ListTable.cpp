#include "ListTable.h"

ListTable::ListTable() {
	first = NULL;
	last = NULL;
	number = 0;
}

ListTable::~ListTable() {
	if (first != NULL)
	{
		ListNode *nowList = first;
		ListNode *nextList = first;
		while (nowList != NULL)
		{
			nextList = nowList->next;
			delete nowList;
			nowList = nextList;
		}
	}
}

void ListTable::addList(ListNode *list) {
	if (first == NULL)
	{
		first = list;
		last = list;
	}
	else
	{
		last->next = list;
		last = last->next;
	}
	number++;
}