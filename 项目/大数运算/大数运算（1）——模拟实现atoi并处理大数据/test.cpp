#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#include "BigData.h"

void TestAtoi()
{
	cout<<atoi("1234567890")<<endl;	//�Ϸ����ճ����	
	cout<<atoi("+878923743")<<endl;	//�з��ţ�������ǰ�治��Ҫ�ӷ���
	cout<<atoi("-328748923")<<endl;	//�з��ţ�������ǰ����Ҫ���Ϸ��š�-��
	cout<<atoi("aaa3878944")<<endl;	//�Ƿ��ַ��ڿ�ͷ�����0
	cout<<atoi("12238dhhd3")<<endl;	//�Ƿ��ַ����м䣬ֻ�����һ���Ƿ��ַ�ǰ�����������
	cout<<atoi("0000323423")<<endl;	//ǰ�õ���ɺ��Բ��ǣ���һ���������ֿ�ʼ
	cout<<atoi("000aa89898")<<endl;	//ǰ��0�ͷǷ��ַ������
	cout<<atoi("000387ss33")<<endl;	//ǰ��0�����ֺͷǷ��ַ������
}

void TestBigDataLikeAtoi()
{
	BigData b1("1234567890");
	BigData b2("+878923743");
	BigData b3("-328748923");
	BigData b4("aaa3878944");
	BigData b5("12238dhhd3");
	BigData b6("0000323423");
	BigData b7("000aa89898");
	BigData b8("000387ss33");
	BigData b9("+0000323423342345646576678768564564534534234234");
	BigData b10("-0564560087880989890645342343254546546567773423");

	cout<<b1<<endl;
	cout<<b2<<endl;
	cout<<b3<<endl;
	cout<<b4<<endl;
	cout<<b5<<endl;
	cout<<b6<<endl;
	cout<<b7<<endl;
	cout<<b8<<endl;
	cout<<b9<<endl;
	cout<<b10<<endl;
}
int main()
{
	//TestAtoi();
	TestBigDataLikeAtoi();
	system("pause");
	return 0;
}