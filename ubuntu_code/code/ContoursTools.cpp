#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

#include "ContoursTools.h"

void ContoursTools::bayer2rgb5(MAR & result, MAR & origin)
//resultΪ��ά����originΪ��ά����
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
//resultΪorigin�����淽ʽ��չ
{
	int i, j;
	int r, c;

	int height = origin.height;
	int width = origin.width;

	//�м䲿��,r,cΪresult���к���
	for (i = 0; i < height; i++)
	{
		r = i + vsize;
		for (j = 0; j < width; j++)
		{
			c = j + hsize;
			result.data[r*(width + 2 * hsize) + c] = origin.data[i*width + j];
		}
	}

	//�ϱ߽���չ,r,cΪresult�����踴��Ԫ�ص��к���
	for (i = vsize - 1; i >= 0; i--)
	{
		r = vsize + vsize - i;
		for (j = hsize; j < width + hsize; j++)
		{
			c = j;
			result.data[i*(width + 2 * hsize) + j] = result.data[r*(width + 2 * hsize) + c];
		}
	}

	//�ұ߽���չ,r,cΪresult�����踴��Ԫ�ص��к���
	for (i = 0; i < vsize + height; i++)
	{
		r = i;
		for (j = hsize + width; j < 2 * hsize + width; j++)
		{
			c = hsize + width - 1 - (j - (hsize + width - 1));
			result.data[i*(width + 2 * hsize) + j] = result.data[r*(width + 2 * hsize) + c];
		}
	}

	//�±߽���չ,r,cΪresult�����踴��Ԫ�ص��к���
	for (i = vsize + height; i < 2 * vsize + height; i++)
	{
		r = vsize + height - 1 - (i - (vsize + height - 1));
		for (j = hsize; j < 2 * hsize + width; j++)
		{
			c = j;
			result.data[i*(width + 2 * hsize) + j] = result.data[r*(width + 2 * hsize) + c];
		}
	}

	//��߽���չ,r,cΪresult�����踴��Ԫ�ص��к���
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
//��άorigin������RGBֵת��Ϊ�Ҷ�ͼ��result(��ά)
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
	double H[400] =	//�˲����ݣ�Matlab����fspecial('gaussian',[20,20],4)����
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
	//H�ķ�Χ��-9��11�������Ҫ��origin������չ���м����ֹԽ�磬�˴����ĸ��������չ10��/��

	int i, j;			//result��origin������к���
	int h_h, h_w;		//H������к���
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
//�����˲���ĻҶ�ͼ��gray���ҳ�lineNumber���߶ȵĵȸ��ߣ��洢��lineNumber��������
{
	int i, j;
	int height = gray.height;
	int width = gray.width;

	//����ȸ��߼�Ĳ�ֵ
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

	//�ҳ��ȸ���
	int bwLine = 0;
	MAR bwImage(height, width, 2);		//����grayͼ���ֵ�仯��ĺڰ�ͼ��
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
//originΪ��ά�ڰ�ͼ�񣬸��ڵȸ�������Ϊ1�����ڻ���ڵȸ�������Ϊ0��list���ܰ������������ͬ����֮����һ��x = -1�Ľ�����
{
	int i, j;
	int height = origin.height;
	int width = origin.width;

	MAR memory(height + 2, width + 2, 2);
	//��¼������ÿһ���Ƿ��ѱ�����������ʼΪ0��Ϊ1ʱ������ѱ�����
	for (i = 0; i < height + 2; i++)
	{
		for (j = 0; j < width + 2; j++)
		{
			memory.data[i*(width + 2) + j] = 0;
		}
	}

	//��չorigin���ĸ������+1����0���
	MAR originEx(height + 2, width + 2, 2);
	for (i = 0; i < height; i++)			//�м䲿��
	{
		for (j = 0; j < width; j++)
		{
			originEx.data[(i + 1)*(width + 2) + j + 1] = origin.data[i*width + j];
		}
	}
	for (i = 0; i < width + 2; i++)			//�ϱ�Ե
		originEx.data[i] = 0;
	for (i = 0; i < height + 2; i++)		//���Ե
		originEx.data[i*(width + 2)] = 0;
	for (i = 0; i < width + 2; i++)			//�±�Ե
		originEx.data[(height + 1)*(width + 2) + i] = 0;
	for (i = 0; i < height + 2; i++)		//�ұ�Ե
		originEx.data[i*(width + 2) + width + 1] = 0;

	//�����Ͻǿ�ʼ��һ����ʼ��
	int x = 0, y = 0;
	FindStart(originEx, memory, x, y);
	int a = 0, b = 0, c = 0, d = 0;			//��Ԫ��
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
	int nowX, nowY;				//��Ѱ�߽�����е�����
	int lastDirection;
	while (x != -1)
	{
		//��������
		nowList = new ListNode;
		nowList->thisList = new MyLinkedList;
		nowList->next = NULL;
		list.addList(nowList);

		lastDirection = DOWN;	//������·�Ϊ����Ȧ���Ĳ��֣���ʱӦ����
		nowX = x + 1;
		nowY = y;
		nowList->thisList->addNode(x + 1 - 1, y + 1 - 1);		//+1ָ(nowX,nowY)���·��ĵ㣬-1ָ����任Ϊorigin������
		memory.data[(x + 1)*exWidth + y + 1] = 1;
		//Ȧ��ͼ��
		while (nowX != x || nowY != y)
		{
			a = originEx.data[nowX*exWidth + nowY];
			b = originEx.data[nowX*exWidth + nowY + 1];
			c = originEx.data[(nowX + 1)*exWidth + nowY + 1];
			d = originEx.data[(nowX + 1)*exWidth + nowY];
			value4 = a * 8 + b * 4 + c * 2 + d * 1;
			switch (value4)
			{
			case 1:		//����
				if (memory.data[(nowX + 1)*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX, nowY - 1);
					memory.data[(nowX + 1)*exWidth + nowY] = 1;
				}
				lastDirection = LEFT;
				nowY--;
				break;
			case 2:		//����
				if (memory.data[(nowX + 1)*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX, nowY);
					memory.data[(nowX + 1)*exWidth + nowY + 1] = 1;
				}
				lastDirection = DOWN;
				nowX++;
				break;
			case 4:		//����
				if (memory.data[nowX*exWidth + nowY + 1] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY);
					memory.data[nowX*exWidth + nowY + 1] = 1;
				}
				lastDirection = RIGHT;
				nowY++;
				break;
			case 8:		//����
				if (memory.data[nowX*exWidth + nowY] == 0) {
					nowList->thisList->addNode(nowX - 1, nowY - 1);
					memory.data[nowX*exWidth + nowY] = 1;
				}
				lastDirection = UP;
				nowX--;
				break;
			case 3:		//����+����
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
			case 6:		//����+����
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
			case 12:		//����+����
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
			case 9:			//����+����
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
			case 7:			//����+����+����
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
			case 14:			//����+����+����
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
			case 13:			//����+����+����
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
			case 11:			//����+����+����
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
				if (lastDirection == UP) {		//����
					if (memory.data[(nowX + 1)*exWidth + nowY] == 0) {
						nowList->thisList->addNode(nowX, nowY - 1);
						memory.data[(nowX + 1)*exWidth + nowY] = 1;
					}
					lastDirection = LEFT;
					nowY--;
					break;
				}
				if (lastDirection == DOWN) {	//����
					if (memory.data[nowX*exWidth + nowY + 1] == 0) {
						nowList->thisList->addNode(nowX - 1, nowY);
						memory.data[nowX*exWidth + nowY + 1] = 1;
					}
					lastDirection = RIGHT;
					nowY++;
					break;
				}
			case 10:
				if (lastDirection == LEFT) {	//����
					if (memory.data[(nowX + 1)*exWidth + nowY + 1] == 0) {
						nowList->thisList->addNode(nowX, nowY);
						memory.data[(nowX + 1)*exWidth + nowY + 1] = 1;
					}
					lastDirection = DOWN;
					nowX++;
					break;
				}
				if (lastDirection == RIGHT) {	//����
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

		nowList->thisList->last->next = nowList->thisList->first;	//��Ϊѭ������
																	//����һ����ʼ��
		FindStart(originEx, memory, x, y);
	}
	edgeProcess(list, height, width);
}

void ContoursTools::FindStart(MAR & originEx, MAR & memory, int & x, int & y)
//MarchingSquare���ߺ������ںڰ�ͼ��originEx�У�ΪѰ�ҵȸ�����һ����ʼ�㡣�Ҳ���ʱ��x = -1
//�ҵ�����ʼ��Ϊ���ص�(x,y)���·��ĵ�
{
	int i, j;
	int exHeight = originEx.height;
	int exWidth = originEx.width;
	//�˴��ߺͿ��ȡ������չ֮���ֵ

	for (i = x; i < exHeight - 1; i++)
	{
		for (j = y; j < exWidth - 1; j++)
		{
			if (originEx.data[(i + 1)*exWidth + j + 1] == 1)
			{
				if (originEx.data[(i + 1)*exWidth + j] == 0
					&& originEx.data[i*exWidth + j + 1] == 0)
				{
					if (memory.data[(i + 1)*exWidth + j + 1] == 0)		//��Ԫ�������·�Ϊ1����δ���������º�����Ϊ0
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
//MarchingSquare���ߺ�����������(x,y)Ϊ���ϸ���ĸ����ڷ�����ۼ�ֵ
//������б߽紦��
{
	return 8 * origin.data[x*origin.width + y]
		+ 4 * origin.data[x*origin.width + y + 1]
		+ 2 * origin.data[(x + 1)*origin.width + y + 1]
		+ origin.data[(x + 1)*origin.width + y];
}

void ContoursTools::edgeProcess(ListTable &list, int height, int width)
//�߽紦��������������˱߽磬��Ҫȥ���߽粿�֣����ܻ���Ҫ����ֽ�Ϊ�������
{
	//����Ϊ����ѭ��������ɾ���߽�㣬Ȼ��Ϊ��������һ�����ʵ�first
	//�����а���X�α߽�ʱ��Ӧ������ָ�ΪX��
	int listNumber = list.number;
	int i, j;
	ListNode *nowList = list.first;
	LinkedNode *nowNode = nowList->thisList->first;
	int listLength;

	for (i = 0; i < listNumber; i++)
	{
		//ɾ���߽粿��
		//��first�ƶ���һ�����ʵ�λ��
		listLength = nowList->thisList->length;
		for (i = 0; i < listLength; i++)
		{
			if (edgeJudge(nowList->thisList->first->x, nowList->thisList->first->y, height, width)
				&& edgeJudge(nowList->thisList->first->next->x, nowList->thisList->first->next->y, height, width))
			{//��first�����һ����ڱ߽���ʱ
				nowList->thisList->first = nowList->thisList->first->next;
				nowList->thisList->last = nowList->thisList->last->next;
			}
		}

		//��ʼɾ���߽�
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

		//�ֽⲿ��
		//�ж���Ҫ�ֽ�Ϊ��������
		int listNumber = cutJudge(nowList->thisList);

		//�ֽ�
		if (listNumber > 1)
		{
			ListNode *newList;								//������
			ListNode *wholeList = nowList;					//���ڷֽ������
			LinkedNode *breakNode;
			int counter;				//���㵽��ϵ�ʱ�������˶��ٵ�
			for (j = 0; j < listNumber - 1; j++)
			{
				newList = new ListNode;
				newList->thisList = new MyLinkedList;
				newList->next = NULL;
				list.addList(newList);

				breakNode = wholeList->thisList->first;
				counter = 1;
				while (1)						//��Ѱ����ضϵĵ�
				{
					if (nearJudge(breakNode->x, breakNode->y, breakNode->next->x, breakNode->next->y) == false)
						break;
					breakNode = breakNode->next;
					counter++;
				}
				newList->thisList->first = breakNode->next;			//�������ͷΪ�ϵ����һ����
				newList->thisList->last = wholeList->thisList->last;	//�������ĩ����Ϊԭ�����ĩ��
				newList->thisList->length = wholeList->thisList->length - counter;		//��������������
				breakNode->next = wholeList->thisList->first;		//ԭ�����ĩ��ָ��ԭ�����ͷ
				wholeList->thisList->last = breakNode;				//��ԭ�����ĩ����Ϊ�ϵ�
				wholeList->thisList->length = counter;				//�޸�ԭ���������

																	//��һ������
				wholeList = newList;
			}
		}

		//��һ����
		nowList = nowList->next;
	}
}

bool ContoursTools::edgeJudge(int x, int y, int height, int width)
//�ж�(x,y)�Ƿ��ڸ�Ϊheighe����Ϊwidth�ľ���߽���
{
	if (x == 0) return true;
	if (y == 0) return true;
	if (x == height - 1) return true;
	if (y == width - 1) return true;
	return false;
}

int ContoursTools::cutJudge(MyLinkedList *nowList)
//������Ҫ��nowList�ֽ�Ϊ������������1ʱ������ֽ�

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
//�ж�(x1,y1),(x2,y2)�Ƿ�����
{
	if (x1 == x2 + 1 && y1 == y2) return true;
	if (x1 == x2 - 1 && y1 == y2) return true;
	if (y1 == y2 + 1 && x1 == x2) return true;
	if (y1 == y2 - 1 && x1 == x2) return true;
	return false;
}
