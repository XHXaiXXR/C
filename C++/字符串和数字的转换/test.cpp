#include<iostream>
using namespace std;
#include <sstream>

void test()
{
	//���ַ���ת������
	int num = 0;
	stringstream ss1("5432532");
	ss1>>num;
	cout<<num<<endl;

	//������ת���ַ���
	num = 987;
	stringstream ss2;
	ss2<<num;
	cout<<ss2.str()<<endl;

	//���ַ���ת������
	char* p = "8787834";
	num = atoi(p);
	cout<<num<<endl;

	//string��ת��char����
	string str("njdnisn");
	char* AA = (char*)str.c_str();//c_str()�ķ���ֵ��const char*�����Ը�ֵ�Ļ���Ҫǿת��char*
	cout<<AA<<endl;

	//char����ת��string��
	char* BB = "hello";
	string str1 = BB;
	cout<<str1<<endl;

}
int main()
{
	test();
	system("pause");
	return 0;
}