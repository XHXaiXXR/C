#include<iostream>
using namespace std;
#include<assert.h>

template<class T>
class Stack
{
public:
	Stack()
		:_arr(NULL)
		,_size(0)
		,_capacity(0)
	{}
	void Push(const T& data)
	{
		_CheckCapacity();
		_arr[_size++] = data;
	}
	void Pop()
	{
		assert(_size > 0);
		_size--;
	}
	bool Empty()
	{
		return _size == 0;
	}
	T& Top()
	{
		return _arr[_size - 1];
	}
	size_t Size()
	{
		return _size;
	}
	size_t Capacity()
	{
		return _capacity;
	}
private:
	void _CheckCapacity()
	{
		if(_size == _capacity)
		{
			size_t newcapacity = 2*_capacity + 2;
			T* tmp = new T[newcapacity];
			for(size_t i = 0;i < _size;++i)
			{
				tmp[i] = _arr[i];
			}
			delete[] _arr;
			_arr = tmp;
			_capacity = newcapacity;
		}
	}
private:
	T* _arr;
	size_t _size;
	size_t _capacity;
};
void test()
{
	Stack<int> s;
	for(size_t i = 1;i <= 5;i++)
	{
		s.Push(i);
	}
	cout<<"size = "<<s.Size()<<endl;
	cout<<"capacity = "<<s.Capacity()<<endl;

	while(!s.Empty())
	{
		cout<<s.Top()<<" ";
		s.Pop();
	}
	
	cout<<endl;
	cout<<"size = "<<s.Size()<<endl;
	cout<<"capacity = "<<s.Capacity()<<endl;
}
int main()
{
	test();
	return 0;
}
