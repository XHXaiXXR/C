#include<iostream>
using namespace std;
#include<string>
#include<stack>
#include<cmath>

void test()
{
	string str1 = "ABCBDAB";
	string str2 = "BDCABA";

	size_t x_len = str1.length();
	size_t y_len = str2.length();
	
	int arr[10][10] = {{0}};
	
	//问题的最优解，即X和Y的最长公共子序列的长度记录于arr[i][j]中
	for(int i = 1;i <= x_len;i++)
	{
		for(int j = 1;j <= y_len;j++)
		{
			if(str1[i-1] == str2[j-1])
				arr[i][j] = arr[i-1][j-1] + 1;
			else
				arr[i][j] = max(arr[i][j-1],arr[i-1][j]);
		}
	}
	
	//打印最长公共子序列长度的二维数组
	for(int i = 0;i <= x_len;i++)
	{
		for(int j = 0;j <= y_len;j++)
		{
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
	
	stack<char> s;//存放最长公共子序列
	for(int i = x_len,j = y_len;i >= 1,j >= 1; )
	{
		if(str1[i-1] == str2[j-1])
		{
			s.push(str1[i-1]);
			i--;
			j--;
		}
		else
		{
			if(arr[i][j-1] > arr[i-1][j])
				j--;
			else
				i--;
		}
	}

	cout<<endl;
	while(!s.empty())
	{
		cout<<s.top()<<" ";
		s.pop();
	}
	cout<<endl;

}

int main()
{
	test();
	return 0;
}