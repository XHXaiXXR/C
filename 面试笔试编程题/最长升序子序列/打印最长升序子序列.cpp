#include<iostream>
using namespace std;
#include<vector>

void test()
{
	int arr[] = {0,1,2,6,3,5,6,7,8,9,0};
	//int arr[] = {2,3,4,2,3,4,5,0,3};
	int end = 0;
	int mark_end = 0;
	int size = 1;
	int mark_size = -1;

	//[��ʼλ�ã�����]	[���ȣ�����λ��]		[��ʼλ�ã�����λ��]	���ߵȼ�
	for(int i = 1;i < sizeof(arr)/sizeof(arr[0]);++i)
	{
		if(arr[i] >= arr[end])
			++size;
		else
		{
			if(size > mark_size)
			{
				mark_end = end;
				mark_size = size;
			}
			//�����󳤶�������1������λ�ÿ�ʼ��¼	
			size = 1;
		}

		++end;
	}
	
	//���arr[i] > arr[end],size++�󣬲�û�к�mark_size��ֵ�Ƚ�
	if(size > mark_size)
	{
		mark_end = end;
		mark_size = size;
	}

	int index = 0;
	vector<int> tmp(mark_size);
	for(int i = mark_end - mark_size + 1;i <= mark_end;++i)
	{
		tmp[index++] = arr[i];
	}

	//��ӡ
	for(int i = 0;i < tmp.size();++i)
	{
		cout<<tmp[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	test();
	return 0;
}