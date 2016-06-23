#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <assert.h>

bool Find(int* arr,int _row,int _col,int num)
{
	assert(arr);
	assert(_row > 0);
	assert(_col > 0);
	int row = 0;
	int col = _col - 1;//从右下角开始查找

	while (row < _row && col >= 0)
	{
		if (arr[row * _col + col] == num)
		{
			return true;
		} 
		else if (arr[row * _col + col] > num)
		{
			col--;
		}
		else//arr[row * _col + col] < num
		{
			row++;
		}
	}

	return false;
}

void test()
{
	int arr[4][4] = {{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
	int ret = Find((int*)arr,4,4,6);
	if (ret == true)
	{
		cout<<"find"<<endl;
	} 
	else
	{
		cout<<"no find"<<endl;
	}
} 

int main()
{
	test();
	system("pause");
	return 0;
}