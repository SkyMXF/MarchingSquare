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

	/*****************ͼ��任����******************/
	void bayer2rgb5(MAR &result, MAR &origin);
	//resultΪ��ά����originΪ��ά����

	void mirror_extension(MAR &result, MAR &origin, int vsize, int hsize);
	//resultΪorigin��չ

	void rgb2gray(MAR &result, MAR &origin);
	//��άorigin������RGBֵת��Ϊ�Ҷ�ͼ��result(��ά)

	void imfilter_symmetric(MAR &result, MAR &origin);
	//�˲�

	void im2bw(MAR &result, MAR &origin, int bw);
	//��ֵ�任������bw����Ϊ1��С�ڵ���bw����Ϊ0

	/*****************Ѱ�ҵȸ��ߺ���****************/
	void FindContours(MAR &gray, ListTable *listPointer, int lineNumber);
	//�����˲���ĻҶ�ͼ��gray(��ά)���ҳ�lineNumber���߶ȵĵȸ��ߣ��洢��lineNumber��������

	void MarchingSquare(MAR &origin, ListTable &list);
	//originΪ��ά�ڰ�ͼ�񣬸��ڵȸ�������Ϊ1�����ڻ���ڵȸ�������Ϊ0��list���ܰ������������ͬ����֮����һ��x = -1�Ľ�����

	void FindStart(MAR &originEx, MAR &memory, int &x, int &y);
	//MarchingSquare���ߺ������ںڰ�ͼ��origin�У�ΪѰ�ҵȸ�����һ����ʼ�㡣
	//memory��¼������������ȷ��Ϊ�ȸ��ߵĵ㣬��������Ϊ1�ĵ�������
	//��(x,y)λ�ÿ�ʼ����������������ʼʱ����(x,y)
	//����x = -1ʱ����ʾ������������ʼ��

	short cal(MAR &origin, int x, int y);
	/*MarchingSquare���ߺ�����������(x,y)Ϊ���ϸ���ĸ����ڷ�����ۼ�ֵ
	+---+---+
	| 8 | 4 |
	+---+---+
	| 1 | 2 |
	+---+---+
	*/

	void edgeProcess(ListTable &list, int height, int width);
	//MarchingSquare���ߺ������߽紦��������������˴����߽磬������Ҫ����ֽ�Ϊ�������

	bool edgeJudge(int x, int y, int height, int width);
	//MarchingSquare���ߺ������ж�(x,y)�Ƿ��ڸ�Ϊheighe����Ϊwidth�ľ���߽���

	int cutJudge(MyLinkedList *nowList);
	//MarchingSquare���ߺ�����������Ҫ��nowList�ֽ�Ϊ������������1ʱ������ֽ�

	bool nearJudge(int x1, int y1, int x2, int y2);
	//MarchingSquare���ߺ������ж�(x1,y1),(x2,y2)�Ƿ�����
};

