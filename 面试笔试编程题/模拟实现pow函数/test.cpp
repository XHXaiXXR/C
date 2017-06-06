#include<iostream>
using namespace std;

bool Equal(double num1, double num2)
{
	if (((num1 - num2) > -0.0000001) && ((num1 - num2) < 0.0000001))
	{
		return true;
	} 
	else
	{
		return false;
	}
}

void test()
{
	double base = 0.0;
	int exponent = 0;
	cin>>base;
	cin>>exponent;

	if (Equal(base, 0.0))
	{
		cout<<"result = "<<"0"<<endl;
	}

	double result = 1.0;
	int exponent_new = exponent;

	if (exponent < 0)
	{
		exponent_new = -exponent;
	}
	for (int i = 0; i < exponent_new; ++i)
	{
		result *= base;
	}

	if (exponent < 0)
	{
		result = 1.0 / result;
	}

	cout<<"result = "<<result<<endl;
}

int main()
{
	test();
	system("pause");	
	return 0;
}