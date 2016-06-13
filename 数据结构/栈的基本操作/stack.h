#pragma once

#include <iostream>
using namespace std;

template<class T>
class Stack
{
public:
	Stack()//构造函数
		:_array(NULL)
		,_top(-1)
		,_capacity(0)
	{}
	~Stack()//析构函数
	{
		if (_array)
		{
			delete[] _array;
		}
	}

	void Push(const T& num)//压栈
	{
		_CheckCapacity();
		_array[++_top] = num;
	}

	void Pop()//出栈
	{
		if (Empty() == true)
		{
			printf("Stack is Empty\n");
			return;
		} 
		else
		{
			--_top;
		}
	}

	T& GetTop()//获取栈的栈顶元素
	{
		return _array[_top];
	}

	void PrintStack()//打印栈中的元素
	{
		for (int i = 0;i <= _top;++i)
		{
			cout<<_array[i]<<"  ";
		}
		cout<<endl;
	}

	void PrintStackTop()//打印栈顶元素
	{
		cout<<_array[_top];
	}

	size_t Size()//获取栈的有效大小
	{
		return _top + 1;
	}

	T GetElem(int num)//取第i个数据，top不变
	{
		for (size_t i = 0;i < Size()-1;++i)
		{
			if (i == num-1)
			{
				return _array[i];
			}
		}
		return 0;
	}

	void MackEmpty()//使得栈为空
	{
		_top = -1;
	}
protected:
	void _CheckCapacity()//判断栈是否需要在开辟内存空间
	{
		if (_array == NULL)
		{
			_capacity = 5;
			_array = new T[_capacity];
			return;
		}

		if (_capacity == _top + 1)//动态增容
		{
			_capacity *= 2;
			T* tmp = new T[_capacity];

			for (size_t i = 0;i <= _top;++i)
			{
				tmp[i] = _array[i];
			}
			_array = tmp;
		}
	}

	bool Empty()//栈是否为空
	{
		return _top == -1;
	}
private:
	T* _array;
	int _top;
	size_t _capacity;
};