#include<iostream>
using namespace std;


void test()
{
	int cm = 0;
	cin>>cm;
	
	double m = ((double)cm)/100;

	int foot = m / 0.3048;
	int inch = (m / 0.3048 - foot) * 12;

	cout<<foot<<" "<<inch<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}