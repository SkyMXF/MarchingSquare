#pragma once
#include "MyLinkedList.h"

typedef struct ListNode {
	MyLinkedList *thisList;
	ListNode *next;
	~ListNode()
	{
		if (thisList != NULL)
		{
			delete thisList;
			thisList = NULL;
		}
	}
}ListNode;

class ListTable {
//链表列表类，每个结点指向一个坐标链表
public:
	ListTable();
	~ListTable();

	void addList(ListNode *list);
	//在table的最后添加一个新的list
	//需要在类外进行new
	//例：	ListNode *newList = new ListNode;
	//		newList->thisList = new MyLinkedList;
	//		newList->next = NULL;
	//		...(对newList添加元素或进行操作)
	//		table.addList(newList);

	ListNode *first;	//第一个链表的指针
	ListNode *last;		//最后一个链表指针
	int number;			//保存的链表个数
};