#pragma once
#include <iostream>

typedef struct LinkedNode{
	int x;
	int y;
	LinkedNode *next;
}LinkedNode;

class MyLinkedList
//���������࣬ÿ�����Ϊһ���������(x,y)
{
public:
	MyLinkedList();
	~MyLinkedList();

	void addNode(int xValue,int yValue);		//������ĩ�����(x,y)���
	void deleteNextNode(LinkedNode* pre);		//ɾ��pre������һ�����
	
	LinkedNode *first;		//��Ԫ�ص�ַ
	LinkedNode *last;		//ĩ��Ԫ�ص�ַ
	int length;				//�����ȣ������������ĸ���
};

