#include<iostream>
using namespace std;

int SumNoRound(int minnum,int maxnum)
{
	if(maxnum == minnum)
	{
		return minnum;
	}
	return maxnum + SumNoRound(minnum,maxnum-1);
}
void test()
{
	int minnum = 0;
	cout<<"please get me a minnum:";
	cin>>minnum;
	cout<<"please get me a maxnum:";
	int maxnum = 0;
	cin>>maxnum;
	int sum = SumNoRound(minnum,maxnum);
	cout<<"sum = "<<sum<<endl;
}
int main()
{
	test();
	return 0;
}