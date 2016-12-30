#include<iostream>
using namespace std;


void test()
{
	int time = 0;
	int minue = 0;
	cin>>time;
	cin>>minue;

	if (minue > 0)
	{
		while (minue != 0)
		{
			int tmpminue = time % 100;
			int num = 60 - tmpminue;

			if (num > minue)
			{
				time += minue;
				minue = 0;
			}
			else
			{
				minue -= num;
				time += 100 - tmpminue;
			}
		}
	} 
	else
	{
		minue = minue * (-1);
		int carry = minue / 60;
		time -= carry * 100;
		minue -= carry * 60;

		while(minue != 0)
		{
			int tmpminue = time % 100;

			if (minue > tmpminue)
			{
				minue -= tmpminue;
				time -= (tmpminue + 40);
			} 
			else
			{
				time -= minue;
				minue = 0;
			}
		}

		if (time % 100 == 60)
		{
			time += 40;
		}
	}

	cout<<time<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}