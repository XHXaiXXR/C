#include<iostream>
using namespace std;
#include <string>

void test()
{
	string str;
	cin>>str;

	int arr[6] = {0};
	for(int i = 0;i < 6;i++)
	{
		int j = i;
		int sum = 0;

		while(j < str.length())
		{
			int tmp = str[j];
			sum += tmp;
			j += 6;
		}

		arr[i] = sum;
	}

	for(int i = 0;i < 6;i++)
	{
		int sum = 0;
		while(arr[i] > 0)
		{
			sum += arr[i] % 10;
			arr[i] /= 10;
		}
		while (1)
		{
			if (sum > 9)
			{
				int total = 0;
				while (sum > 0)
				{
					total += sum % 10;
					sum /= 10;
				}
				sum = total;
			}
			else
				break;
		}
		arr[i] = sum;
	}

	for(int i = 0;i < 6;i++)
	{
		cout<<arr[i];
	}
	cout<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}