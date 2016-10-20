#include<iostream>
using namespace std;
#include<vector>
#include<stack>
#include<queue>

void test()
{
	int n = 0;
	int k = 0;
	cin>>n>>k;
	stack<int> arr1;
	stack<int> arr2;
	stack<int> s;
	queue<int> arr;

	int newn = 2*n;
	while(newn--)
	{
		int num = 0;
		cin>>num;
		arr.push(num);
	}

	newn = n;
	while(newn--)
	{
		arr1.push(arr.front());
		arr.pop();
	}
	newn = n;
	while(newn--)
	{
		arr2.push(arr.front());
		arr.pop();
	}

	vector<int> tmp;
	while(k--)
	{
		tmp.clear();
		newn = n;

		while(newn--)
		{
			s.push(arr2.top());
			arr2.pop();
			s.push(arr1.top());
			arr1.pop();
		}

		while(!s.empty())
		{
			tmp.push_back(s.top());
			s.pop();
		}

		for(int i = 0;i < tmp.size()/2;i++)
		{
			arr1.push(tmp[i]);
		}
		for(int i = tmp.size()/2;i < tmp.size();i++)
		{
			arr2.push(tmp[i]);
		}
	}

	for (int i = 0;i < tmp.size();i++)
	{
		cout<<tmp[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}