#include <iostream>
#include <fstream>
using namespace std;

#include "Bitmap.h"

Bitmap::Bitmap()
{
	//�ļ�ͷ
	fileHeader.bfType = 0x4D42;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfSize = sizeof(MYBITMAPFILEHEADER) + sizeof(MYBITMAPINFOHEADER) + 3;
	fileHeader.bfOffBits = sizeof(MYBITMAPFILEHEADER) + sizeof(MYBITMAPINFOHEADER);

	//bmp�ļ���Ϣ
	infoHeader.biSize = sizeof(MYBITMAPINFOHEADER);
	infoHeader.biHeight = 1;
	infoHeader.biWidth = 1;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 24;
	infoHeader.biCompression = 0;
	infoHeader.biSizeImage = 0;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;

	//��ɫ��(Ĭ�ϲ�ʹ��)
	paletteentry = 0;

	//ͼ������(Ĭ��Ϊ1x1��һ��(0,0,0)�ĵ�)
	buffer = new BYTE[3];
	*(buffer + 0) = 0;			//B
	*(buffer + 1) = 0;			//G
	*(buffer + 2) = 0;			//R
}

Bitmap::Bitmap(Bitmap &copy)
{
	//�ļ�ͷ
	fileHeader.bfType = 0x4D42;
	fileHeader.bfReserved1 = copy.fileHeader.bfReserved1;
	fileHeader.bfReserved2 = copy.fileHeader.bfReserved2;
	fileHeader.bfSize = copy.fileHeader.bfSize;
	fileHeader.bfOffBits = copy.fileHeader.bfOffBits;

	//bmp�ļ���Ϣ
	infoHeader.biSize = copy.infoHeader.biSize;
	infoHeader.biHeight = copy.infoHeader.biHeight;
	infoHeader.biWidth = copy.infoHeader.biWidth;
	infoHeader.biPlanes = copy.infoHeader.biPlanes;
	infoHeader.biBitCount = copy.infoHeader.biBitCount;
	infoHeader.biCompression = copy.infoHeader.biCompression;
	infoHeader.biSizeImage = copy.infoHeader.biSizeImage;
	infoHeader.biXPelsPerMeter = copy.infoHeader.biXPelsPerMeter;
	infoHeader.biYPelsPerMeter = copy.infoHeader.biYPelsPerMeter;
	infoHeader.biClrUsed = copy.infoHeader.biClrUsed;
	infoHeader.biClrImportant = copy.infoHeader.biClrImportant;

	//��ɫ��
	int paletteentrySize = copy.fileHeader.bfOffBits - sizeof(MYBITMAPFILEHEADER) - sizeof(MYBITMAPINFOHEADER);
	paletteentry = new MYPALETTEENTRY[paletteentrySize / 4];		//һ����ɫ�����ռ��4���ֽ�
	for (int i = 0; i < paletteentrySize / 4; i++)
	{
		paletteentry[i] = copy.paletteentry[i];
	}

	//ͼ������(Ĭ��Ϊ1x1��һ��(0,0,0)�ĵ�)
	if (buffer) delete[]buffer;
	int bufferSize = copy.fileHeader.bfSize - copy.fileHeader.bfOffBits;
	buffer = new BYTE[bufferSize];
	for (int j = 0; j < bufferSize; j++)
	{
		buffer[j] = copy.buffer[j];
	}
}

Bitmap::~Bitmap()
{
	if (paletteentry)
	{
		delete[]paletteentry;
		paletteentry = NULL;
	}

	if (buffer) {
		delete[]buffer;
		buffer = NULL;
	}
}

bool Bitmap::readFile(char *fileName)
{
	FILE *input = fopen(fileName, "rb");
	if (!input)
	{
		return false;			//����false��δ�ɹ����ļ�
	}

	fread(&fileHeader, 1, sizeof(MYBITMAPFILEHEADER), input);			//�ļ�ͷ
	fread(&infoHeader, 1, sizeof(MYBITMAPINFOHEADER), input);			//�ļ���Ϣ
	if (fileHeader.bfOffBits != sizeof(MYBITMAPFILEHEADER) + sizeof(MYBITMAPINFOHEADER))		//���ܰ����ĵ�ɫ����Ϣ
	{
		int palSize = fileHeader.bfOffBits - sizeof(MYBITMAPFILEHEADER) - sizeof(MYBITMAPINFOHEADER);
		paletteentry = new MYPALETTEENTRY[palSize];
		fread(paletteentry, 1, palSize, input);
	}

	//��ͼ������
	int height = infoHeader.biHeight;			//ͼƬ�߶�
	int width = infoHeader.biWidth;				//ͼƬ����
	int size = height * width * 3;				//ͼ�������ֽ���

	if (buffer) delete[]buffer;
	buffer = new BYTE[size];
	fread(buffer, 1, size, input);
	fclose(input);
	return true;
}
