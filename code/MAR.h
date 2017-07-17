#pragma once
#include <iostream>
#include "Bitmap.h"

//基本的矩阵类
class MAR {
public:
	int height;			//矩阵行数
	int width;			//矩阵列数
	int dim;			//矩阵维度
	int size;			//空间
	BYTE* data;			//数据

	MAR()
	{
		data = NULL;
	}

	MAR(int h, int w, int d = 2)
	{
		height = h;
		width = w;
		dim = d;

		if (dim = 2) size = height*width;
		if (dim = 3) size = height*width * 3;
		data = new BYTE[size];
	}

	~MAR()
	{
		if (data)
			delete[]data;
	}
};