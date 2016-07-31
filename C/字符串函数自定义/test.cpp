#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "StrMen.h"

void Test1()
{
	char arr[20] = "abcdefgh";
	char *p = "hello bit";
	//strcpy(arr,p);
	MySrtcpy(arr,p);
	cout<<arr<<endl;
}

void Test2()
{
	char arr[20] = "hello_whord";
	char *p = "strncpy";
	//strncpy(arr,p,8);
	MyStrncpy(arr,p,5);
	cout<<arr<<endl;
}

void Test3()
{
	char arr[20] = "hello ";
	char *p = "world";
	//strcat(arr,p);
	MyStrcat(arr,p);
	cout<<arr<<endl;
}

void Test4()
{
	char arr[20] = "hello ";
	char *p = "world";
	//strncat(arr,p,3);
	MySrtncat(arr,p,7);
	cout<<arr<<endl;
}

void Test5()
{
	char *p = "abcded";
	char *q = "abcdea";
	//int ret = strcmp(p,q);
	int ret = MyStrcmp(p,q); 
	cout<<ret<<endl;
}

void Test6()
{
	char *p = "abcde";
	char *q = "abciab";
	//int ret = strncmp(p,q,3);//
	int ret = MyStrncmp(p,q,5);
	cout<<ret<<endl;
}

void Test7()
{
	char *p = "hello world";
	char *q = "ello";
	//cout<<strstr(p,q)<<endl;
	cout<<MyStrstr(p,q)<<endl;
}

void Test8()
{
	char *p = "abcde";
	char c = 'd';
	//cout<<strchr(p,c)<<endl;
	cout<<MyStrchr(p,c)<<endl;
}

void Test9()
{
	char *p = "hello";
	char arr[] = "bit";
	//cout<<strlen(p)<<endl;
	//cout<<strlen(arr)<<endl;
	cout<<MyStrlen(p)<<endl;
	cout<<MyStrlen(arr)<<endl;

	cout<<MyStrlen_OP(p)<<endl;
	cout<<MyStrlen_OP(arr)<<endl;
}

int main()
{
	//Test1();//strcpy
	//Test2();//strncpy
	//Test3();//strcat
	//Test4();//strncat
	//Test5();//strcmp
	//Test6();//strncmp
	//Test7();//strstr
	//Test8();//strchr
	Test9();//strlen
	system("pause");
	return 0;
}