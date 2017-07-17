#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

#include "ContoursTools.h"

void ContoursTools::bayer2rgb5(MAR & result, MAR & origin)
//result为三维矩阵，origin为二维矩阵
{
	MAR mirrorExtend(origin.height + 2, origin.width + 2, 2);
	mirror_extension(mirrorExtend, origin, 1, 1);

	int rHeight = result.height;
	int rWidth = result.width;
	int mHeight = mirrorExtend.height;
	int mWidth = mirrorExtend.width;

	int i, j;
	for (i = 0; i < rHeight; i++)
	{
		for (j = 0; j < rWidth; j++)
		{
			if ((i + 1) % 2)
			{
				if ((j + 1) % 2)
				{
					result.data[i*rWidth * 3 + j * 3 + 0] =
						(mirrorExtend.data[i*mWidth + j] + mirrorExtend.data[i*mWidth + j + 2] + mirrorExtend.data[(i + 2)*mWidth + j] + mirrorExtend.data[(i + 2)*mWidth + j + 2]) / 4.0 + 0.5;
					result.data[i*rWidth * 3 + j * 3 + 1] =
						(mirrorExtend.data[i*mWidth + j + 1] + mirrorExtend.data[(i + 2)*mWidth + j + 1] + mirrorExtend.data[(i + 1)*mWidth + j] + mirrorExtend.data[(i + 1)*mWidth + j + 2]) / 4.0 + 0.5;
					result.data[i*rWidth * 3 + j * 3 + 2] =
						origin.data[i*rWidth + j];
				}
				else
				{
					result.data[i*rWidth * 3 + j * 3 + 0] =
						(mirrorExtend.data[i*mWidth + j + 1] + mirrorExtend.data[(i + 2)*mWidth + j + 1]) / 2.0 + 0.5;
					result.data[i*rWidth * 3 + j * 3 + 1] =
						origin.data[i*rWidth + j];
					result.data[i*rWidth * 3 + j * 3 + 2] =
						(mirrorExtend.data[(i + 1)*mWidth + j] + mirrorExtend.data[(i + 1)*mWidth + j + 2]) / 2.0 + 0.5;
				}
			}
			else
			{
				if ((j + 1) % 2)
				{
					result.data[i*rWidth * 3 + j * 3 + 0] =
						(mirrorExtend.data[(i + 1)*mWidth + j] + mirrorExtend.data[(i + 1)*mWidth + j + 2]) / 2.0 + 0.5;
					result.data[i*rWidth * 3 + j * 3 + 1] =
						origin.data[i*rWidth + j];
					result.data[i*rWidth * 3 + j * 3 + 2] =
						(mirrorExtend.data[i*mWidth + j + 1] + mirrorExtend.data[(i + 2)*mWidth + j + 1]) / 2.0 + 0.5;
				}
				else
				{
					result.data[i*rWidth * 3 + j * 3 + 0] =
						origin.data[i*rWidth + j];
					result.data[i*rWidth * 3 + j * 3 + 1] =
						(mirrorExtend.data[i*mWidth + j + 1] + mirrorExtend.data[(i + 2)*mWidth + j + 1] + mirrorExtend.data[(i + 1)*mWidth + j] + mirrorExtend.data[(i + 1)*mWidth + j + 2]) / 4.0 + 0.5;
					result.data[i*rWidth * 3 + j * 3 + 2] =
						(mirrorExtend.data[i*mWidth + j] + mirrorExtend.data[i*mWidth + j + 2] + mirrorExtend.data[(i + 2)*mWidth + j] + mirrorExtend.data[(i + 2)*mWidth + j + 2]) / 4.0 + 0.5;
				}
			}
		}
	}
}

void ContoursTools::mirror_extension(MAR & result, MAR & origin, int vsize, int hsize)
//result为origin按镜面方式扩展
{
	int i, j;
	int r, c;

	int height = origin.height;
	int width = origin.width;

	//中间部分,r,c为result的行和列
	for (i = 0; i < height; i++)
	{
		r = i + vsize;
		for (j = 0; j < width; j++)
		{
			c = j + hsize;
			result.data[r*(width + 2 * hsize) + c] = origin.data[i*width + j];
		}
	}

	//上边界扩展,r,c为result中所需复制元素的行和列
	for (i = vsize - 1; i >= 0; i--)
	{
		r = vsize + vsize - i;
		for (j = hsize; j < width + hsize; j++)
		{
			c = j;
			result.data[i*(width + 2 * hsize) + j] = result.data[r*(width + 2 * hsize) + c];
		}
	}

	//右边界扩展,r,c为result中所需复制元素的行和列
	for (i = 0; i < vsize + height; i++)
	{
		r = i;
		for (j = hsize + width; j < 2 * hsize + width; j++)
		{
			c = hsize + width - 1 - (j - (hsize + width - 1));
			result.data[i*(width + 2 * hsize) + j] = result.data[r*(width + 2 * hsize) + c];
		}
	}

	//下边界扩展,r,c为result中所需复制元素的行和列
	for (i = vsize + height; i < 2 * vsize + height; i++)
	{
		r = vsize + height - 1 - (i - (vsize + height - 1));
		for (j = hsize; j < 2 * hsize + width; j++)
		{
			c = j;
			result.data[i*(width + 2 * hsize) + j] = result.data[r*(width + 2 * hsize) + c];
		}
	}

	//左边界扩展,r,c为result中所需复制元素的行和列
	for (i = 0; i < 2 * vsize + height; i++)
	{
		r = i;
		for (j = hsize - 1; j >= 0; j--)
		{
			c = hsize + hsize - j;
			result.data[i*(width + 2 * hsize) + j] = result.data[r*(width + 2 * hsize) + c];
		}
	}
}

void ContoursTools::rgb2gray(MAR & result, MAR & origin)
//三维origin，根据RGB值转换为灰度图像result(二维)
{
	int height = origin.height;
	int width = origin.width;
	int i, j;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			result.data[i*width + j] =
				0.2989*origin.data[i*width * 3 + j * 3 + 0] + 0.587*origin.data[i*width * 3 + j * 3 + 1] + 0.114*origin.data[i*width * 3 + j * 3 + 2] + 0.5;
		}
	}
}

void ContoursTools::imfilter_symmetric(MAR & result, MAR & origin)
{
	double H[400] =	//滤波数据，Matlab代码fspecial('gaussian',[20,20],4)生成
	{
		0.0000, 0.0001, 0.0001, 0.0002, 0.0002, 0.0003, 0.0004, 0.0005, 0.0006, 0.0006, 0.0006, 0.0006, 0.0005, 0.0004, 0.0003, 0.0002, 0.0002, 0.0001, 0.0001, 0.0000,
		0.0001, 0.0001, 0.0002, 0.0003, 0.0004, 0.0006, 0.0007, 0.0009, 0.0010, 0.0011, 0.0011, 0.0010, 0.0009, 0.0007, 0.0006, 0.0004, 0.0003, 0.0002, 0.0001, 0.0001,
		0.0001, 0.0002, 0.0003, 0.0005, 0.0007, 0.0009, 0.0012, 0.0014, 0.0016, 0.0017, 0.0017, 0.0016, 0.0014, 0.0012, 0.0009, 0.0007, 0.0005, 0.0003, 0.0002, 0.0001,
		0.0002, 0.0003, 0.0005, 0.0007, 0.0011, 0.0014, 0.0019, 0.0022, 0.0025, 0.0027, 0.0027, 0.0025, 0.0022, 0.0019, 0.0014, 0.0011, 0.0007, 0.0005, 0.0003, 0.0002,
		0.0002, 0.0004, 0.0007, 0.0011, 0.0015, 0.0021, 0.0027, 0.0033, 0.0037, 0.0039, 0.0039, 0.0037, 0.0033, 0.0027, 0.0021, 0.0015, 0.0011, 0.0007, 0.0004, 0.0002,
		0.0003, 0.0006, 0.0009, 0.0014, 0.0021, 0.0029, 0.0037, 0.0045, 0.0050, 0.0054, 0.0054, 0.0050, 0.0045, 0.0037, 0.0029, 0.0021, 0.0014, 0.0009, 0.0006, 0.0003,
		0.0004, 0.0007, 0.0012, 0.0019, 0.0027, 0.0037, 0.0047, 0.0057, 0.0065, 0.0069, 0.0069, 0.0065, 0.0057, 0.0047, 0.0037, 0.0027, 0.0019, 0.0012, 0.0007, 0.0004,
		0.0005, 0.0009, 0.0014, 0.0022, 0.0033, 0.0045, 0.0057, 0.0069, 0.0078, 0.0083, 0.0083, 0.0078, 0.0069, 0.0057, 0.0045, 0.0033, 0.0022, 0.0014, 0.0009, 0.0005,
		0.0006, 0.0010, 0.0016, 0.0025, 0.0037, 0.0050, 0.0065, 0.0078, 0.0089, 0.0094, 0.0094, 0.0089, 0.0078, 0.0065, 0.0050, 0.0037, 0.0025, 0.0016, 0.0010, 0.0006,
		0.0006, 0.0011, 0.0017, 0.0027, 0.0039, 0.0054, 0.0069, 0.0083, 0.0094, 0.0100, 0.0100, 0.0094, 0.0083, 0.0069, 0.0054, 0.0039, 0.0027, 0.0017, 0.0011, 0.0006,
		0.0006, 0.0011, 0.0017, 0.0027, 0.0039, 0.0054, 0.0069, 0.0083, 0.0094, 0.0100, 0.0100, 0.0094, 0.0083, 0.0069, 0.0054, 0.0039, 0.0027, 0.0017, 0.0011, 0.0006,
		0.0006, 0.0010, 0.0016, 0.0025, 0.0037, 0.0050, 0.0065, 0.0078, 0.0089, 0.0094, 0.0094, 0.0089, 0.0078, 0.0065, 0.0050, 0.0037, 0.0025, 0.0016, 0.0010, 0.0006,
		0.0005, 0.0009, 0.0014, 0.0022, 0.0033, 0.0045, 0.0057, 0.0069, 0.0078, 0.0083, 0.0083, 0.0078, 0.0069, 0.0057, 0.0045, 0.0033, 0.0022, 0.0014, 0.0009, 0.0005,
		0.0004, 0.0007, 0.0012, 0.0019, 0.0027, 0.0037, 0.0047, 0.0057, 0.0065, 0.0069, 0.0069, 0.0065, 0.0057, 0.0047, 0.0037, 0.0027, 0.0019, 0.0012, 0.0007, 0.0004,
		0.0003, 0.0006, 0.0009, 0.0014, 0.0021, 0.0029, 0.0037, 0.0045, 0.0050, 0.0054, 0.0054, 0.0050, 0.0045, 0.0037, 0.0029, 0.0021, 0.0014, 0.0009, 0.0006, 0.0003,
		0.0002, 0.0004, 0.0007, 0.0011, 0.0015, 0.0021, 0.0027, 0.0033, 0.0037, 0.0039, 0.0039, 0.0037, 0.0033, 0.0027, 0.0021, 0.0015, 0.0011, 0.0007, 0.0004, 0.0002,
		0.0002, 0.0003, 0.0005, 0.0007, 0.0011, 0.0014, 0.0019, 0.0022, 0.0025, 0.0027, 0.0027, 0.0025, 0.0022, 0.0019, 0.0014, 0.0011, 0.0007, 0.0005, 0.0003, 0.0002,
		0.0001, 0.0002, 0.0003, 0.0005, 0.0007, 0.0009, 0.0012, 0.0014, 0.0016, 0.0017, 0.0017, 0.0016, 0.0014, 0.0012, 0.0009, 0.0007, 0.0005, 0.0003, 0.0002, 0.0001,
		0.0001, 0.0001, 0.0002, 0.0003, 0.0004, 0.0006, 0.0007, 0.0009, 0.0010, 0.0011, 0.0011, 0.0010, 0.0009, 0.0007, 0.0006, 0.0004, 0.0003, 0.0002, 0.0001, 0.0001,
		0.0000, 0.0001, 0.0001, 0.0002, 0.0002, 0.0003, 0.0004, 0.0005, 0.0006, 0.0006, 0.0006, 0.0006, 0.0005, 0.0004, 0.0003, 0.0002, 0.0002, 0.0001, 0.0001, 0.0000
	};

	int height = origin.height;
	int width = origin.width;
	int hHeight = 20;
	int hWidth = 20;
	int h_h_1 = (hHeight - 1) / 2;
	int h_h_2 = hHeight - h_h_1;
	h_h_1 = -h_h_1;
	int h_w_1 = (hWidth - 1) / 2;
	int h_w_2 = hWidth - h_w_1;
	h_w_1 = -h_w_1;

	double sum_data = 0.0, src_data = 0.0;

	MAR extendOri(height + 20, width + 20, 2);
	mirror_extension(extendOri, origin, 10, 10);
	//H的范围从-9到11，因此需要将origin矩阵扩展进行计算防止越界，此处向四个方向各扩展10行/列

	int i, j;			//result及origin矩阵的行和列
	int h_h, h_w;		//H矩阵的行和列
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			sum_data = 0.0;
			for (h_h = h_h_1; h_h < h_h_2; h_h++)
			{
				for (h_w = h_w_1; h_w < h_w_2; h_w++)
				{
					src_data = extendOri.data[(i + h_h + 10) * extendOri.width + j + 10 + h_w];
					sum_data += src_data * H[(h_h - h_h_1)*hWidth + (h_w - h_w_1)];
				}
			}
			result.data[i*width + j] = sum_data;
		}
	}
}

void ContoursTools::im2bw(MAR &result, MAR &origin, int bw)
{
	int height = origin.height;
	int width = origin.width;
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (origin.data[i*width + j] <= bw)
				result.data[i*width + j] = 0;
			else
				result.data[i*width + j] = 1;
		}
	}
}

void ContoursTools::FindContours(MAR & gray, ListTable *listPointer, int lineNumber)
//根据滤波后的灰度图像gray，找出lineNumber个高度的等高线，存储在lineNumber个链表中
{
	int i, j;
	int height = gray.height;
	int width = gray.width;

	//计算等高线间的差值
	int max = gray.data[0], min = gray.data[0];
	int valueR;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			valueR = gray.data[i*width + j];
			if (max < valueR)
				max = valueR;
			if (min > valueR)
				min = valueR;
		}
	}

	int *Tarray = new int[lineNumber + 2];
	double d = (double)((max - min)) / (lineNumber + 1);
	for (i = 0; i < lineNumber + 2; i++)
	{
		Tarray[i] = (int)(min + i*d + 0.5);
	}

	//找出等高线
	int bwLine = 0;
	MAR bwImage(height, width, 2);		//保存gray图像二值变化后的黑白图像
	for (i = 0; i < lineNumber; i++)
	{
		bwLine = Tarray[i + 1];
		im2bw(bwImage, gray, bwLine);
		MarchingSquare(bwImage, listPointer[i]);
	}
	delete[]Tarray;
	Tarray = NULL;
}

void ContoursTools::MarchingSquare(MAR & origin, ListTable &list)
//origin为二维黑白图像，高于等高线区域为1，低于或等于等高线区域为0，list可能包含多个链表，不同链表之间用一个x = -1的结点隔开
{
	int i, j;
	int height = origin.height;
	int width = origin.width;

	MAR memory(height + 2, width + 2, 2);
	//记录矩阵中每一点是否已被加入链表，初始为0，为1时则代表已被加入
	for (i = 0; i < height + 2; i++)
	{
		for (j = 0; j < width + 2; j++)
		{
			memory.data[i*(width + 2) + j] = 0;
		}
	}

	//拓展origin，四个方向各+1，用0填充
	MAR originEx(height + 2, width + 2, 2);
	for (i = 0; i < height; i++)			//中间部分
	{
		for (j = 0; j < width; j++)
		{
			originEx.data[(i + 1)*(width + 2) + j + 1] = origin.data[i*width + j];
		}
	}
	for (i = 0; i < width + 2; i++)			//上边缘
		originEx.data[i] = 0;
	for (i = 0; i < height + 2; i++)		//左边缘
		originEx.data[i*(width + 2)] = 0;
	for (i = 0; i < width + 2; i++)			//下边缘
		originEx.data[(height + 1)*(width + 2) + i] = 0;
	for (i = 0; i < height + 2; i++)		//右边缘
		originEx.data[i*(width + 2) + width + 1] = 0;

	//从左上角开始找一个起始点
	int x = 0, y = 0;
	FindStart(originEx, memory, x, y);
	int a = 0, b = 0, c = 0, d = 0;			//四元组
	int value4 = a * 8 + b * 4 + c * 2 + d * 1;
	/*
	+---+---+
	| a | b |
	+---+---+
	| d | c |
	+---+---+
	*/
	int exHeight = height + 2;
	int exWidth = width + 2;
	ListNode *nowList = NULL;
	LinkedNode *nowNode = NULL;
	int nowX, nowY;				//搜寻边界过程中的坐标
	int lastDirection;
	while (x != -1)
	{
		//创建链表
		nowList = new ListNode;
		nowList->thisList = new MyLinkedList;
		nowList->next = NULL;
		list.addList(nowList);

		lastDirection = DOWN;	//起点右下方为所需圈出的部分，此时应下移
		nowX = x + 1;
		nowY = y;
		nowList->thisList->addNode(x + 1 - 1, y + 1 - 1);		//+1指(nowX,nowY)右下方的点，-1指将其变换为origin的坐标
		memory.data[(x + 1)*exWidth + y + 1] = 1;
		//圈出图案
		while (nowX != x || nowY != y)
		{
			a = originEx.data[nowX*exWidth + nowY];
			b = originEx.data[nowX*exWidth + nowY + 1];
			c = originEx.data[(nowX + 1)*exWidth + nowY + 1];
			d = originEx.data[(nowX + 1)*exWidth + nowY];
			value4 = a * 8 + b * 4 + c * 2 + d * 1;
			switch (value4)
			{
			case 1:		//左下
				if (memory.data[(nowX + 1)*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX, nowY - 1);
					memory.data[(nowX + 1)*exWidth + nowY] = 1;
				}
				lastDirection = LEFT;
				nowY--;
				break;
			case 2:		//右下
				if (memory.data[(nowX + 1)*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX, nowY);
					memory.data[(nowX + 1)*exWidth + nowY + 1] = 1;
				}
				lastDirection = DOWN;
				nowX++;
				break;
			case 4:		//右上
				if (memory.data[nowX*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY);
					memory.data[nowX*exWidth + nowY + 1] = 1;
				}
				lastDirection = RIGHT;
				nowY++;
				break;
			case 8:		//左上
				if (memory.data[nowX*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY - 1);
					memory.data[nowX*exWidth + nowY] = 1;
				}
				lastDirection = UP;
				nowX--;
				break;
			case 3:		//右下+左下
				if (memory.data[(nowX + 1)*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX, nowY);
					memory.data[(nowX + 1)*exWidth + nowY + 1] = 1;
				}
				if (memory.data[(nowX + 1)*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX, nowY - 1);
					memory.data[(nowX + 1)*exWidth + nowY] = 1;
				}
				lastDirection = LEFT;
				nowY--;
				break;
			case 6:		//右上+右下
				if (memory.data[nowX*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY);
					memory.data[nowX*exWidth + nowY + 1] = 1;
				}
				if (memory.data[(nowX + 1)*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX, nowY);
					memory.data[(nowX + 1)*exWidth + nowY + 1] = 1;
				}
				lastDirection = DOWN;
				nowX++;
				break;
			case 12:		//左上+右上
				if (memory.data[nowX*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY - 1);
					memory.data[nowX*exWidth + nowY] = 1;
				}
				if (memory.data[nowX*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY);
					memory.data[nowX*exWidth + nowY + 1] = 1;
				}
				lastDirection = RIGHT;
				nowY++;
				break;
			case 9:			//左下+左上
				if (memory.data[(nowX + 1)*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX, nowY - 1);
					memory.data[(nowX + 1)*exWidth + nowY] = 1;
				}
				if (memory.data[nowX*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY - 1);
					memory.data[nowX*exWidth + nowY] = 1;
				}
				lastDirection = UP;
				nowX--;
				break;
			case 7:			//右上+右下+左下
				if (memory.data[nowX*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY);
					memory.data[nowX*exWidth + nowY + 1] = 1;
				}
				if (memory.data[(nowX + 1)*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX, nowY);
					memory.data[(nowX + 1)*exWidth + nowY + 1] = 1;
				}
				if (memory.data[(nowX + 1)*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX, nowY - 1);
					memory.data[(nowX + 1)*exWidth + nowY] = 1;
				}
				lastDirection = LEFT;
				nowY--;
				break;
			case 14:			//左上+右上+右下
				if (memory.data[nowX*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY - 1);
					memory.data[nowX*exWidth + nowY] = 1;
				}
				if (memory.data[nowX*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY);
					memory.data[nowX*exWidth + nowY + 1] = 1;
				}
				if (memory.data[(nowX + 1)*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX, nowY);
					memory.data[(nowX + 1)*exWidth + nowY + 1] = 1;
				}
				lastDirection = DOWN;
				nowX++;
				break;
			case 13:			//左下+左上+右上
				if (memory.data[(nowX + 1)*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX, nowY - 1);
					memory.data[(nowX + 1)*exWidth + nowY] = 1;
				}
				if (memory.data[nowX*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY - 1);
					memory.data[nowX*exWidth + nowY] = 1;
				}
				if (memory.data[nowX*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY);
					memory.data[nowX*exWidth + nowY + 1] = 1;
				}
				lastDirection = RIGHT;
				nowY++;
				break;
			case 11:			//右下+左下+左上
				if (memory.data[(nowX + 1)*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX, nowY);
					memory.data[(nowX + 1)*exWidth + nowY + 1] = 1;
				}
				if (memory.data[(nowX + 1)*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX, nowY - 1);
					memory.data[(nowX + 1)*exWidth + nowY] = 1;
				}
				if (memory.data[nowX*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY - 1);
					memory.data[nowX*exWidth + nowY] = 1;
				}
				lastDirection = UP;
				nowX--;
				break;
			case 5:
				if (lastDirection == UP) {		//左下
					if (memory.data[(nowX + 1)*exWidth + nowY] == 0) {
						nowList->thisList->addNode(nowX, nowY - 1);
						memory.data[(nowX + 1)*exWidth + nowY] = 1;
					}
					lastDirection = LEFT;
					nowY--;
					break;
				}
				if (lastDirection == DOWN) {	//右上
					if (memory.data[nowX*exWidth + nowY + 1] == 0) {
						nowList->thisList->addNode(nowX - 1, nowY);
						memory.data[nowX*exWidth + nowY + 1] = 1;
					}
					lastDirection = RIGHT;
					nowY++;
					break;
				}
			case 10:
				if (lastDirection == LEFT) {	//右下
					if (memory.data[(nowX + 1)*exWidth + nowY + 1] == 0) {
						nowList->thisList->addNode(nowX, nowY);
						memory.data[(nowX + 1)*exWidth + nowY + 1] = 1;
					}
					lastDirection = DOWN;
					nowX++;
					break;
				}
				if (lastDirection == RIGHT) {	//左上
					if (memory.data[nowX*exWidth + nowY] == 0) {
						nowList->thisList->addNode(nowX - 1, nowY - 1);
						memory.data[nowX*exWidth + nowY] = 1;
					}
					lastDirection = UP;
					nowX--;
					break;
				}
			}
		}

		nowList->thisList->last->next = nowList->thisList->first;	//成为循环链表
																	//找下一个起始点
		FindStart(originEx, memory, x, y);
	}
	edgeProcess(list, height, width);
}

void ContoursTools::FindStart(MAR & originEx, MAR & memory, int & x, int & y)
//MarchingSquare工具函数。在黑白图像originEx中，为寻找等高线找一个起始点。找不到时令x = -1
//找到的起始点为返回的(x,y)右下方的点
{
	int i, j;
	int exHeight = originEx.height;
	int exWidth = originEx.width;
	//此处高和宽均取矩阵拓展之后的值

	for (i = x; i < exHeight - 1; i++)
	{
		for (j = y; j < exWidth - 1; j++)
		{
			if (originEx.data[(i + 1)*exWidth + j + 1] == 1)
			{
				if (originEx.data[(i + 1)*exWidth + j] == 0
					&& originEx.data[i*exWidth + j + 1] == 0)
				{
					if (memory.data[(i + 1)*exWidth + j + 1] == 0)		//四元组中右下方为1，且未被处理，左下和右上为0
					{
						x = i;
						y = j;
						return;
					}
				}
			}
		}
	}
	x = -1;
}

short ContoursTools::cal(MAR & origin, int x, int y)
//MarchingSquare工具函数，返回以(x,y)为左上格的四个相邻方格的累加值
//不会进行边界处理
{
	return 8 * origin.data[x*origin.width + y]
		+ 4 * origin.data[x*origin.width + y + 1]
		+ 2 * origin.data[(x + 1)*origin.width + y + 1]
		+ origin.data[(x + 1)*origin.width + y];
}

void ContoursTools::edgeProcess(ListTable &list, int height, int width)
//边界处理，部分链表包含了边界，需要去除边界部分，可能还需要将其分解为多个链表
{
	//步骤为，从循环链表中删除边界点，然后为该链表找一个合适的first
	//链表中包含X段边界时，应将链表分割为X个
	int listNumber = list.number;
	int i, j;
	ListNode *nowList = list.first;
	LinkedNode *nowNode = nowList->thisList->first;
	int listLength;

	for (i = 0; i < listNumber; i++)
	{
		//删除边界部分
		//将first移动到一个合适的位置
		listLength = nowList->thisList->length;
		for (i = 0; i < listLength; i++)
		{
			if (edgeJudge(nowList->thisList->first->x, nowList->thisList->first->y, height, width)
				&& edgeJudge(nowList->thisList->first->next->x, nowList->thisList->first->next->y, height, width))
			{//当first点和下一点均在边界上时
				nowList->thisList->first = nowList->thisList->first->next;
				nowList->thisList->last = nowList->thisList->last->next;
			}
		}

		//开始删除边界
		nowNode = nowList->thisList->first;
		for (j = 0; j < listLength; j++)
		{
			if (edgeJudge(nowNode->x, nowNode->y, height, width)
				&& edgeJudge(nowNode->next->x, nowNode->next->y, height, width)
				&& edgeJudge(nowNode->next->next->x, nowNode->next->next->y, height, width))
				nowList->thisList->deleteNextNode(nowNode);
			else
				nowNode = nowNode->next;
		}

		//分解部分
		//判断需要分解为几个链表
		int listNumber = cutJudge(nowList->thisList);

		//分解
		if (listNumber > 1)
		{
			ListNode *newList;								//新链表
			ListNode *wholeList = nowList;					//正在分解的链表
			LinkedNode *breakNode;
			int counter;				//计算到达断点时共经过了多少点
			for (j = 0; j < listNumber - 1; j++)
			{
				newList = new ListNode;
				newList->thisList = new MyLinkedList;
				newList->next = NULL;
				list.addList(newList);

				breakNode = wholeList->thisList->first;
				counter = 1;
				while (1)						//搜寻所需截断的点
				{
					if (nearJudge(breakNode->x, breakNode->y, breakNode->next->x, breakNode->next->y) == false)
						break;
					breakNode = breakNode->next;
					counter++;
				}
				newList->thisList->first = breakNode->next;			//新链表的头为断点的下一个点
				newList->thisList->last = wholeList->thisList->last;	//新链表的末项设为原链表的末项
				newList->thisList->length = wholeList->thisList->length - counter;		//设置新链表项数
				breakNode->next = wholeList->thisList->first;		//原链表的末项指向原链表的头
				wholeList->thisList->last = breakNode;				//将原链表的末项设为断点
				wholeList->thisList->length = counter;				//修改原链表的项数

																	//下一新链表
				wholeList = newList;
			}
		}

		//下一链表
		nowList = nowList->next;
	}
}

bool ContoursTools::edgeJudge(int x, int y, int height, int width)
//判断(x,y)是否在高为heighe，宽为width的矩阵边界上
{
	if (x == 0) return true;
	if (y == 0) return true;
	if (x == height - 1) return true;
	if (y == width - 1) return true;
	return false;
}

int ContoursTools::cutJudge(MyLinkedList *nowList)
//计算需要将nowList分解为几个链表，返回1时则无需分解

{
	int listNumber = 0;
	int i;
	LinkedNode *nowNode = nowList->first;
	for (i = 0; i < nowList->length; i++)
	{
		if (nearJudge(nowNode->x, nowNode->y, nowNode->next->x, nowNode->next->y) == false)
			listNumber++;
		nowNode = nowNode->next;
	}
	return (listNumber > 1) ? listNumber : 1;
}

bool ContoursTools::nearJudge(int x1, int y1, int x2, int y2)
//判断(x1,y1),(x2,y2)是否相邻
{
	if (x1 == x2 + 1 && y1 == y2) return true;
	if (x1 == x2 - 1 && y1 == y2) return true;
	if (y1 == y2 + 1 && x1 == x2) return true;
	if (y1 == y2 - 1 && x1 == x2) return true;
	return false;
}
