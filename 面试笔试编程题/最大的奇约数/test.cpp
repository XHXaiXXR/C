#include<iostream>
using namespace std;

int rev(int x)
{
	int tmp = 0;

	while(x > 0)
	{
		tmp = tmp * 10 + x % 10;
		x = x / 10;
	}
	return tmp;
}
void test()
{
	int x = 0;
	int y = 0;
	cin>>x>>y;

	cout<<rev(rev(x)+rev(y))<<endl;
}
int main()
{
	test();
	return 0;
}