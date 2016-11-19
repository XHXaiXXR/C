#include <iostream>
using namespace std;
#include <vector>

void test()
{
	int arr[] = {2,3,4,2,3,4,5,0,3};
	int size = sizeof(arr)/sizeof(arr[0]);
	int maxlen = -1;

	vector<int> len(size,1);//存放以i为终点的最长升序序列的个数
	for (int i = 1;i < size;++i)
	{
		int max = 0;
		for (int j = 0;j < i;++j)
		{
			//寻找以i为终点，前i-1个序列中的最长子序列，即为最优的子状态
			if (arr[j] < arr[i] && len[j] > max)
			{
				max = len[j];
			}
		}
		len[i] = max + 1;
		if (maxlen < len[i])
		{
			maxlen = len[i];
		}
	}

	//打印状态列表
	for (int i = 0;i < size;++i)
	{
		cout<<len[i]<<" ";
	}
	cout<<endl;

	cout<<"最长升序序列长度："<<maxlen<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}