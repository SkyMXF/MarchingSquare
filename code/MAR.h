#pragma once
#include <iostream>
#include "Bitmap.h"

//�����ľ�����
class MAR {
public:
	int height;			//��������
	int width;			//��������
	int dim;			//����ά��
	int size;			//�ռ�
	BYTE* data;			//����

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