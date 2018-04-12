#pragma once
/******************************************************
һ��bmp�ļ���4������ɣ�
1.λͼ�ļ�ͷBITMAPFILEHEADER
2.λͼ��Ϣ��BITMAPINFOHEADER
3.��ɫ����ϢPALETTEENTRY(����û��)
4.λͼ����(ͨ��ָ���ѯ����)
******************************************************/

#pragma pack(1)

typedef unsigned char BYTE;		//1�ֽ�
typedef unsigned short WORD;	//2�ֽ�
typedef unsigned int DWORD;		//4�ֽ�
typedef int LONG;		//4�ֽڣ��з���

typedef struct {
	WORD	bfType;				//�ļ����ͱ�ǣ���ֵ����Ϊ0x4D42(���ַ�"BM")
	DWORD	bfSize;				//�ļ���С�����ֽ�Ϊ��λ
	WORD	bfReserved1;		//����λ����������Ϊ0
	WORD	bfReserved2;		//����λ����������Ϊ0
	DWORD	bfOffBits;			//�������ļ�ͷ��ʼ��ʵ��ͼ������֮����ֽڵ�ƫ����(�ļ�ͷ����+��Ϣ����+��ɫ�峤��)
} MYBITMAPFILEHEADER;

typedef struct {
	DWORD	biSize;			//����BITMAPINFOHEADER������ֽ���
	LONG	biWidth;		//ͼ����
	LONG	biHeight;		//ͼ��߶�
	WORD	biPlanes;		//bmpͼƬ������ƽ�棬һ��Ϊ1
	WORD	biBitCount;		//ÿ����λ����ֵΪ1,4,8,16,24,32
	DWORD	biCompression;		//ͼ������ѹ������
								//BI_RGB��û��ѹ��
								//BI_RLE8��ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)��
								//BI_RLE4��ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����
								//BI_BITFIELDS��ÿ�����صı�����ָ�������������
								//BI_JPEG��JPEG��ʽ

	DWORD	biSizeImage;		//ͼ���С����ʽΪBI_RGBʱ��������Ϊ0
	LONG	biXPelsPerMeter;	//ˮƽ�ֱ��ʣ���λ����/��
	LONG	biYPelsPerMeter;	//��ֱ�ֱ��ʣ���λ����/��
	DWORD	biClrUsed;			//ʵ��ʹ�õĲ�ɫ���е���ɫ������(��Ϊ0��˵��ʹ�����е�ɫ����)
	DWORD	biClrImportant;		//˵����ͼ����ʾ����ҪӰ�����ɫ������Ŀ�����Ϊ0����ʾ����Ҫ
} MYBITMAPINFOHEADER;

typedef struct {				//��ɫ����Ϣ
	BYTE peRed;
	BYTE peGreen;
	BYTE peBlue;
	BYTE peFlags;
} MYPALETTEENTRY;

class Bitmap {
public:
	MYBITMAPFILEHEADER	fileHeader;
	MYBITMAPINFOHEADER	infoHeader;
	MYPALETTEENTRY		*paletteentry;
	BYTE				*buffer;

	Bitmap();
	Bitmap(Bitmap&);
	~Bitmap();

	bool readFile(char*);
};