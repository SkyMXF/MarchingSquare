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
//�����б��࣬ÿ�����ָ��һ����������
public:
	ListTable();
	~ListTable();

	void addList(ListNode *list);
	//��table��������һ���µ�list
	//��Ҫ���������new
	//����	ListNode *newList = new ListNode;
	//		newList->thisList = new MyLinkedList;
	//		newList->next = NULL;
	//		...(��newList���Ԫ�ػ���в���)
	//		table.addList(newList);

	ListNode *first;	//��һ�������ָ��
	ListNode *last;		//���һ������ָ��
	int number;			//������������
};