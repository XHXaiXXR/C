#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <assert.h>

char FindFirstOneChar(char* str)
{
	assert(str);
	int tables[256] = {0};//Ascii表中有256个字符
	char* tmp = str;

	while (*tmp != '\0')
	{
		//不加unsigned char也可以
		tables[(unsigned char)*tmp]++;
		tmp++;

		//也可以一步到位
		//tables[(unsigned char)*tmp++]++;
	}
	tmp = str;
	while (*tmp != '\0')
	{
		//不加unsigned char也可以
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

//查找一个字符串中第一个只出现一次的字符
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