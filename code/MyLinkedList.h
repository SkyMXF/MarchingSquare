#pragma once
#include <iostream>

typedef struct LinkedNode{
	int x;
	int y;
	LinkedNode *next;
}LinkedNode;

class MyLinkedList
//坐标链表类，每个结点为一个点的坐标(x,y)
{
public:
	MyLinkedList();
	~MyLinkedList();

	void addNode(int xValue,int yValue);		//在链表末端添加(x,y)结点
	void deleteNextNode(LinkedNode* pre);		//删除pre结点后面一个结点
	
	LinkedNode *first;		//首元素地址
	LinkedNode *last;		//末端元素地址
	int length;				//链表长度，即所包含结点的个数
};

