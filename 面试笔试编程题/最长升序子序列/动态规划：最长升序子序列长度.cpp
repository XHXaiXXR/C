#include <iostream>
using namespace std;
#include <vector>

void test()
{
	int arr[] = {2,3,4,2,3,4,5,0,3};
	int size = sizeof(arr)/sizeof(arr[0]);
	int maxlen = -1;

	vector<int> len(size,1);//�����iΪ�յ����������еĸ���
	for (int i = 1;i < size;++i)
	{
		int max = 0;
		for (int j = 0;j < i;++j)
		{
			//Ѱ����iΪ�յ㣬ǰi-1�������е�������У���Ϊ���ŵ���״̬
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

	//��ӡ״̬�б�
	for (int i = 0;i < size;++i)
	{
		cout<<len[i]<<" ";
	}
	cout<<endl;

	cout<<"��������г��ȣ�"<<maxlen<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}