#define _CRT_SECURE_NO_WARNINGS 1

#include "Data.h"

void Test1()// ���캯��   �������캯��
{
	Data d;//����ȱʡ�Ĺ��캯��
	d.Display();
	Data d1(2016,6,2);//���Σ�������ȱʡֵ
	d1.Display();
	Data d2;
	d2 = d; //���ÿ������캯����
	d2.Display();
}

void Test2()//operator=()
{
	Data d(2005,8,8);
	d.Display();
	Data d1;
	d1 = d;
	d1.Display();
}

void Test3()//operator+()  operator-()
{
	Data d(2016,6,29);
	d.Display();

	//d = d + (-2);
	//d.Display();
	
	d = d - (-3);
	d.Display();
}

void Test4()//operator++()   operator++(int)  operator--()   operator--(int)
{
	Data d(2005,1,1);
	d.Display();
	//++d;
	//d++;
	//--d;
	d--;
	d.Display();
}

void Test5()//operator-()
{
	Data d(2016,6,8);
	d.Display();
	Data d1(2014,8,18);
	d1.Display();
	int day = d-d1;
	cout<<"л���ٺ�����ϼ��һ��"<<day<<"����"<<endl;
}

int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	Test5();
	system("pause");
	return 0;
}