#define _CRT_SECURE_NO_WARNINGS 1

#include "FileCompress.h"
#include<windows.h>

int main()
{
	int start =  GetTickCount();
	HuffmanFileCompress fc;
	fc.CompressFile("test.txt");
	HuffmanFileCompress fc2;
	fc2.UnCompressFile("test.txt.Compress");
	int end = GetTickCount();
	cout<<"Ñ¹ËõÎÄ¼þºÄÊ±£º"<<end - start<<endl;

	system("pause");
	return 0;
}