#pragma once

#include "Bitmap.h"
#include "MAR.h"
#include "MyLinkedList.h"
#include "ListTable.h"

class ContoursTools
{
public:
	ContoursTools() {};
	~ContoursTools() {};

	/*****************图像变换函数******************/
	void bayer2rgb5(MAR &result, MAR &origin);
	//result为三维矩阵，origin为二维矩阵

	void mirror_extension(MAR &result, MAR &origin, int vsize, int hsize);
	//result为origin扩展

	void rgb2gray(MAR &result, MAR &origin);
	//三维origin，根据RGB值转换为灰度图像result(二维)

	void imfilter_symmetric(MAR &result, MAR &origin);
	//滤波

	void im2bw(MAR &result, MAR &origin, int bw);
	//二值变换，大于bw的设为1，小于等于bw的设为0

	/*****************寻找等高线函数****************/
	void FindContours(MAR &gray, ListTable *listPointer, int lineNumber);
	//根据滤波后的灰度图像gray(二维)，找出lineNumber个高度的等高线，存储在lineNumber个链表中

	void MarchingSquare(MAR &origin, ListTable &list);
	//origin为二维黑白图像，高于等高线区域为1，低于或等于等高线区域为0，list可能包含多个链表，不同链表之间用一个x = -1的结点隔开

	void FindStart(MAR &originEx, MAR &memory, int &x, int &y);
	//MarchingSquare工具函数。在黑白图像origin中，为寻找等高线找一个起始点。
	//memory记录了已搜索或已确认为等高线的点，遇到其中为1的点则跳过
	//从(x,y)位置开始搜索，搜索到的起始时保存(x,y)
	//返回x = -1时，表示已搜索不到起始点

	short cal(MAR &origin, int x, int y);
	/*MarchingSquare工具函数，返回以(x,y)为左上格的四个相邻方格的累加值
	+---+---+
	| 8 | 4 |
	+---+---+
	| 1 | 2 |
	+---+---+
	*/

	void edgeProcess(ListTable &list, int height, int width);
	//MarchingSquare工具函数。边界处理，部分链表包含了大量边界，可能需要将其分解为多个链表

	bool edgeJudge(int x, int y, int height, int width);
	//MarchingSquare工具函数。判断(x,y)是否在高为heighe，宽为width的矩阵边界上

	int cutJudge(MyLinkedList *nowList);
	//MarchingSquare工具函数。计算需要将nowList分解为几个链表，返回1时则无需分解

	bool nearJudge(int x1, int y1, int x2, int y2);
	//MarchingSquare工具函数。判断(x1,y1),(x2,y2)是否相邻
};

