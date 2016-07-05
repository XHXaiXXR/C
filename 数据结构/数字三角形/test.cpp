#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#define MAX 100
int Arr[MAX][MAX];
size_t N = 0;

size_t MaxSum(int col,int row)
{
	if (col == N)
	{
		return Arr[col][row];
	}

	int _LeftSum = MaxSum(col+1,row);//�����½ǵݹ�
	int _RightSum = MaxSum(col+1,row+1);//���ҵݹ�

	return _LeftSum > _RightSum ? _LeftSum + Arr[col][row] : _RightSum + Arr[col][row];
}

void Test()
{
	cout<<"���������������ε�������"<<endl;
	cin>>N;
	cout<<"����������"<<endl; 
	for (int i = 1;i <= N; ++i)
	{
		for (int j = 1; j <= i; ++j)
		{
			cin>>Arr[i][j];
		}
	}

	int maxsum = MaxSum(1,1);
	cout<<"�����������·��Ϊ�� "<<maxsum<<endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}