#include<iostream>
using namespace std;
#include<vector>

class UnionSet
{
public:
	UnionSet(int n)
		:_n(n)
	{
		_set.resize(n+1,-1);
		for(int i = 0;i < _set.size();++i)
		{
			_set[i] = -1;
		}
	}

	void UnionSetFrient(int root1,int root2)
	{
		int newroot1 = _FindRoot(root1);
		int newroot2 = _FindRoot(root2);

		if(newroot1 != newroot2)
		{
			_set[newroot1] += _set[newroot2];
			_set[newroot2] = newroot1;
		}
	}

	int Count()
	{
		int count = 0;
		for(int i = 0;i < _set.size();++i)
		{
			if(_set[i] < 0)
				++count;
		}

		//初始化时0位置的下标为-1，0位置下标不参与计算
		return (count - 1);
	}
protected:
	int _FindRoot(int x)
	{
		if(_set[x] >= 0)//不是根
		{
			x = _set[x];
		}

		return x;
	}
private:
	//int* _set;
	vector<int> _set;
	int _n;
};

int Frient(int n,int m,int arr[][2])
{
	UnionSet us(n);

	for(int i = 0;i < m;++i)
	{
		us.UnionSetFrient(arr[i][0],arr[i][1]);
	}

	return us.Count();
}

void test()
{
	const int n = 10;
	const int m = 7;
	int arr[m][2] ={{1,2},{2,3},{1,3},{4,5},{6,7},{7,8},{9,10}};
	
	cout<<"有多少个朋友圈："<<Frient(n,m,arr)<<endl;
}
int main()
{
	test();
	return 0;
}