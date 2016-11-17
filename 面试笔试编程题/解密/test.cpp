#include <iostream>
using namespace std;
#include<string>
#include <algorithm>
#include<vector>

void DFS(const string& str,int len,vector<int>& v,vector<char>& arr)
{
	if (len == str.size())
	{
		for (int i = 0;i < len;i++)
		{
			cout<<arr[i];
		}
		cout<<endl;
		return;
	}

	for (int i = 0;i < str.size();i++)
	{
		if (v[i] == 0)
		{
			arr[len] = str[i];
			v[i] = 1;
			DFS(str,len+1,v,arr);
			v[i] = 0;
		}
	}
}
void test()
{
	string str;
	cin>>str;
	sort(str.begin(),str.end());

	vector<int> boolarr(str.size());
	vector<char> arr(str.size());
	DFS(str,0,boolarr,arr);
}

int main()
{
	test();
	system("pause");
	return 0;
}