#pragma once

#include <iostream>
using namespace std;

template<class T>
class Stack
{
public:
	Stack()//���캯��
		:_array(NULL)
		,_top(-1)
		,_capacity(0)
	{}
	~Stack()//��������
	{
		if (_array)
		{
			delete[] _array;
		}
	}

	void Push(const T& num)//ѹջ
	{
		_CheckCapacity();
		_array[++_top] = num;
	}

	void Pop()//��ջ
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

	T& GetTop()//��ȡջ��ջ��Ԫ��
	{
		return _array[_top];
	}

	void PrintStack()//��ӡջ�е�Ԫ��
	{
		for (int i = 0;i <= _top;++i)
		{
			cout<<_array[i]<<"  ";
		}
		cout<<endl;
	}

	void PrintStackTop()//��ӡջ��Ԫ��
	{
		cout<<_array[_top];
	}

	size_t Size()//��ȡջ����Ч��С
	{
		return _top + 1;
	}

	T GetElem(int num)//ȡ��i�����ݣ�top����
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

	void MackEmpty()//ʹ��ջΪ��
	{
		_top = -1;
	}
protected:
	void _CheckCapacity()//�ж�ջ�Ƿ���Ҫ�ڿ����ڴ�ռ�
	{
		if (_array == NULL)
		{
			_capacity = 5;
			_array = new T[_capacity];
			return;
		}

		if (_capacity == _top + 1)//��̬����
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

	bool Empty()//ջ�Ƿ�Ϊ��
	{
		return _top == -1;
	}
private:
	T* _array;
	int _top;
	size_t _capacity;
};