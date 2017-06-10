#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include<vector>


void test()
{
	vector<int> arr;
	int num = 0;
	cin>>num;
	for (int i = 0;i < num;++i)
	{
		int n = 0;
		cin>>n;
		arr.push_back(n);
	}

	int star = 0;
	int end = arr.size()-1;

	while (star < end)
	{
		//����ҵ�ż��ͣ����
		while (star < end && arr[star] % 2 != 0)
		{
			star++;
		}
		//�ұ��ҵ�����ͣ����
		while (star < end && arr[end] % 2 == 0)
		{
			end--;
		}

		swap(arr[star], arr[end]);
	}

	for (int i = 0;i < arr.size(); ++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}