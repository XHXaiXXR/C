#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <assert.h>

class UnionFindSet
{
public:
	//构造函数
	UnionFindSet(int n)
		:_n(n)
		,_set(new int[n])
	{
		//初始化_set数组，全部初始化为-1
		memset(_set,-1,sizeof(int)*n);
	}
	void Union(int x1,int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);

		if (root1 != root2)
		{
			_set[root1] += _set[root2];
			_set[root2] = root1;
		}
	}
	int Count()
	{
		int count = 0;
		for (size_t i = 0;i < _n;i++)
		{
			if (_set[i] < 0)
			{
				count++;
			}
		}
		return count-1;//0的位置一开始就初始化成-1，0的位置不用
		               //故_set[0]为负数不属于一个朋友圈
	}
private:
	int FindRoot(int x)
	{
		if (_set[x] >= 0)
		{
			x = _set[x];
		}
		return x;
	}
protected:
	int* _set;//设置一个数组存放值
	int _n;
};

int Friend(int n,int m,int r[][2])
{
	assert(r);
	UnionFindSet ufs(n+1);//0的位置不用
	for (size_t i = 0;i < m;i++)
	{
		int r1 = r[i][0];
		int r2 = r[i][1];
		ufs.Union(r1,r2);
	}
	
	return ufs.Count();
}
void Test1()
{
	int r[3][2] = {{1,2},{2,3},{4,5}};//n=总人数，m=多少对好友关系
	cout<<"朋友圈？"<<Friend(5,3,r)<<endl;
}
void Test2()
{
	int r[][2] = {{1,2},{2,3},{4,5},{5,9},{6,2},{7,8}};//n=总人数，m=多少对好友关系
	cout<<"朋友圈？"<<Friend(9,6,r)<<endl;
}
int main()
{
	Test1();
	//Test2();
	system("pause");
	return 0;
}