#include<iostream>
using namespace std;
#include <sstream>

void test()
{
	//将字符串转成数字
	int num = 0;
	stringstream ss1("5432532");
	ss1>>num;
	cout<<num<<endl;

	//将数字转成字符串
	num = 987;
	stringstream ss2;
	ss2<<num;
	cout<<ss2.str()<<endl;

	//将字符串转成数字
	char* p = "8787834";
	num = atoi(p);
	cout<<num<<endl;

	//string类转成char类型
	string str("njdnisn");
	char* AA = (char*)str.c_str();//c_str()的返回值是const char*，所以赋值的话需要强转成char*
	cout<<AA<<endl;

	//char类型转成string类
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