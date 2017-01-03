#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#include "BigData.h"
#include <sstream>
#include <string>

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

void TestOperatorAdd()
{
	//���� + ���� = ����
	BigData b1("-11111111111111111111111111111111111111111111");//44λ
	BigData b2("-999999999999999999999");//21λ
	cout<<b1+b2<<endl;

	//�������ϴ� + ��������С�� = ����
	BigData b3("-1647567436598347899222233232");//28λ
	BigData b4("999999999999999999999");//21λ
	cout<<b3+b4<<endl;

	//���� + ���� = ����
	BigData b5("999999999999999999999");//21λ
	BigData b6("999999999999999999999");//21λ
	cout<<b5+b6<<endl;	

	//�������ϴ� + ��������С�� = ����
	BigData b7("99999999999999999999999999999999999999999");
	BigData b8("-11111111111111111111111111");
	cout<<b7+b8<<endl;	
}
void TestStringCompare()
{
	std::string str1 = "2111111111";
	std::string str2 = "111111111111111111111111";
	
	int num = str1.compare(str2);
	cout<<num<<endl;
}
void TestOperatorSub()
{
	//�������ϴ� - ��������С�� = ���� 
	BigData b1("555555555555555555555");//21λ
	BigData b2("7777777751234");//21λ
	cout<<b1-b2<<endl;

	//�������ϴ� - ��������С�� = ����
	BigData b3("-555555555555555555555");
	BigData b4("-777777777777777777777777777777");
	cout<<b3-b4<<endl;

	//���� - ���� = ����
	BigData b5("11111111111111111111111111111");
	BigData b6("-55555555555555555555555555555");
	cout<<b5-b6<<endl;
	
	//���� - ���� = ����
	BigData b7("-111111111111111111");
	BigData b8("55555555555555555555555555555");
	cout<<b7-b8<<endl;
}
void TestOperatorMul()
{
	BigData b1("435");
	BigData b2("453");
	cout<<b1*b2<<endl;

	BigData b3("435");
	BigData b4("-453");
	cout<<b3*b4<<endl;

	BigData b5("445335");
	BigData b6("4535456");
	cout<<b5*b6<<endl;

	BigData b7("-4454335");
	BigData b8("-45245453");
	cout<<b7*b8<<endl;

	BigData b9("33478071698956898786044169848212690817704794983713768568912431388982883793878002287614711652531743087737814467999489");
	BigData b10("36746043666799590428244633799627952632279158164343087642676032283815739666511279233373417143396810270092798736308917");
	cout<<b9*b10<<endl;

	BigData b11("1995329832536118781503430");
	BigData b12("22675676878679");
	cout<<b11*b12<<endl;
}

void TestStringStream()
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
}
void TestOperatorDiv()
{
	BigData b1("36278");
	BigData b2("22");
	cout<<b1/b2<<endl;

	BigData b3("0");
	BigData b4("22");
	cout<<b3/b4<<endl;

	BigData b5("45245454548977709709890899786767542574");
	BigData b6("45245454548977709709890886381332368970");
	cout<<b5/b6<<endl;

	BigData b7("45245454548977709709890886381332368970");
	BigData b8("1995329832536118781503430");
	cout<<b7/b8<<endl;
}
int main()
{
	//TestAtoi();
	//TestBigDataLikeAtoi();
	//TestOperatorAdd();
	//TestStringCompare();
	//TestOperatorSub();
	//TestOperatorMul();
	TestOperatorDiv();
	//TestStringStream();

	system("pause");
	return 0;
}