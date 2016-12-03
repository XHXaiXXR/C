#pragma once
#include<vector>

class UnionSet
{
public:
	UnionSet(int n)
		:_n(n)
	{
		_set.resize(n+1,-1);
		for(size_t i = 0;i < _set.size();++i)
		{
			_set[i] = -1;
		}
	}

	void UnionSetFrient(int root1,int root2)
	{
		int newroot1 = FindRoot(root1);
		int newroot2 = FindRoot(root2);

		if(newroot1 != newroot2)
		{
			_set[newroot1] += _set[newroot2];
			_set[newroot2] = newroot1;
		}
	}

	int Count()
	{
		int count = 0;
		for(size_t i = 0;i < _set.size();++i)
		{
			if(_set[i] < 0)
				++count;
		}

		//��ʼ��ʱ0λ�õ��±�Ϊ-1��0λ���±겻�������
		return (count - 1);
	}
	int FindRoot(int x)
	{
		if(_set[x] >= 0)//���Ǹ�
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

