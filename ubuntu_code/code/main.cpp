#include <iostream>
#include <fstream>
using namespace std;

#pragma pack(1)
#include"ContoursTools.h"

int main()
{
	int i, j;
	int lineNumber = 10;		//等高线条数
	ContoursTools tool;

	Bitmap pic;
	pic.readFile("input.bmp");
	int height = pic.infoHeader.biHeight;
	int width = pic.infoHeader.biWidth;

	//图像数据保存为矩阵,一维R,二维G,三维B (与bmp文件内部顺序相反)
	MAR originData(height, width, 3);
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			originData.data[i*width * 3 + j * 3 + 0] = pic.buffer[(height - i - 1)*width * 3 + j * 3 + 2];
			originData.data[i*width * 3 + j * 3 + 1] = pic.buffer[(height - i - 1)*width * 3 + j * 3 + 1];
			originData.data[i*width * 3 + j * 3 + 2] = pic.buffer[(height - i - 1)*width * 3 + j * 3 + 0];
		}
	}

	/*
	//提取R分量
	MAR originRedData(height, width, 2);
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			originRedData.data[i*width + j] = originData.data[i*width * 3 + j * 3 + 0];
		}
	}*/

	//根据R分量进行变换
	//MAR rgb5(height, width, 3);
	//bayer2rgb5(rgb5, originRedData);

	//转换为灰度图像
	MAR gray(height, width, 2);
	//tool.rgb2gray(gray, rgb5);
	tool.rgb2gray(gray, originData);

	//对灰度图像滤波
	MAR filterIm(height, width, 2);
	tool.imfilter_symmetric(filterIm, gray);

	//找出等高线并存储
	ListTable *contoursList = new ListTable[lineNumber];
	for (i = 0; i < lineNumber; i++)
	{
		contoursList[i].first = NULL;
		contoursList[i].number = 0;
	}

	tool.FindContours(filterIm, contoursList, lineNumber);
	//tool.FindContours(gray, contoursList, lineNumber);

	//根据链表中的数据，直接在图上绘制等高线
	int R = 255, G = 255, B = 255;
	int dG = -5;
	ListNode *nowList;
	LinkedNode *nowNode;

	for (i = 0; i < lineNumber; i++)
	{
		nowList = contoursList[i].first;
		//cout << i << "\t" << contoursList[i].number << endl;
		while (nowList != NULL)
		{
			nowNode = nowList->thisList->first;
			for (j = 0; j < nowList->thisList->length; j++)
			{
				originData.data[nowNode->x * width * 3 + nowNode->y * 3 + 0] = R;
				originData.data[nowNode->x * width * 3 + nowNode->y * 3 + 1] = G;
				originData.data[nowNode->x * width * 3 + nowNode->y * 3 + 2] = B;
				nowNode = nowNode->next;
				G += dG;
				if (G == 255 || G == 0)
					dG = -dG;
			}
			nowList = nowList->next;
		}
	}

	//写入结果(height方向与bmp文件记录顺序相反)
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			pic.buffer[(height - i - 1)*width * 3 + j * 3 + 2] = originData.data[i*width * 3 + j * 3 + 0];
			pic.buffer[(height - i - 1)*width * 3 + j * 3 + 1] = originData.data[i*width * 3 + j * 3 + 1];
			pic.buffer[(height - i - 1)*width * 3 + j * 3 + 0] = originData.data[i*width * 3 + j * 3 + 2];
		}
	}

	//保存绘制后的图像
	FILE *output = fopen("output.bmp", "wb");
	if (!output)
	{
		cout << "Cannot open output file!\n";
	}

	fwrite(&pic.fileHeader, 1, sizeof(MYBITMAPFILEHEADER), output);
	fwrite(&pic.infoHeader, 1, sizeof(MYBITMAPINFOHEADER), output);
	fwrite(pic.buffer, 1, height*width * 3, output);
	fclose(output);

	delete[]contoursList;

	return 0;
}