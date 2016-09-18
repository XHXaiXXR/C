#include<iostream>
using namespace std;
#include<assert.h>

template<class T>
class ArrayTwoStack
{
public:
	ArrayTwoStack()
		:_capacity(2)
		,_top1(-1)
		,_top2(_capacity)
		,_size1(0)
		,_size2(0)
	{
		_arr = new T[_capacity];
	}
	
	void Push(const T& data,int num)
	{
		CheckCapacity();
		assert(num == 1 || num == 2);

		if(num == 1)
		{
			_arr[++_top1] = data;
			_size1++;
		}
		else if(num == 2)
		{
			_arr[--_top2] = data;
			_size2++;
		}
	}
	void Pop(int num)
	{
		assert((num == 1 && _size1 != 0) \
				|| (num == 2 && _size2 != 0));
		
		if(num == 1)
		{
			_top1--;
			_size1--;
		}
		else if(num == 2)
		{
			_top2++;
			_size2--;
		}
	}
	T& Top(int num)
	{
		assert(num == 1 || num == 2);

		if(num == 1)
		{
			return _arr[_top1];
		}
		else if(num == 2)
		{
			return _arr[_top2];
		}
	}
	size_t Size(int num)
	{
		assert(num == 1 || num == 2);

		if(num == 1)
		{
			return _size1;
		}
		else if(num == 2)
		{
			return _size2;
		}
	}
	bool Empty(int num)
	{
		assert(num == 1 || num == 2);

		if(num == 1)
		{
			return _size1 == 0;
		}
		else if(num == 2)
		{
			return _size2 == 0;
		}
	}
private:
	void CheckCapacity()
	{
		if(_top1 + 1 == _top2)
		{
			size_t newcapacity = _capacity * 2 + 3;
			T* tmp = new T[newcapacity];
			if(tmp == NULL)
			{
				cout<<"new capacity false"<<endl;
				return;
			}
			else
			{
				for(int i = 0;i <= _top1;i++)
				{
					tmp[i] = _arr[i];
				}
				for(int i = _top2;i < _capacity;i++)
				{
					tmp[i] = _arr[i];
				}

				delete[] _arr;
				_arr = tmp;
				_capacity = newcapacity;
				_top2 = _top2 * 2 + 3;
			}
		}
	}
private:
	size_t _capacity;
	T _top1;
	T _top2;
	size_t _size1;
	size_t _size2;
	T* _arr;
};


void test()
{
	ArrayTwoStack<int> s;
	s.Push(1,1);
	s.Push(2,2);
	s.Push(3,1);
	s.Push(4,2);
	s.Push(5,1);
	s.Push(6,2);
	cout<<"top1 = "<<s.Top(1)<<endl;
	cout<<"size1 = "<<s.Size(1)<<endl;
	cout<<"top2 = "<<s.Top(2)<<endl;
	cout<<"size2 = "<<s.Size(2)<<endl;

	cout<<endl;

	s.Pop(1);
	s.Pop(1);
	s.Pop(2);
	cout<<"top1 = "<<s.Top(1)<<endl;
	cout<<"size1 = "<<s.Size(1)<<endl;
	cout<<"top2 = "<<s.Top(2)<<endl;
	cout<<"size2 = "<<s.Size(2)<<endl;
	
	cout<<endl;
	
	s.Push(10,1);
	cout<<"top1 = "<<s.Top(1)<<endl;
	cout<<"size1 = "<<s.Size(1)<<endl;
	cout<<"top2 = "<<s.Top(2)<<endl;
	cout<<"size2 = "<<s.Size(2)<<endl;
}
int main()
{
	test();
	return 0;
}