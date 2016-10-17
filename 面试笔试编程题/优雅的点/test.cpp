#include<iostream>
using namespace std;
#include<math.h>

void test()
{
	int num = 0;
	int count = 0;
	cin>>num;
		
	for(int i = 0;i < sqrt(num);i++)
	{
		double j = sqrt(num - i*i);
		
		if(int(j) == j)
		{
			count++;
		}
	}

	cout<<4*count<<endl;
}
int main()
{
	test();
	return 0;
}