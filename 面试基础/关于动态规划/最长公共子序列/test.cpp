#include<iostream>  
using namespace std;  
#include<string>  
#include <queue>

void test()  
{  
	string str1 = "ABCBDAB";
	string str2 = "BDCABA";

	int arr[10][10] = {{0}};

	for (int i = 1;i <= str1.size();++i)
	{
		for (int j = 1;j <= str2.size();++j)
		{
			if (str1[i-1] == str2[j-1])
			{
				arr[i][j] = arr[i-1][j-1] + 1;
			}
			else
			{
				arr[i][j] = max(arr[i-1][j],arr[i][j-1]);
			}
		}
	}
	queue<char> q;
	for (int i = 0,j = 0;i < str1.size(),j < str2.size();)
	{
		if (str1[i] == str2[j])
		{
			q.push(str1[i]);
			i++;
			j++;
		} 
		else
		{
			if (arr[i+1][j+2] > arr[i+2][j+1])
			{
				j++;
			} 
			else
			{
				i++;
			}
		}
	}

	while(!q.empty())
	{
		cout<<q.front()<<" ";
		q.pop();
	}
	cout<<endl;
}  

int main()  
{  
	test();  
	system("pause");
	return 0;  
}
