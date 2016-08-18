#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <assert.h>

char FindFirstOneChar(char* str)
{
	assert(str);
	int tables[256] = {0};//Ascii������256���ַ�
	char* tmp = str;

	while (*tmp != '\0')
	{
		//����unsigned charҲ����
		tables[(unsigned char)*tmp]++;
		tmp++;

		//Ҳ����һ����λ
		//tables[(unsigned char)*tmp++]++;
	}
	tmp = str;
	while (*tmp != '\0')
	{
		//����unsigned charҲ����
		if (tables[(unsigned char)*tmp] == 1)
		{
			return *tmp;
		} 
		else
		{
			tmp++;
		}
	}
}

//����һ���ַ����е�һ��ֻ����һ�ε��ַ�
void Test()
{
	char* str = "hhddadeechrhg";
	char ret = FindFirstOneChar(str);
	cout<<ret<<endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}