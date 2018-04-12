#include <iostream>
#include <fstream>
using namespace std;

#pragma pack(1)
#include"ContoursTools.h"

int main()
{
	int i, j;
	int lineNumber = 10;		//�ȸ�������
	ContoursTools tool;

	Bitmap pic;
	pic.readFile("input.bmp");
	int height = pic.infoHeader.biHeight;
	int width = pic.infoHeader.biWidth;

	//ͼ�����ݱ���Ϊ����,һάR,��άG,��άB (��bmp�ļ��ڲ�˳���෴)
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
	//��ȡR����
	MAR originRedData(height, width, 2);
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			originRedData.data[i*width + j] = originData.data[i*width * 3 + j * 3 + 0];
		}
	}*/

	//����R�������б任
	//MAR rgb5(height, width, 3);
	//bayer2rgb5(rgb5, originRedData);

	//ת��Ϊ�Ҷ�ͼ��
	MAR gray(height, width, 2);
	//tool.rgb2gray(gray, rgb5);
	tool.rgb2gray(gray, originData);

	//�ԻҶ�ͼ���˲�
	MAR filterIm(height, width, 2);
	tool.imfilter_symmetric(filterIm, gray);

	//�ҳ��ȸ��߲��洢
	ListTable *contoursList = new ListTable[lineNumber];
	for (i = 0; i < lineNumber; i++)
	{
		contoursList[i].first = NULL;
		contoursList[i].number = 0;
	}

	tool.FindContours(filterIm, contoursList, lineNumber);
	//tool.FindContours(gray, contoursList, lineNumber);

	//���������е����ݣ�ֱ����ͼ�ϻ��Ƶȸ���
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

	//д����(height������bmp�ļ���¼˳���෴)
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			pic.buffer[(height - i - 1)*width * 3 + j * 3 + 2] = originData.data[i*width * 3 + j * 3 + 0];
			pic.buffer[(height - i - 1)*width * 3 + j * 3 + 1] = originData.data[i*width * 3 + j * 3 + 1];
			pic.buffer[(height - i - 1)*width * 3 + j * 3 + 0] = originData.data[i*width * 3 + j * 3 + 2];
		}
	}

	//������ƺ��ͼ��
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